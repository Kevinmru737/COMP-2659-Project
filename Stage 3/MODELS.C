#include "models.h"


void jump(Player * player) {

	player->is_jumping = TRUE;
	player->vert_vel = 5;

}

void move_player(Player * player) {
	
	(player->y_pos) += (player->vert_vel)--;

}


void stop_jump(Player * player) {

	player->is_jumping = FALSE;
	player->vert_vel = 0;
}


void move_triangle_obs(Triangle* triangle) {

	triangle->x_pos +=triangle->hor_vel;
}

void move_platform_(Platform* platform) {

	platform->x_pos += platform->hor_vel;
}

