
#include "vbl.h"


static short main_game_timer = 0;
static short animation_timer = 0;
static UINT32 time_elapsed_melody = 0;
static UINT32 time_elapsed_base = 0;

/*****************************************************************************
 *Purpose: C helper function for the main game loop vbl ISR.
*          Dependin on if the main game is running or an event animation is
*          running or mouse is enabled it will run with differnt timings and
*           execute differnt functions
*
* Note:  The game will run at 35 hz, hence the (main_game_timer==2).
          THe event animation timer is also set up with a custom number(7)
******************************************************************************/
void process_vbl_isr() 
{
    if(is_main_game_running == TRUE) {
        main_game_timer++;
        if (main_game_timer == 2) {
            update_level(&model, &game_state);
            update_game_objects(&model);
            fatal_collision = player_fatal_collision(&model);

            time_elapsed_base++;
            time_elapsed_melody++;
            update_music(&time_elapsed_melody, &time_elapsed_base);
        
            render_request = 1;
            main_game_timer = 0;

        }

    } else if(event_animation_running == TRUE) {

        animation_timer++;
        if (animation_timer == 7){
            render_request = 1;
            animation_timer = 0;
        }
        
    } else if(is_mouse_enabled() == TRUE) {
            render_request = 1;
    }
}
