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
	new_player->top_left.x_pos = x;
	new_player->top_left.y_pos = y;
	new_player->top_right.x_pos = x + 31;
	new_player->top_right.y_pos = y;
	new_player->bot_left.x_pos = x;
	new_player->bot_left.y_pos = y + 31;
	new_player->bot_right.x_pos = x + 31;
	new_player->bot_right.y_pos = y + 31;

	new_player->vert_vel = 0;
	new_player->is_jumping = FALSE;
	return new_player;
}
/* Author: Depanshu
 *
 * Purpose: Sets the appropriate conditions to simulate a player's initial
 *			jump conditions.
 */
void jump(Player* player) {
	player->is_jumping = FALSE;
	player->is_jumping = TRUE;
	player->vert_vel = 5; 

}


/* Author: Depanshu
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
}



/* Moves the platform in the horizontal left direction
*/
void move_platform(Platform* platform) {

	platform->top_left.x_pos -= platform->hor_vel;
	platform->top_right.x_pos -= platform->hor_vel;

};

/*
	Creates a Triangle object at a specfied x and y value and returns it
*/

<<<<<<< HEAD
void initialize_triangle(int x, int y, int hor_vel, Triangle* new_triangle) {
=======
Triangle* create_triangle(int x, int y, int hor_vel) {
	Triangle triangle;
	Triangle* new_triangle = &triangle;
>>>>>>> stage-3-kevins-changes
	new_triangle->hot_spot.x_pos = x;
	new_triangle->hot_spot.y_pos = y;

	new_triangle->bot_left.x_pos = x;
	new_triangle->bot_left.y_pos = y + 31;

	new_triangle->bot_right.x_pos = x + 31;
	new_triangle->bot_right.y_pos = y + 31;

	new_triangle->top.x_pos = x + 15;
	new_triangle->top.y_pos = y;

	new_triangle->hor_vel = hor_vel;

	return new_triangle;
}



/* Author: Kevin
 *
 * Purpose: Creates a Platform object, initializes it and returns it.
 *
 * Details: ......TBA
 *
 */
<<<<<<< HEAD
void initialize_platform(int x, int y, int width, int height, int hor_vel, Platform* new_platform) {
=======
Platform* create_platform(int x, int y, int width, int height, int hor_vel) {
	Platform platform;
	Platform* new_platform = &platform;
	
>>>>>>> stage-3-kevins-changes
	new_platform->top_left.x_pos = x;
	new_platform->top_left.y_pos = y;

	new_platform->top_right.x_pos = x + (width - 1);
	new_platform->top_right.y_pos = y;

	new_platform->bot_left.x_pos = x;
	new_platform->bot_left.y_pos = y + (height - 1);

	new_platform->bot_right.x_pos = x + (width - 1);
	new_platform->bot_right.y_pos = y + (height - 1);

	new_platform->hor_vel = hor_vel;
	return new_platform;
}

Ground* create_ground(int y) {
	Ground* ptr_ground;

	
	ptr_ground->y_pos = y;

	return ptr_ground;
}