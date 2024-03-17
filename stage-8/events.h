#ifndef EVENTS_H
#define EVENTS_H
#include "models.h"
#include "macros.h"

/*** Synchronous Events***/
void update_game_objects(Model * model, bool *fatal_collision);
void update_platform_or_triangle(Game_Object * object);
/*** Asynchronous Events ***/
void jump_request(Model * model, short player_num);
void pause_request();
void quit_request();

/*** Conditional Events ***/
void update_player_state_moving_up(Game_Object * player);
void update_player_state_moving_down(Model * model, short player_num);
bool check_player_safe_collision_with_platform(Model * model, short player_num);
void update_player_state_on_platform(Model * model, short player_num);
#endif