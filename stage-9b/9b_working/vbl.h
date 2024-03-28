
#ifndef vbl_H
#define vbl_H
#include <osbind.h>
#include "events.h"
#include "level.h"
#include "global.h"




void main_gm_vbl_isr();
void process_main_game_vbl_isr();
void fatal_animation_vbl_isr();
void collision_animation_helper();




#endif
