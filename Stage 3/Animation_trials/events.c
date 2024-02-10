#include "types.h"
#include "models.h"
#include "events.h"

void spawn_triangle(int x, int y) {

}

void spawn_platform(int x, int y) {

}

void player_death() {

}

void player_victory() {

}

void player_jumping(Player* player) {
    if (player->is_jumping == TRUE) {
        move_player(player);
    }
    else {
        stop_jump(player);
    }
    
}



