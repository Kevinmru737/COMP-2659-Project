/*Author: Kevin and Depanshu*/

#include "events.h"
#include "stdio.h"

#define INITIAL_JUMP_VELOCITY 30

/****************************** SYNCHRONOUS EVENTS ******************************/

/*********************************************************
 * Purpose: Moves all active triangles leftward on the screen.
 *
 * Input: Pointer to a Model struct
 * Output: Updated x positions of all active triangle vertices.
 *
 * Details: Iterates over each active triangle, moving its x position left by its velocity.
 * 			Triangles reaching the left edge are reinitialized to the right, with preserved y position and velocity.
 *			Uses a helper function move_a_single_active_triangle to move a single active triangle.
 *
 *******************************************************/

void move_all_active_triangles(Model *model) {
    short i = 0;
    for (i; i < model->num_active_triangles; i++) {
		move_a_single_active_triangle(model,i);
	
	}
}

/*********************************************************
 * Purpose: Moves a single active triangle.
 *
 * Input: Pointer to a Model struct, index of the triangle being moved
 * Output: The x position of the triangle is updated.
 *
 * Details: Moves the specified triangle left by its horizontal velocity. 
 *          Checks for collisions with players; if a collision occurs, the movement is stopped and the function returns early
 *
 *********************************************************/
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


/*********************************************************
 * Purpose: Moves all active platforms leftward on the screen.
 *
 * Input: Pointer to a Model struct
 * Output: Updated x positions of all active platform vertices.
 *
 * Details: Similar to triangle movement, but for platforms. Platforms reaching the left boundary are repositioned 
 * 			to the right, maintaining their y position and horizontal velocity. Also uses a helper function to move a single active platform
 *******************************************************/

void move_all_active_platforms(Model* model) {
    short i = 0;
     for (i; i < model->num_active_platforms; i++) {
        move_a_single_platform(model, i);
    }

}


/*********************************************************
 * Purpose: Moves a single active platform.
 *
 * Input: Pointer to a Model struct, index of the platform being moved
 * Output: The x position of the platform is updated.
 *
 * Details: Moves the specified platform left by its horizontal velocity. 
 *          Checks for unsafe collisions with players; if an unsafe collision occurs, and the function returns early
 *
 *********************************************************/
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

/*********************************************************
 * Purpose: Triggers a jump for a player if they are on safely on a ground or a platform.
 *
 * Input: Pointer to a Model struct, player index
 * Output: The vertical velocity of the player is updated if the player is player is safely on a surface or ground ; Does nothing otherwise
 *
 * Details: If the player is deemed safe on ground or platform, their vertical velocity is set to an initial jump velocity.
 *
 *********************************************************/

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


/*********************************************************
 * Purpose: Update Player Position on the y axis
 *
 * Input: Pointer to the game model structure
 * Output: Updates each active player's position by their velocity if they meet the conditions
 *
 * Details: This function iterates over all active players in the game model and updates
 *          their vertical positions based on their current vertical velocity and collision with ground/surface status
 *
 * Input: Pointer to the game model structure.
 * Output: Updates each active player's position if they are jumping or not on a safe surface AND did not have had a fatal collision.
 *********************************************************/
void move_all_active_players(Model *model) {
    short i = 0;
    for (i; i < model->num_active_players; i++) {
        if ((model->player[i].vert_vel != 0 || player_safe_on_ground_or_surface(model, i) == FALSE) && model->player[i].fatal_collision == FALSE  ) {
            move_one_player(model,i);
        }
    }
    
}



/*********************************************************
 * Purpose: Move a Single Player
 *
 * Input: Pointer to the game model structure, player numbe being moved
 * Output: Updates the specified player's vertical position and velocity.
 *
 * Details: This function iterates over all active players in the game model and updates
 *          their vertical positions based on their current vertical velocity and collision with ground/surface status.
 *			If a player collides with any other object the movement is stopped and the function returns early
 *
 *********************************************************/
void move_one_player(Model *model, short player_num) {
    short i = 0;

    /* how many steps to move the player, regardless of direction. */
    short move_step_count = model->player[player_num].vert_vel < 0 ?
						-(model->player[player_num].vert_vel) : (model->player[player_num].vert_vel);


    /*Move once at least since the jump request was granted,
	assumes move is immediately called after the jump request*/
    if(model->player[player_num].vert_vel == INITIAL_JUMP_VELOCITY) {
        update_player_pos(&model->player[player_num]);
        i++;
    }
		
	for(i; i < move_step_count; i++) {
			
	/*check for any collision to stop the movement*/
		if(player_safe_on_ground_or_surface(model, player_num) == TRUE || player_fatal_collision(model, player_num) == TRUE) {
			model->player[player_num].vert_vel = 0;
			return; /*player collided with an object, so exit early*/
        }
        update_player_pos(&model->player[player_num]);
    }
	
	
	/*check for collision since it won't be checked after the last step in the loop*/
	if(player_safe_on_ground_or_surface(model, player_num) == TRUE || player_fatal_collision(model, player_num) == TRUE) {
        model->player[player_num].vert_vel = 0;
        return;
    }
	

	/*Don't change velocity if it already equals the terminal velocity*/
	if (model->player[player_num].vert_vel <= -60) {
		return; 
	} else {
		if(model->player[player_num].vert_vel <= 0) {
			model->player[player_num].vert_vel -= 20; /*Descent speed*/
		} else{
		model->player[player_num].vert_vel -= 3; /*Ascent deceleration*/

		}
	}

}




