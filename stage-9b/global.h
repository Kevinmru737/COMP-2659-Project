

#ifndef GLOBAL_H
#define GLOBAL_H


#include "models.h"
#include "macros.h"
#define VBL_VECTOR_NUM 28
extern Model model;
extern unsigned char game_state;
extern bool fatal_collision;
extern short render_request;

extern bool is_main_game_running;
extern bool event_animation_running;
extern bool is_mouse_enabled;
#endif
