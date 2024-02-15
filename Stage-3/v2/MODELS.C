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




