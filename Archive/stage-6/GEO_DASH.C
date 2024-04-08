/*
* Main game loop
*/
#include "input.h"
#include "models.h"
#include "events.h"
#include "render.h"
#include "bool.h"
#include "level.h"
#include <osbind.h>

#define NO_INP_CHAR '\0'


UINT32 get_time();
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]);
UINT8 allocated_buffer[32260];




int main() {
	
	Model  model;
    UINT32 time_then, time_now,time_elapsed;
    UINT8 game_state = 0;
    UINT32 *back_buffer, *front_buffer;
    UINT32* orig_buffer = Physbase();
	short player_num = 0;
    bool is_curr_buffer_front = TRUE, fatal_collision = FALSE;
	char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    int user_quit = FALSE;

	time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, orig_buffer, allocated_buffer);


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
				Setscreen(-1,back_buffer,-1);
				is_curr_buffer_front = FALSE;
			} else {
				render(&model, front_buffer);
				Setscreen(-1,front_buffer,-1);
				is_curr_buffer_front = TRUE;
			}
				
			Vsync();              
			time_then = time_now;
				
		}

		ch = NO_INP_CHAR;
        user_input(&ch);
		user_quit = (ch == '\033');
		
	}

    Setscreen(-1, orig_buffer, -1);

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
 * 			 front buffer pointer is set to point to the original buffer
 *
 * Input:  Back buffer, front buffer and the original true buffer
 * Output: Modifies the back buffer to point to a 256 byte aligned address in back_buffer_array and changes the address stored at front buffer to orig_buffer
 *
 *********************************************************/
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]) {

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

    *back_buffer =	(UINT32*)temp;
    *front_buffer = orig_buffer;
}

