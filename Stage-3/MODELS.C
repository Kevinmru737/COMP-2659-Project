#include "models.h"
#include "stdio.h"



/* Author: Depanshu and Kevin
 *
 * Purpose: Moves the player in the vertical direction by updating its y position
 *  		by a single unit. Moves "up" if the vertical velocity is positive, "down" otherwise
 *
 * Details: Although counter-intuitive to real-world physics/logic, subtraction of
 *			a vertical velocity increases the upwards position of the player 
 *			(as it would appear on screen) and vice versa.
 */
void update_player_pos(Player * player) {

    short player_move_direction = player->vert_vel > 0 ? -1: 1;

    (player->top_left.y_pos) += player_move_direction;
    (player->top_right.y_pos) += player_move_direction;
    (player->bot_left.y_pos) += player_move_direction;
    (player->bot_right.y_pos) += player_move_direction;

}


/* Moves the triangle in the horizontal left direction by a single unit
*/
void update_triangle_pos(Triangle* triangle) {
	(triangle->bot_left.x_pos)--;
	(triangle->top.x_pos)--; 
	(triangle->bot_right.x_pos)--; 
	(triangle->hot_spot.x_pos)--;

}

/* Moves the platform in the horizontal left direction by a single unit
*/
void update_platform_pos(Platform* platform) {
	(platform->top_left.x_pos)--;
	(platform->top_right.x_pos)--;
	(platform->bot_left.x_pos)--;
	(platform->bot_right.x_pos)--;

}



/* Author: Kevin
*
* Purpose:  Initializes a triangle instance with specified position and velocity
*
* Details: Even though the triangle does not have a top left corner. The triangle will be drawn
*			using a bitmap, so the hotspot  is the top left corner of the bitmap. The x and 
*			and y cordinates define this hotspot. All triangles will have fixed height and width.
*
* Restriction:
*		- No bounds checking is done so, user has to give valid parameters
*/
void initialize_triangle(int x, int y, short hor_vel, Triangle* new_triangle) {
	new_triangle->hot_spot.x_pos = x;
	new_triangle->hot_spot.y_pos = y;

	new_triangle->bot_left.x_pos = x;
	new_triangle->bot_left.y_pos = y + 31;

	new_triangle->bot_right.x_pos = x + 31;
	new_triangle->bot_right.y_pos = y + 31;

	new_triangle->top.x_pos = x + 15;
	new_triangle->top.y_pos = y;

	new_triangle->hor_vel = hor_vel;
}



/* Author: Kevin
*
* Purpose:  Initializes a paltform instance with specified position and velocity
*
* Details: The x and y position define the top left corner of the platform's bounding box.
*		   The width and height define how many pixels wide and how many scan line does the
*		   the platfrom cover respectively
*
* Restriction:
*		- No bounds checking is done so, user has to give valid parameters
*		- The box in the game is assumed to be at least one long(32 pixels) wide
* 		  and 2 scan line long. So the width must be at least 32 and height must be at least 2 for
*	      correct behaviour.
*/
void initialize_platform(int x, int y, int width, int height, int hor_vel, Platform* new_platform) {
	new_platform->top_left.x_pos = x;
	new_platform->top_left.y_pos = y;

	new_platform->top_right.x_pos = x + (width - 1);
	new_platform->top_right.y_pos = y;

	new_platform->bot_left.x_pos = x;
	new_platform->bot_left.y_pos = y + (height - 1);

	new_platform->bot_right.x_pos = x + (width - 1);
	new_platform->bot_right.y_pos = y + (height - 1);

	new_platform->hor_vel = hor_vel;
}


/* Author: Kevin
*
* Purpose:  Initializes a ground instance with specified position and velocity
*
*/
void initialize_ground(int y, Ground* ptr_ground) {
	ptr_ground->y_pos = y;
}



/* Author: Kevin and Depanshu
*
* Purpose: Initializes a player instance with specified position and velocity
*
* Details: The player's initial position is determined by the x and y parameters, which define the top-left corner
*   	   of the player's bounding box. The player is assumed to have a square bounding box with a size of 32x32 pixels
*   	   (hence the addition of 31 pixels to x and y for bottom and right sides).
*
* Restriction:
*  No bounds checking is done, only permissible values of x and y are allowed:
*  0 <= x < 640
*  0 <= y < 400
*/
void initialize_player(int x, int y, Player* player) {
	player->top_left.x_pos = x;
	player->top_left.y_pos = y;
	player->top_right.x_pos = x + 31;
	player->top_right.y_pos = y;
	player->bot_left.x_pos = x;
	player->bot_left.y_pos = y + 31;
	player->bot_right.x_pos = x + 31;
	player->bot_right.y_pos = y + 31;

	player->vert_vel = 0;
	player->fatal_collision = FALSE;

}



