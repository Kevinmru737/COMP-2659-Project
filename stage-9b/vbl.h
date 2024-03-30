
#ifndef vbl_H
#define vbl_H
#include <osbind.h>
#include "events.h"
#include "level.h"
#include "global.h"

#include "macros.h"
#include "music.h"

void main_gm_vbl_isr();
void process_main_game_vbl_isr();
void event_animation_vbl_isr();
void animation_helper();



extern UINT32 time_elapsed_melody;
extern UINT32 time_elapsed_base;




#endif
