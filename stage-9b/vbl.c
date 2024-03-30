
#include "vbl.h"
short main_game_timer = 0;
short animation_timer = 0;
bool is_main_game_running = FALSE;
bool event_animation_running = FALSE;
bool is_mouse_enabled = FALSE;
UINT32 time_elapsed_melody = 0,
    time_elapsed_base = 0;

/*
 *Purpose: C helper function for the main game loop vbl ISR. Updates the level, game model and 
           checks for collision. The game will run at 35 hz, hence the (main_game_timer==2).

*/
void process_vbl_isr() 
{
    if(is_main_game_running == TRUE) {
        main_game_timer++;
        if (main_game_timer == 2)
        {
            update_level(&model, &game_state);
            update_game_objects(&model, &fatal_collision);
            fatal_collision = player_fatal_collision(&model, 0);

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
    


    } else if(is_mouse_enabled == TRUE) {

    }
}
