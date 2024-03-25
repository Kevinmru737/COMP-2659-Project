
#include "vbl_isr.h"

short main_game_timer = 0;
short expl_timer = 0;

/*
 * Purpose: Process all the synchronous events in the game. Since the game runs at
 *          35 hz, it only processes synchronous events for every second clock tick.
 */
void process_main_game_vbl_isr() {
    main_game_timer++;
    if (main_game_timer == 2)
    {
        update_level(&model, &game_state);
        update_game_objects(&model, &fatal_collision);
        fatal_collision = player_fatal_collision(&model, 0);
        render_request = 1;
        main_game_timer = 0;
    }
}

/*
 * Purpose: Process the timing for the explosion animation
 */
void process_explosion_vbl_isr() {
    expl_timer++;
    if (expl_timer == 7)
    {
        render_request = 1;
        expl_timer = 0;
    }
}






