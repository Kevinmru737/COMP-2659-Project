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
#include <osbind.h>


UINT32 get_time();
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
UINT8 allocated_buffer[32260];
void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, Model *model, bool *is_curr_buffer_front);


int main() {
	
	Model  model;
    UINT32 time_then, time_now, time_elapsed;
    UINT32 time_elapsed_melody = 0,
		 time_elapsed_base = 0;

    UINT8 game_state = 0;
    UINT32 *back_buffer, *front_buffer;
	short player_num = 0;
    bool is_curr_buffer_front = TRUE, fatal_collision = FALSE;
	char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    int user_quit = FALSE;
	

	time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, allocated_buffer);
	start_music();

    while (user_quit == FALSE && fatal_collision == FALSE) {
     
		if(ch == ' ') {
			jump_request(&model, 0);
		}

	
		time_now = get_time();
		time_elapsed = time_now - time_then;

		if (time_elapsed > 1) {
			
			update_level(&model,&game_state);
			update_game_objects(&model, &fatal_collision);
			fatal_collision = player_fatal_collision(&model, player_num);
	
			if(is_curr_buffer_front == TRUE) {
				render(&model, back_buffer);
				set_video_base(back_buffer);
				is_curr_buffer_front = FALSE;
			} else {
				render(&model, front_buffer);
				set_video_base(front_buffer);
				is_curr_buffer_front = TRUE;
			}

			Vsync();

			time_then = time_now;
			time_elapsed_base++;
			time_elapsed_melody++;
			update_music(&time_elapsed_melody, &time_elapsed_base);

		}

		ch = NO_INP_CHAR;
        user_input(&ch);
		user_quit = (ch == '\033');
		
	}

	if(fatal_collision == TRUE) {
		play_explosion_sound();
		fatal_Collision_animation(back_buffer, front_buffer,&model, &is_curr_buffer_front);
	}
	while(!Cconis());

	set_video_base(front_buffer);
	stop_sound();
    return 0;
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

    UINT32 address;
    UINT8 *temp = back_buffer_array;

    while(1) {
        address = (UINT32) temp;
        address &= 0xff;
        if(address == 0) {
            break;
        }
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
 * Output: Animates a fatal collision by cycling through explosion images on the game display. Modifies the is_curr_buffer_front flag to reflect the current active buffer.
 *********************************************************/

void fatal_Collision_animation(UINT32* back_buffer, UINT32* front_buffer, Model *model, bool *is_curr_buffer_front) {
  
  UINT32 time_then, time_now,time_elapsed;
  short explosion_counter = 0;
  time_then  = get_time();

  while(explosion_counter < EXPLOSION_ANIMATION_TOTAL_FRAMES) {
	
	time_now  = get_time();
	time_elapsed = time_now - time_then;

	if(time_elapsed > 7) {
		
		if(*is_curr_buffer_front == TRUE) {
			render_explosion(model, back_buffer, explosion_counter);
			Setscreen(-1,back_buffer,-1);
			*is_curr_buffer_front = FALSE;
		} else {
			render_explosion(model, front_buffer, explosion_counter);
			Setscreen(-1,front_buffer,-1);
			*is_curr_buffer_front = TRUE;
		}

		Vsync();
		time_then = time_now;
		explosion_counter++;

	}
  }


}

