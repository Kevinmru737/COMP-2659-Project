#ifndef EVENTS_H
#define EVENTS_H
#include "types.h"
#include "models.h"
/*** Synchronous Events***/
void triangle_moving(Triangle* triangle);
void platform_moving(Platform* platform);
void player_death();
void player_victory();
void player_jumping(Player* player);
bool player_triangle_collison( Player* player , Triangle * triangle);


/*** Asynchronous Events ***/
void jump_request(Player* player);
void pause_request();
void quit_request();
void increment_attempt();

/*** Conditional Events ***/
bool ground_collision(Player* player, Ground* ground);
bool platform_collision_unsafe(Player* player, Platform* platform);
bool platform_collision_safe(Player* player, Platform* platform);
bool victory_collision(Player* player, Victory_Wall* victory_wall);
bool player_triangle_collison_helper( Player* player , Triangle * triangle);
bool is_player_falling( Player * player, Platform *Platform, Ground * ground);



#endif