
#ifndef RAST_ASM_H
#define RAST_ASM_H

#include "consts.h"

void clear_screen(UINT32* base);
void clear_except_ground(UINT32* base);
void set_video_base(UINT32 *);
UINT32* get_video_base();



#endif
