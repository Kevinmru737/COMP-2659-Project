/*
* Main game loop
*/
#include "input.h"
#include "models.h"
#include "events.h"
#include "render.h"
#include "rast_asm.h"
#include "macros.h"
#include "level.h"
#include "music.h"
#include "effects.h"
#include "global.h"
#include "vbl.h"
#include "vct_inst.h"
#include <osbind.h>
#include "vic.h"
#define FINAL_VICTORY_FRAME_COUNT 10
UINT8 allocated_buffer[32260];


/*GLobals to sync with the VBL*/
Model model;
unsigned char game_state;
bool fatal_collision;
short render_request = 0;

void final_victory_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer);
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);
void main_game_loop();
void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer, Model *model, short *num_times_ground_drawn);
void delay_to_display_score();
void paul_mode();


int main() {

    UINT8 *current_buffer = (UINT8 *) get_video_base();
    unsigned char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    Vector orig_vbl_vector;
    bool user_quit = FALSE;

    render_splash_screen(current_buffer);
    init_keyboard_isr();
    orig_vbl_vector = install_vector(VBL_VECTOR_NUM, vbl_isr);

    while(user_quit == FALSE) {
        if(ch == ' ') {
            main_game_loop();
            render_splash_screen(current_buffer);
        }

        ch = NO_INP_CHAR;
        user_input(&ch);
        user_quit = (ch == '\033');
    }
    
    install_vector(VBL_VECTOR_NUM, orig_vbl_vector);

    restore_keyboard_isr();
  
    
    return 0;
}






void main_game_loop() {

    UINT32 *back_buffer, *front_buffer, *current_buffer;
    
    short num_times_ground_drawn = 0;
    unsigned char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    

    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
    current_buffer = back_buffer;
    enter_super();
    start_music();
    exit_super();

    
    
    is_main_game_running = TRUE;
    game_state = 0;
    fatal_collision = FALSE;

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
    is_main_game_running = FALSE;
    
    if(fatal_collision == TRUE) {

        enter_super();
        play_explosion_sound();
        exit_super();

        fatal_Collision_animation(back_buffer, front_buffer,current_buffer, &model, &num_times_ground_drawn);
        render_score(current_buffer, game_state -1 );
        set_video_base(current_buffer);
        delay_to_display_score();

    } else {
        final_victory_animation(back_buffer, front_buffer, current_buffer);
    }
  

    enter_super();
    stop_sound();
    exit_super();
    
    set_video_base(front_buffer);


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


    event_animation_running = TRUE;
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

    event_animation_running = FALSE;


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
 * Purpose: Pauses the program execution so that the score can be display for a brief time
 *********************************************************/
void delay_to_display_score() {
    unsigned long i = 0;
    while (i++ < 1000000);

}







/* Similar to the main game loop, but with collisions tunred off
*/
void paul_mode() {

    UINT32 *back_buffer, *front_buffer, *current_buffer;
    short num_times_ground_drawn = 0;
    unsigned char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    
    game_state = 0;

    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
    enter_super();
    start_music();
    exit_super();

    current_buffer = back_buffer;
    is_main_game_running = TRUE;
    while (game_state < MAX_GAME_STATE) {
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

    is_main_game_running = FALSE;

    enter_super();
    stop_sound();
    exit_super();

    final_victory_animation(back_buffer, front_buffer, current_buffer);

    set_video_base(front_buffer);


}






void final_victory_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer){
    short animation_frame_counter;
    short animation_loop_count = 0;


    event_animation_running = TRUE;
    while (animation_loop_count < 10) {     
        animation_frame_counter = 0;
        while(animation_frame_counter < FINAL_VICTORY_FRAME_COUNT) {

	        if(render_request == 1) {
                draw_8_bit_bitmap((UINT8 *)current_buffer, 0 ,0, 400, 640, victory_animation_frames[animation_frame_counter]);
                set_video_base(current_buffer);
                switch_buffers(&current_buffer, front_buffer, back_buffer);

    		    animation_frame_counter++;
                render_request = 0;
	        }
   
        }
        animation_loop_count++;

    }
    event_animation_running = FALSE;

}

















