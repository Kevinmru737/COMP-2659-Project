/*
*Purpose: Header file for a clear quick function author by Marc Shroeder. Clears the 38k bytes in memory 
*       starting from base. Before calling, make sure the base points to the starts of the frame buffer
*       or there might be an error related to memory

*/

#ifndef RAST_ASM_H
#define RAST_ASM_H

#include "macros.h" 

void clear_screen(UINT32* base);
void clear_except_ground(UINT32* base);

void set_video_base(UINT32 *);
UINT32* get_video_base();

void enter_super();
void exit_super();



#endif
