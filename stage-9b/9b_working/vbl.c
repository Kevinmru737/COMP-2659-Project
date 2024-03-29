
#include "vbl.h"
short main_game_timer = 0;
short col_anim_timer = 0;

/*
 *Purpose: C helper function for the main game loop vbl ISR. Updates the level, game model and 
           checks for collision. The game will run at 35 hz, hence the (main_game_timer==2).

*/
void process_main_game_vbl_isr() 
{
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
 *Purpose: C helper function for the player explosion animation.
           The timing of the explosion is set by the (col_anim_timer == 7). If 7 is less, the player
           will "explode faster", if more, the player will "explode" slower. Basically controls how many frames
           to do the explosion sequence.
*/

void collision_animation_helper() 
{
    col_anim_timer++;
    if (col_anim_timer == 7)
    {
        render_request = 1;
        col_anim_timer = 0;
    }
    


}