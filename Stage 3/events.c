#include "types.h"
#include "models.h"
#include <stdio.h>

void spawn_triangle(int x, int y) {

}

void spawn_platform(int x, int y) {

}

void player_death() {

}

void player_victory() {

}

void player_jumping(Player* player) {
    jump(player);
    while (player->top_left.y_pos > 250) {
        move_player(player);
    }
    stop_jump(player);
}



