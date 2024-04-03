#ifndef EVENTS_H
#define EVENTS_H
#include "models.h"
#include "consts.h"

/*** Synchronous Events***/
void update_game_objects(Model * model);
void update_platform_or_triangle(Game_Object * object);
/*** Asynchronous Events ***/
void jump_request(Model * model);


/*** Conditional Events ***/
void update_player_state_moving_up(Game_Object * player);
void update_player_state_moving_down(Model * model);
bool check_player_safe_collision_with_platform(Model * model);
void update_player_state_on_platform(Model * model);
#endif