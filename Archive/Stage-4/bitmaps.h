/*
*Purpose: Header file for a clear quick function author by Marc Shroeder. Clears the 38k bytes in memory 
*       starting from base. Before calling, make sure the base points to the starts of the frame buffer
*       or there might be an error related to memory

*/

#ifndef BITMAPS_H
#define BITMAPS_H

#include "types.h"

extern const UINT32 player_img[];
extern const UINT32 ground_img[];
extern const UINT32 triangle_img[];
extern const UINT32 platform_img[];


#endif
