#ifndef EVENTS_H
#define EVENTS_H
#include "models.h"

/*** Synchronous Events***/
void move_all_active_triangles(Model *model);
void move_all_active_platforms(Model* model);
bool player_died(Model *model, short player_);
void move_a_single_active_triangle(Model* model, short triangle_num);
void move_a_single_platform(Model* model, short platform_num);
void remove_triangle (Model* model, short triangle_num);
void clear_triangle (Triangle* triangle);
void remove_platform (Model* model, short platform_number);
void clear_platform (Platform* platform);

/*** Asynchronous Events ***/
void jump_request(Model * model, short player_num);
void pause_request();
void quit_request();

/*** Conditional Events ***/
void move_all_active_players(Model *model);
void move_one_player(Model *model, short player_num);


#endif