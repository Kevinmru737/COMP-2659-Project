#include "events.h"
#include "stdio.h"

#define INITIAL_JUMP_VELOCITY 15

/****************************** SYNCHRONOUS EVENTS ******************************/

/* Author: Kevin and Depanshu
 *
* Purpose: This event synchronously happens every screen refresh and moves
*          a all active platforms object right to left across the screen.
 *
 * Details: Utilizes a helper to handle individual triangle movement and collision
 *
 */
void move_all_active_triangles(Model *model) {
    short i = 0;
    for (i; i < model->num_active_triangles; i++) {
		move_a_single_active_triangle(model,i);
	
	}
}


/* Author: Depanshu
 *
 * Purpose: Moves a specified triangle based on its horizontal velocity.
 * 			Exits early if a collision with any player is detected.
 *
 */

void move_a_single_active_triangle(Model* model, short triangle_num) {
	short i = 0;
	short k;	
	for(i; i< model->triangles[triangle_num].hor_vel; i++){
		update_triangle_pos(&model->triangles[triangle_num]);
		
		for (k = 0; k < model->num_active_players; k++) {
			
			if (player_triangle_collision(&(model->player[k]), &(model->triangles[triangle_num])) == TRUE) {
				return;
			}
			
		}
		
	}

}




/* Author: Depanshu
 *
 * Purpose: This event synchronously happens every screen refresh and moves
 *          a all active platforms object right to left across the screen.
 *
 * Details:
 *   Calls a helper function to move each active platform
 *
 */
void move_all_active_platforms(Model* model) {
    short i = 0;
     for (i; i < model->num_active_platforms; i++) {
        move_a_single_platform(model, i);
    }

}


void move_a_single_platform(Model* model,short platform_number) {
	short i = 0;
	short k;	
	for(i; i< model->platform[platform_number].hor_vel; i++){
		update_platform_pos(&model->platform[platform_number]);
		
		for (k = 0; k < model->num_active_players; k++) {
			
			if ( platform_collision_unsafe(&(model->player[k]), &(model->platform[platform_number])) == TRUE) {
				return;
			}
			
		}
		
	}

}




/****************************** ASYNCHRONOUS EVENTS ******************************/
/* Author: Depanshu
 * Purpose: Triggers a jump for a player if they are on safely on a ground or a platform.
 *
 */

void jump_request(Model * model, short player_num) {

    if(player_safe_on_ground_or_surface(model, player_num) == TRUE) {
        model->player[player_num].vert_vel = INITIAL_JUMP_VELOCITY;
    }

}




void pause_request() {
    /* TBD*/
}

void quit_request() {
    /* Pressing ESC will close the entire game at any point. */
}






/******************************************** CONDITIONAL EVENTS ********************************************/



/* Author :Depanshu
 * Purpose: Moves all active players if they have non-zero vertical velocity or are not in contact with a safe surface.
 *
 */
void move_all_active_players(Model *model) {
    short i = 0;
    for (i; i < model->num_active_players; i++) {
        if (model->player[i].vert_vel != 0 || player_safe_on_ground_or_surface(model, i) == FALSE) {
            move_one_player(model,i);
        }
    }
    
}



/* Author: Depanshu
 * Purpose: Moves a single player based on their vertical velocity, checking for safe landing or fatal collisions.
 *
 */
void move_one_player(Model *model, short player_num) {
    short i = 0;

    /* how many steps to move the player, regardless of direction. */
    short move_step_count = model->player[player_num].vert_vel < 0 ? -(model->player[player_num].vert_vel):(model->player[player_num].vert_vel);

    /*Move once at least since the jump request was granted, assumes move is immediately called after the jump request*/
    if(model->player[player_num].vert_vel == INITIAL_JUMP_VELOCITY) {
        update_player_pos(&model->player[player_num]);
        i++;
    }

    for(i; i < move_step_count; i++) {
        if(player_safe_on_ground_or_surface(model, player_num) == TRUE || player_fatal_collision(model, player_num) == TRUE) {
            model->player[player_num].vert_vel = 0;
            return;
        }
        update_player_pos(&model->player[player_num]);

    }
	
	if(player_safe_on_ground_or_surface(model, player_num) == TRUE || player_fatal_collision(model, player_num) == TRUE) {
        model->player[player_num].vert_vel = 0;
        return;
    }
	

	/*Don't change velocity if it already equals the terminal velocity*/
	if (model->player[player_num].vert_vel == -10) {
		return; 
	} else {
		model->player[player_num].vert_vel--; 
	}

}




