#ifndef EVENTS_H
#define EVENTS_H
#include "types.h"
#include "models.h"
/*** Synchronous Events***/
void triangle_moving(Triangle* triangle);
void platform_moving(Platform* platform);
void player_death();
void player_victory();
bool player_triangle_collison( Player* player , Triangle * triangle);
void move_player(Model *model);

/*** Asynchronous Events ***/
void jump_request(Model *model);
void pause_request();
void quit_request();
void increment_attempt();

/*** Conditional Events ***/
bool ground_collision(Player* player, Ground* ground);
bool platform_collision_unsafe(Player* player, Platform* platform);
bool platform_collision_safe(Player* player, Platform* platform);
bool victory_collision(Player* player, Victory_Wall* victory_wall);
bool player_triangle_collison_helper( Player* player , Triangle * triangle);
bool is_player_not_falling( Model *model);



#endif