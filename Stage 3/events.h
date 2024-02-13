#ifndef EVENTS_H
#define EVENTS_H


/*** Synchronous Events***/
void triangle_moving(Triangle* int x, int y, int hor_vel);
void platform_moving(Platform* platform, int x, int y, int width, int height, int hor_vel);
void player_death();
void player_victory();
void player_jumping(Player* player);

/*** Asynchronous Events ***/
void jump_request(Player* player);
void pause_request();
void quit_request();
void increment_attempt();

/*** Conditional Events ***/
bool ground_collision(Player* player, Ground* ground);
void reset_attempt(Attempt* prev_attempt_number);
bool platform_collision_unsafe(Player* player, Platform* platform);
bool platform_collision_safe(Player* player, Platform* platform);
bool victory_collision(Player* player, Victory_Wall* victory_wall);
void reset_attempt(Attempt* prev_attempt_number);


#endif