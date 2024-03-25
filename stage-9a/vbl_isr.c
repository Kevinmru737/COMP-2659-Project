
#include "vbl_isr.h"

short timer = 0;


/*
 * Purpose: Process all the synchronous events in the game. Since the game runs at
 *          35 hz, it only processes synchronous events for every second clock tick.
 */

void process_main_game_vbl_isr() {
    timer++;
    if (timer == 2)
    {
        update_level(&model, &game_state);
        update_game_objects(&model, &fatal_collision);
        fatal_collision = player_fatal_collision(&model, 0);
        render_request = 1;
        timer = 0;
    }
}







