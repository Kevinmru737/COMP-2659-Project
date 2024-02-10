#include "models.h"

/*
Initiates the jump sequence for the player
*/
void jump(Player * player) {

	player->is_jumping = TRUE;
	player->vert_vel = 5;

}


/* 
   Moves the player in the vertical direction by updating its y position
   with its vertical velocity
*/
void move_player(Player * player) {
	player->top_left.y_pos += (player->vert_vel);
	player->top_right.y_pos += (player->vert_vel);
	player->bot_left.y_pos += (player->vert_vel);
	player->bot_right.y_pos += (player->vert_vel);
	(player->vert_vel)--;
}



/* 
Sets the jump property to false to stop the player's jump sequence
*/
void stop_jump(Player * player) {

	player->is_jumping = FALSE;
	player->vert_vel = 0;
}


/* 
Moves the triangle in the horizontal left direction
*/
void move_triangle_obs(Triangle* triangle) {

	triangle->bot_left.x_pos += triangle->hor_vel;
	triangle->top.x_pos += triangle->hor_vel;
	triangle->bot_right.x_pos += triangle->hor_vel;
}



/* 
Moves the platform in the horizontal left direction
*/
void move_platform_(Platform* platform) {

	platform->top_left.x_pos += platform->hor_vel;
	platform->top_right.x_pos += platform->hor_vel;

	platform->bot_left.x_pos += platform->hor_vel;
	platform->bot_right.x_pos += platform->hor_vel;

};



/*Constructor for creating an instance of player
  the player is 32 * 32 , so we only need its top left (hotspot) 
   to set other properties. Subtracting and adding by 31 because
   of inclusivity*/
Player* create_player(int x, int y) {
	Player* new_player;

	new_player->top_left.x_pos = x;
	new_player->top_left.y_pos = y;

	new_player->top_right.x_pos = x + 31;
	new_player->top_right.y_pos = y;

	new_player->bot_left.x_pos = x;
	new_player->bot_left.y_pos = y - 31;

	new_player->bot_right.x_pos = x + 31;
	new_player->bot_right.y_pos = y - 31;

	new_player->vert_vel = 0;
	new_player->is_jumping = FALSE;

	return new_player;
}

/*Constructor for creating an instance of triangle obstacle.
The given x and y cordinate are for the bottom left vertex of the triangle.
The height and width of the each triangle will be same, 16 and 32 respectivly.
*/
Triangle* create_triangle(int x, int y, int hor_vel) {

	Triangle* new_triangle;

	new_triangle->slope = 2;

	new_triangle->bot_left.x_pos = x;
	new_triangle->bot_left.y_pos = y;

	new_triangle->top.x_pos = x + 16;
	new_triangle->top.y_pos = y + 32;
	
	new_triangle->bot_right.x_pos = x + 32;
	new_triangle->bot_right.y_pos = y;

	new_triangle->hor_vel = hor_vel;
	return new_triangle;
}


/*Constructor for creating an instance of platform obstacle.
The given x and y cordinate are for the top left  vertex of the paltform.
*/
Platform* create_platform(int x_top_left, int y_top_left, int width, int height, int hor_vel) {

	Platform* new_paltform;

	new_paltform->top_left.x_pos = x_top_left;
	new_paltform->top_left.y_pos = y_top_left;

	new_paltform->bot_left.x_pos = x_top_left;
	new_paltform->bot_right.y_pos = y_top_left - height;


	new_paltform->top_right.x_pos = x_top_left + width;
	new_paltform->top_right.y_pos = y_top_left;

	new_paltform->bot_right.x_pos = x_top_left + width;
	new_paltform->bot_right.y_pos = y_top_left - height;

	new_paltform->hor_vel = hor_vel;
	return new_paltform;
}

