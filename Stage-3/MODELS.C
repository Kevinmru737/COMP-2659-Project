#include "models.h"



/* Author: Kevin and Depanshu
 * Purpose: Constructs an instance of the player, initializes it, and returns it.
 *
 * Details:
 *   Initializes the player, all values taken as input and those initialized
 *	 are assuming the bit position as it would be represented on screen.
 *   (on a 640 x 400 bit per pixel raster graphic screen).
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
	player->is_jumping = FALSE;
}




/* Author: Depanshu
 *
 * Purpose: Sets the appropriate conditions to simulate a player's initial
 *			jump conditions.
 */
void jump(Player* player) {
	player->is_jumping = TRUE;
	player->vert_vel = 5; 

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
void move_player(Player * player) {
	if (player->is_jumping == TRUE) {
			player->top_left.y_pos -= (player->vert_vel);
			player->top_right.y_pos -= (player->vert_vel);
			player->bot_left.y_pos -= (player->vert_vel);
			player->bot_right.y_pos -= (player->vert_vel);
			
			/* Dont change if the vertical velocity == terminal( ie -5) */
			if (player->vert_vel >= -5) {
				(player->vert_vel)--;
			}
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

/*
Creates a Triangle object at a specfied x and y value and returns it
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
 * Purpose: Creates a Platform object, initializes it and returns it.
 *
 * Details: ......TBA
 *
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



