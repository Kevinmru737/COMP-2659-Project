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
extern const UINT32 background_img[];
extern const UINT32 platform_32_32 [];
extern const UINT32 platform_32_16[];
extern const UINT32 brick_32_32[];
extern const UINT32 brick_32_32_2[];
extern const UINT32 *game_object_images[];
extern const UINT32 start_message [];

#endif
