#ifndef EVENTS_H
#define EVENTS_H
#include "models.h"

/*** Synchronous Events***/
void move_all_active_triangles(Model *model);
void move_all_active_platforms(Model* model);
bool player_died(Model *model, short player_);
/*** Asynchronous Events ***/
void jump_request(Model * model, short player_num);
void pause_request();
void quit_request();

/*** Conditional Events ***/
void move_all_active_players(Model *model);


#endif