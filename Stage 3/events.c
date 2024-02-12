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
/* Author: Kevin
 * Purpose: This event occurs when a player jump should occur and 
 *          continues until the player is no longer jumping.
 *
 * Details:
 *   Calls the function to move the player.
 *
 * Restriction:
 *  Not called directly by user code; used internally by draw_32_bit_bitmap.
 */
void player_jumping(Player* player) {
    if (player->is_jumping == TRUE) {
        move_player(player);
    } 
}



