#ifndef EVENTS_H
#define EVENTS_H
#include "models.h"
#define PLAYER_INITIAL_JUMP_VELOCITY 30
#define PLAYER_LEFT_EDGE_X_POS 160
#define PLAYER_WIDTH 31
#define PLAYER_RIGHT_EDGE_X_POS 191
#define POSSIBLE_COLLISION_RIGHT_EDGE (PLAYER_RIGHT_EDGE_X_POS + DEFAULT_OBJECT_VELOCITY)
#define POSSIBLE_COLLISION_LEFT_EDGE (PLAYER_LEFT_EDGE_X_POS + DEFAULT_OBJECT_VELOCITY)


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