/* Author: Depanshu
* Purpose: Performs a collision check between the player and the triangle object
*
* Details: This function  first does a "gross" collision check, if determined
*           that the player is inside triangle's 32 x 32 box, it will call a helper function to
*           do a collision check
*
*/
bool player_triangle_collision( Player* player , Triangle * triangle){
    
    if( triangle->bot_left.x_pos > player->bot_right.x_pos ||     /*triangle is way off right of the player */ 
        player->bot_left.x_pos > triangle->bot_right.x_pos ||    /*triangle is way off left of the player */ 
        player->top_right.y_pos > triangle->bot_left.y_pos ||    /*triangle is above the player */ 
        triangle->top.y_pos > player->bot_left.y_pos   )         /*triangle is below the player */ 
         {

            return FALSE;
        }

    return player_triangle_collision_helper(player, triangle);

}




/* Author: Depanshu
*
* Purpose: To check if a player has collided with a triangle
 * 
 * Details: This method calculates the expected Y positions on the triangle's hypotenuse from two reference points:
 *       	1. `y_on_hypotenuse_from_bot_left`: Expected Y position on the hypotenuse for the player's bottom right edge, calculated from the triangle's bottom left vertex.
 *       	2. `y_on_hypotenuse_from_top`: Expected Y position on the hypotenuse for the player's bottom left edge, calculated from the triangle's top vertex.
 *
 
 *   - Collision cases:
 *       1. The player's bottom right edge aligns with or crosses the hypotenuse extending upwards from the triangle's bottom left vertex.
 *       2. The player's bottom left edge aligns with or crosses the hypotenuse extending downwards from the triangle's top vertex.
 *       3. Any point on the player's bottom edge directly aligns with the triangle's top vertex, indicating a collision at the peak.
 *
 */
bool player_triangle_collision_helper( Player* player , Triangle * triangle) {

    int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
	
	/*Case 1*/
    if(player->bot_right.x_pos >= triangle->bot_left.x_pos && player->bot_right.x_pos <= triangle->bot_left.x_pos + 15) {
		y_on_hypotenuse_from_bot_left = -2 * (player->bot_right.x_pos - triangle->bot_left.x_pos) + triangle->bot_left.y_pos;

		if (y_on_hypotenuse_from_bot_left <= player->bot_right.y_pos) {
			player->fatal_collision = TRUE;
			return TRUE;
		}
	}

	/*Case 2*/
	if(player->bot_left.x_pos >= triangle->bot_left.x_pos + 15 && player->bot_left.x_pos <= triangle->bot_right.x_pos) {
		 y_on_hypotenuse_from_top = 2 * (player->bot_left.x_pos - triangle->top.x_pos) + triangle->top.y_pos;

		if (y_on_hypotenuse_from_top >= player->bot_left.y_pos) {
			player->fatal_collision = TRUE;
			return TRUE;
		}
	}



	/*Case 3*/
    if( player->bot_left.y_pos == triangle->top.y_pos &&
        player->bot_right.x_pos >= triangle->top.x_pos &&
        player->bot_left.x_pos <= triangle->top.x_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }

    /* No collision occurred */
    return FALSE;

}




/* Author: Kevin
 *
 * Purpose: Checks for whehter the top edge of the ground and bottom edge of player are in contact
 *
 * Details:
 *   Returns TRUE if a collision was detected and FALSE if there is no collision.
 *
 * Restrictions: 
 *   y position comparisons are based on the bit positions as they would appear
 *   on screen.
 */
bool ground_collision(Player* player, Ground* ground) {
    if (player->bot_left.y_pos >=  ground->y_pos) {
        return TRUE;
    }
    return FALSE;
}



