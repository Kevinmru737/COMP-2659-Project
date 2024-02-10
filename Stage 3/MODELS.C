#include "models.h"

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
	return new_player;
}
void jump(Player * player) {

	player->is_jumping = TRUE;
	player->vert_vel = 5;

}
/* Moves the player in the vertical direction by updating its y position
   with its vertical velocity
*/
void move_player(Player * player) {
	player->top_left.y_pos += (player->vert_vel);
	player->top_right.y_pos += (player->vert_vel);
	player->bot_left.y_pos += (player->vert_vel);
	player->bot_right.y_pos += (player->vert_vel);
	(player->vert_vel)--;
}

/* Sets the jump property to false to stop the player's jump sequence
*/
void stop_jump(Player * player) {

	player->is_jumping = FALSE;
	player->vert_vel = 0;
}
/* Moves the triangle in the horizontal left direction
*/
void move_triangle_obs(Triangle* triangle) {

	triangle->bot_left.x_pos += triangle->hor_vel;
	triangle->top.x_pos += triangle->hor_vel;
	triangle->bot_right.x_pos += triangle->hor_vel;
}



/* Moves the platform in the horizontal left direction
*/
void move_platform_(Platform* platform) {

	platform->top_left.x_pos += platform->hor_vel;
	platform->top_right.x_pos += platform->hor_vel;

};

