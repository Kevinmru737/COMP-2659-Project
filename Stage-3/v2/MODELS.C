#include "models.h"



/* Author: Depanshu
 *
 * Purpose: Sets the appropriate conditions to simulate a player's initial
 *			jump conditions.
 */
void jump(Player* player, int vert_velocity) {
	player->is_jumping = TRUE;
	player->vert_vel = vert_velocity;

}



/* Author: Depanshu and Kevin
 *
 * Purpose: Moves the player in the vertical direction by updating its y position
 *  		with its vertical velocity
 *
 * Details: Although counter-intuitive to real-world physics/logic, subtraction of
 *			a vertical velocity increases the upwards position of the player 
 *			(as it would appear on screen) and vice versa.
 */
void move_player_vert(Player * player) {
    player->top_left.y_pos -= (player->vert_vel);
    player->top_right.y_pos -= (player->vert_vel);
    player->bot_left.y_pos -= (player->vert_vel);
    player->bot_right.y_pos -= (player->vert_vel);
			
    /* Dont change if the vertical velocity == terminal( ie -5) */
    if (player->vert_vel >= -5) {
        (player->vert_vel)--;
    }

}



/* Sets the jump property to false to stop the player's jump sequence
*/
void stop_jump(Player * player) {
	player->is_jumping = FALSE;
	player->vert_vel = 0;
}



/* Moves the triangle in the horizontal left direction
*/
void move_triangle(Triangle* triangle) {
	triangle->bot_left.x_pos -= triangle->hor_vel;
	triangle->top.x_pos -= triangle->hor_vel;
	triangle->bot_right.x_pos -= triangle->hor_vel;
	triangle->hot_spot.x_pos -= triangle->hor_vel;
}



/* Moves the platform in the horizontal left direction
*/
void move_platform(Platform* platform) {
	platform->top_left.x_pos -= platform->hor_vel;
	platform->top_right.x_pos -= platform->hor_vel;
	platform->bot_left.x_pos -= platform->hor_vel;
	platform->bot_right.x_pos -= platform->hor_vel;

};



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
void initialize_triangle(int x, int y, int hor_vel, Triangle* new_triangle) {
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
void initialize_player(int x, int y, Player* player, int vert_vel) {
	player->top_left.x_pos = x;
	player->top_left.y_pos = y;
	player->top_right.x_pos = x + 31;
	player->top_right.y_pos = y;
	player->bot_left.x_pos = x;
	player->bot_left.y_pos = y + 31;
	player->bot_right.x_pos = x + 31;
	player->bot_right.y_pos = y + 31;

	player->vert_vel = vert_vel;
	player->is_jumping = FALSE;
}



/* Author: Depanshu
* Purpose: Performs a preliminary collision check between a player and a triangle.
*
* Details: This function  determines if a detailed collision check is necessary
*          by comparing the  positions of the player and triangle, allowing for early
*          exit in clear no-collision cases. If a potential collision is detected,
*          it calls `player_triangle_collison_helper` to check if a collision has occurred
*
*/
bool player_triangle_collison( Player* player , Triangle * triangle){
    
    if( triangle->bot_left.x_pos > player->bot_right.x_pos ||     /*triangle is way off right of the player */ 
        player->bot_left.x_pos > triangle->bot_right.x_pos ||    /*triangle is way off left of the player */ 
        player->top_right.y_pos > triangle->bot_left.y_pos ||    /*triangle is above the player */ 
        triangle->top.y_pos > player->bot_left.y_pos   )         /*triangle is below the player */ 
         {

            return FALSE;
        }

    return player_triangle_collison_helper(player, triangle);

}




/* Author: Depanshu
*
* Purpose: This function checks for collision between a player and a triangle.
*
* Details:
*   - Returns TRUE if a collision was detected and FALSE if there is no collision.
*   - The triangle is represented by three lines, and collision can occur along its two diagonal lines.
*   - The slopes of the diagonal lines have been calculated to be 2 and -2 from the bitmap data.
*   - There are three possible collision scenarios:
*       1: The bottom-right edge of the player collides with the diagonal line from the bottom-left vertex of the triangle.
*       2: Any point on the entire bottom edge (line) of the player can collide with the top vertex of the triangle.
*       3: The bottom-left edge of the player collides with the diagonal line from the top vertex of the triangle.
*
*/
bool player_triangle_collison_helper( Player* player , Triangle * triangle) {

    int y;

    /*Check if player is along the right diagnol line towards vertex */
    y = -2 * (player->bot_right.x_pos - triangle->bot_left.x_pos) + triangle->bot_left.y_pos;

    if (y == player->bot_right.y_pos) {
        return TRUE;
    }

    /*Check if player is along the downward diagnol line from the vertex*/
    y = 2 * (player->bot_left.x_pos - triangle->top.x_pos) + triangle->top.y_pos;

    if (y == player->bot_right.y_pos) {
        return TRUE;
    }

    /*Check if player is bottom edge of the player collides with  the top vertex of the triangle*/
    if( player->bot_left.y_pos == triangle->top.y_pos &&
        player->bot_right.x_pos >= triangle->top.x_pos &&
        player->bot_left.x_pos <= triangle->top.x_pos) {
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
 * Purpose: Cheks for whether the player has collided unsafely with the platform
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

    /*Checking if the top edge of player and bottom edge of platfrom collided*/
    if( player->top_left.y_pos == platform->bot_right.y_pos &&
        player->top_right.x_pos >= platform->bot_left.x_pos &&
        platform->bot_right.x_pos >= player->top_left.x_pos) {
            return TRUE;
        }

    /*Checking if the right edge of player and left edge of platfrom collided*/
    if( player->top_right.x_pos ==  platform->top_left.x_pos &&
        platform->top_left.y_pos >= player->top_right.y_pos  &&
        player->bot_right.y_pos >= platform->top_left.y_pos) {
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
            stop_jump(player);
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







/* Author: Depanshu
*
* Purpose: Checks if the player is not falling based on collisions with the ground and platforms.
*
* Details: This function determines whether the player is currently in a state where they are not falling.
*          It checks for collisions between the player and the ground, as well as collisions with active platforms,
*          and returns TRUE if any collision is detected, indicating that the player is not falling.
*
*/
bool is_player_not_falling(Model *model, short player_num) {
    int i = 0;

    if ( ground_collision( &(model->player[player_num]), &(model->ground) ) ) {
        stop_jump(&model->player[player_num]);
        return TRUE;
    }

    for( i; i < model->num_active_platforms; i++) {
        if( platform_collision_safe(&model->player[player_num], &model->platform[i] ) == TRUE) {
             stop_jump(&model->player[player_num]);
            return TRUE;
        }
    }

    return FALSE;
}
