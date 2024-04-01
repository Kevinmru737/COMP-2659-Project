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
#include "vic.h"

#define FINAL_VICTORY_FRAME_COUNT   10

UINT8 allocated_buffer[32260];


/*Globals to sync with the VBL*/
Model model;
unsigned char game_state;
bool fatal_collision;


void final_victory_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer);
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);
void main_game_loop();
void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer, Model *model, short *num_times_ground_drawn);
void delay_to_display_score();
void paul_mode();

/*Main enter screen*/
int main() {
    UINT16 *current_buffer = (UINT16 *) get_video_base();
    Vector orig_vbl_vector;
    CURSOR_STATUS  user_input = NO_SELECTION;

    render_splash_screen(current_buffer);
    init_keyboard_isr();
    orig_vbl_vector = install_vector(VBL_VECTOR_NUM, vbl_isr);
    enable_mouse();

    while(user_input != SELECTED_EXIT) {
        if(user_input == SELECTED_PAUL_MODE) {
            disable_mouse();
            play_select_sound();
            paul_mode();
            enable_mouse();
            render_splash_screen(current_buffer);
        } else if(user_input == SELECTED_1_PLAYER) {
            disable_mouse();
            play_select_sound();
            main_game_loop();
            enable_mouse();
            render_splash_screen(current_buffer);
        }

        if(render_request == 1) {
            render_mouse(current_buffer);
            render_request = 0;
        }
        user_input = get_user_mouse_input();
    }
    
    install_vector(VBL_VECTOR_NUM, orig_vbl_vector);
    restore_keyboard_isr();
  
    
    return 0;
}




/*********************************************************
 * Purpose: Executes the main game loop
 *
 * Details:
 * - The function initializes the game state and manages the main game loop until a fatal collision occurs or the
 *   game reaches its final state.
 * - Utilizes global variables to track the state of the game - is_main_game_running, fatal_collision, game_state,
 *   render_request. They must be reset at the start of each play through
 * - Enable keyboard must be called for user input and the key board must be disabled after the user has either
 *   collided or reached max game state
 * - Upon a fatal collision, plays an explosion sound and animation, then displays the score.
 *   If the game completes without a fatal collision, it triggers the final victory animation.
 *********************************************************/

void main_game_loop() {

    UINT32 *back_buffer, *front_buffer, *current_buffer;  
    short num_times_ground_drawn = 0;
    
    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
    current_buffer = back_buffer;
    start_music();
  

    is_main_game_running = TRUE;
    fatal_collision = FALSE;
    game_state = 0;
    enable_keyboard();

    while (fatal_collision == FALSE && game_state < MAX_GAME_STATE) {
        if(user_pressed_space() == TRUE) {
            jump_request(&model, 0);
        }

        if (render_request == 1) {
            render(&model, current_buffer, &num_times_ground_drawn);
            set_video_base(current_buffer);
            switch_buffers(&current_buffer, front_buffer, back_buffer);
            render_request = 0;
       }

    }
 
    is_main_game_running = FALSE;
    disable_keyboard();

    if(fatal_collision == TRUE) {
   
        play_explosion_sound();
    
        fatal_Collision_animation(back_buffer, front_buffer,current_buffer, &model, &num_times_ground_drawn);
        render_score(current_buffer, game_state -1 );
        set_video_base(current_buffer);
        delay_to_display_score();

    } else {
        final_victory_animation(back_buffer, front_buffer, current_buffer);
    }


    stop_sound();

    
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
    event_animation_running = TRUE; /*global in vbl isr*/

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



/*********************************************************
 * Purpose: Similar to the main game loop, but collisions won't cause the game to end
 *********************************************************/
void paul_mode() {
    UINT32 *back_buffer, *front_buffer, *current_buffer;
    short num_times_ground_drawn = 0;
    
    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
    start_music();
    current_buffer = back_buffer;

    /*these need to be set every time as they are global*/
    is_main_game_running = TRUE;    
    game_state = 0;
    enable_keyboard();

    while (game_state < MAX_GAME_STATE) {
        if(user_pressed_space() == TRUE) {
            jump_request(&model, 0);
        }

        if (render_request == 1) {
            render(&model, current_buffer, &num_times_ground_drawn);
            set_video_base(current_buffer);
            switch_buffers(&current_buffer, front_buffer, back_buffer);
            render_request = 0;
       }
    }

    is_main_game_running = FALSE;
    disable_keyboard();
    stop_sound();

    final_victory_animation(back_buffer, front_buffer, current_buffer);

    set_video_base(front_buffer);


}



/*********************************************************
 * Purpose: Executes the animation of a final victory scene in a game
 *          Animates a final victory scene by cycling through victory images on the game display.
 *********************************************************/
void final_victory_animation(UINT32* back_buffer, UINT32* front_buffer, UINT32* current_buffer){
    short animation_frame_counter; /* Used to loop the animation 10 times*/
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

















