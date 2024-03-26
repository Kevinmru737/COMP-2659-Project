/*
* Main game loop
*/
#include "input.h"
#include "models.h"
#include "events.h"
#include "render.h"
#include "macros.h"
#include "level.h"
#include "music.h"
#include "effects.h"
#include "rast_asm.h"
#include "global.h"
#include "vbl.h"
#include "vct_inst.h"
#include <osbind.h>

UINT8 allocated_buffer[32260];
Model model;
unsigned char game_state;
bool fatal_collision;
short render_request = 0;
UINT32 get_time();
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);
void main_game_loop();
void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer, Model *model, short *num_times_ground_drawn);
void wait_for_1_second();



int main() {


    UINT8 *current_buffer = (UINT8 *) get_video_base();
    char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/

    bool user_quit = FALSE;

    render_splash_screen(current_buffer);
    while(user_quit == FALSE) {
        if(ch == ' ') {
            main_game_loop();
            render_splash_screen(current_buffer);
        }

        ch = NO_INP_CHAR;
        user_input(&ch);
        user_quit = (ch == '\033');
    }

    draw_8_bit_bitmap((UINT8*) current_buffer, 608, 0, 400, 32, 
                   victory_wall);
    
    
    
    
    
    
    return 0;
}






void main_game_loop() {

    UINT32 *back_buffer, *front_buffer, *current_buffer;
    bool user_quit;
    short num_times_ground_drawn = 0;
    short player_num = PLAYER_INDEX;
    char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    Vector orig_vbl_vector = install_vector(VBL_VECTOR_NUM, main_gm_vbl_isr);

    game_state = 0;
    user_quit = fatal_collision = FALSE;



    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
/*    start_music();
*/

    current_buffer = back_buffer;
    while (fatal_collision == FALSE && game_state < MAX_GAME_STATE) {
        if(ch == ' ') {
            jump_request(&model, 0);
        }

        if (render_request == 1) {
            render(&model, current_buffer, &num_times_ground_drawn);
            set_video_base(current_buffer);

            switch_buffers(&current_buffer, front_buffer, back_buffer);
            render_request = 0;

       }
        ch = NO_INP_CHAR;
        user_input(&ch);

    }
    install_vector(VBL_VECTOR_NUM, orig_vbl_vector);

    if(fatal_collision == TRUE) {
  /*      play_explosion_sound();*/
        fatal_Collision_animation(back_buffer, front_buffer,current_buffer, &model, &num_times_ground_drawn);
    }

    /*stop_sound();*/
    render_score(current_buffer, game_state -1 );
    set_video_base(current_buffer);

    wait_for_1_second();

    set_video_base(front_buffer);

    game_state = 0;
    fatal_collision = FALSE;



}
















/*********************************************************
 * Author: Paul Pospisil
 * Purpose: Retrieves the current time from a cpu clock. This function accesses
 * 			a timer in the memory that increments 70 times per second and returns the current
 * 			value of this timer.
 *
 * Input: None.
 * Output: Returns the current time as a UINT32 value.
 *
 *********************************************************/
UINT32 get_time(){
	UINT32 time_now;
	UINT32 old_ssp;
	UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */
	
	old_ssp = Super(0); /* enter privileged mode */
	time_now = *timer;
	Super(old_ssp); /* exit privileged mode */
	
	return time_now;
	
}



/*********************************************************
 * Purpose: Initializes the back and front buffer pointers for double buffering
 *
 * Details: * The back buffer pointer is set to a 256-byte aligned address within the global back_buffer_array.
 * 			 front buffer pointer is set to point to the value provided by the TOS call PHysbase()
 *
 * Input:  Back buffer, front buffer and the original true buffer
 * Output: Modifies the back buffer to point to a 256 byte aligned address in back_buffer_array and changes the address stored at front buffer
 *
 *********************************************************/
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]) {

    UINT8 *temp = back_buffer_array;

    while( ((UINT32) temp) & 0xFF) {
        temp++;
    }

    *back_buffer =	(UINT32*) temp;
    *front_buffer =  get_video_base();
}

/*********************************************************
 * Purpose: Executes the animation of a fatal collision in a game
 *
 * Input: back_buffer - Pointer to the back buffer's base address.
 *        front_buffer - Pointer to the front buffer's base address.
 *        model - Pointer to the game model containing state and objects to be rendered.
 *        is_curr_buffer_front - Pointer to a boolean flag indicating the currently active buffer (TRUE for front, FALSE for back).
 *
 * Output: Animates a fatal collision by cycling through explosion images on the game display. 
 *********************************************************/

void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer, Model *model, short *num_times_ground_drawn){
  
    short explosion_counter = 0;
    Vector orig_vbl_vector = install_vector(VBL_VECTOR_NUM, fatal_animation_vbl_isr);


    while(explosion_counter < EXPLOSION_ANIMATION_TOTAL_FRAMES) {

	    if(render_request == 1) {
            render(model, current_buffer, num_times_ground_drawn);
            render_explosion(model, current_buffer, explosion_counter);
            set_video_base(current_buffer);
            switch_buffers(&current_buffer, front_buffer, back_buffer);

    		explosion_counter++;
            render_request = 0;
	    }

    }
    
    install_vector( VBL_VECTOR_NUM, orig_vbl_vector);


}

/*********************************************************
 * Purpose: Toggles between the front and back buffers.
 *
 * Input: current_buffer - Double pointer to the current buffer's base address.
 *        front_buffer - Pointer to the front buffer's base address.
 *        back_buffer - Pointer to the back buffer's base address.
 *
 * Output: Modifies the current_buffer pointer to switch between pointing to the front and the back buffer.
 *********************************************************/
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer) {

    if(*current_buffer == front_buffer) {
        *current_buffer = back_buffer;
    } else {
        *current_buffer = front_buffer;
    }


}

/*********************************************************
 * Purpose: Pauses the program execution for 1 second *
 *********************************************************/
void wait_for_1_second() {
    UINT32 start_time = get_time();

    while (get_time() - start_time < 70) {}

}
