/*
* Main game loop
*/
#include "input.h"
#include "models.h"
#include "events.h"
#include "render.h"
#include "bool.h"
#include "stdio.h"
#define NO_INP_CHAR '\0'


UINT32 get_time();
void intit_starting_model(Model* model);



int main() {
	Model  model;
    UINT32 time_then, time_now, time_elapsed;
	UINT32* base = Physbase();
	bool was_ground_drawn = FALSE;
	char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    int user_quit = FALSE; 


	intit_starting_model(&model);
	time_then = get_time();
		
    while (user_quit == FALSE) {
		if(ch == ' ') {
			jump_request(&model, 0);
		}
		
		time_now = get_time();
		time_elapsed = time_now - time_then;
		
		if (time_elapsed > 1) {
			move_all_active_triangles(&model);
			move_all_active_platforms(&model);
			move_all_active_players(&model);
			render(&model, base, &was_ground_drawn);

			if(model.player[0].fatal_collision == TRUE) {
				break;
			}
			
			time_then = time_now;
		}
		
		ch = NO_INP_CHAR;
        user_input(&ch);
		user_quit = (ch == '\033');
		
	}

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
 * Purpose: Initialize Starting Game Model
 *
 * Details: This function initializes the model values with predefined values as chosen by the user
 *
 * Input:  Pointer to the game model (Model* model) to be initialized.
 * Output: The game model is modified to reflect the initial game state with
 *         predefined entities and their attributes.
 *
 *********************************************************/
void intit_starting_model(Model* model) {
	
	model->num_active_players = 1;
	model->num_active_triangles = 1;
	model->num_active_platforms = 0;
	
	initialize_ground( 271, &( model->ground ) );
	
	initialize_player( 45, 271 - 31, &( model->player[0] ) );
	
	initialize_triangle(640-32, 271 - 31, 8, & ( model->triangles[0] ) );
	
	initialize_platform(640-64 , 271 - 64, 64, 32, 5, & ( model->platform[0] ) );
	
}