/* Author: Kevin
 *
 * Purpose: Checks for whether the player has collided unsafely with the platform
 *
 * Details:
 *   Returns TRUE if an unsafe collision was detected and FALSE if there
 *   is no collision.
 *   -TRUE means the player has had an UNSAFE collision and death should occur
 *   -FALSE means the player has not yet had an unsafe collision with a platform.
 *
 * Restrictions: 
 *   x and y position comparisons are based as they would
 *   appear on screen. 'Moving down' increases y and vice versa.
 */
bool platform_collision_unsafe(Player* player, Platform* platform) {

    /*Checking if the top edge of player and bottom edge of platform collided*/
    if( player->top_left.y_pos == platform->bot_right.y_pos &&
        player->top_right.x_pos >= platform->bot_left.x_pos &&
        platform->bot_right.x_pos >= player->top_left.x_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }

    /*Checking if the right edge of player and left edge of platform collided*/
    if( player->top_right.x_pos ==  platform->top_left.x_pos &&
        platform->top_left.y_pos >= player->top_right.y_pos  &&
        player->bot_right.y_pos >= platform->top_left.y_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }


    /* No collision was detected*/
    return FALSE;
}






/* Author: Kevin
 *
 * Purpose: Checks if the platform collided safely with the player
 *
 * Details:
 *   Returns TRUE if a safe collision was detected and FALSE if there
 *   is no collision.
 *
 * Restrictions: 
 *   x and y position comparisons are based as they would
 *   appear on screen. 'Moving down' increases y and vice versa.
 */
bool platform_collision_safe(Player* player, Platform* platform) {

    /*Checking if player's bottom edge is on top of the platform's top edge*/
    if(player->bot_right.y_pos == platform->top_left.y_pos &&
        player->bot_right.x_pos > platform->top_left.x_pos &&
        player->bot_left.x_pos <= platform->top_right.x_pos) {
            return TRUE;
    }

    return FALSE;
}






/* Author: Kevin
 *
 * Purpose: Checks if the player collided  with the victory wall
 *
 * Details:
 *   Returns TRUE if a collision was detected and FALSE if there is no collision.
 *   -TRUE means the player has won and the victory screen should be shown.
 *   -FALSE means the player has not yet collided with the victory_wall but does
 *   not cause death.
 *
 * Restrictions: 
 *  x and y position comparisons are based as they would
 *  appear on screen. 'Moving down' increases y and vice versa.
 */
bool victory_collision(Player* player, Victory_Wall* victory_wall) {
    if (player->bot_right.x_pos >= victory_wall->top_left.x_pos) {
            return TRUE;
        }
    return FALSE;
}






/*  Author: Depanshu
 *  Purpose: Checks if the player is on the ground or a platform based on collisions.
 *
 * Details: Evaluates collision detection between the player and the ground or any active platforms.
 *          Returns true if a safe collision is detected, false otherwise.
 *
 */
bool player_safe_on_ground_or_surface(Model *model, short player_num) {
    short i = 0;
    if ( ground_collision( &(model->player[player_num]), &(model->ground) ) ) {
        return TRUE;
    }

    for( i; i < model->num_active_platforms; i++) {
        if( platform_collision_safe(&model->player[player_num], &model->platform[i] ) == TRUE) {
            return TRUE;
        }
    }

    return FALSE;
}





/* Author: Depanshu
 * Purpose: Checks for fatal collisions between a specific player and either triangles or platforms.
 *
 * Details: Uses a helper functions to assess collisions separately and returns true if either type of collision occurs.
 *
*/
bool player_fatal_collision(Model *model, short player_num) {

	return has_player_collided_with_any_triangle(model, player_num) || has_player_collided_with_any_platform(model, player_num);

}


/* Author: Depanshu
* Purpose: Checks for fatal collisions between the specified player and all active triangles 
*
*/

bool has_player_collided_with_any_triangle(Model *model, short player_num){
	
	short i = 0;

    for( i; i < model->num_active_triangles; i++) {
        if( player_triangle_collision(&model->player[player_num], &model->triangles[i] ) == TRUE) {
            return TRUE;
        }
    }
	
	return FALSE;

}

/* Author: Depanshu
 * Purpose: Checks for fatal collisions between the specified player and all active platform 
 *
*/

bool has_player_collided_with_any_platform(Model *model, short player_num){
	short i = 0;
	for( i; i < model->num_active_platforms; i++) {
        if( platform_collision_unsafe(&model->player[player_num],&model->platform[i] ) == TRUE) {
            return TRUE;
        }
    }
	
	return FALSE;
}