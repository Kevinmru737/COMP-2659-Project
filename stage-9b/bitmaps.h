/*
*Purpose: Header file for a clear quick function author by Marc Shroeder. Clears the 38k bytes in memory 
*       starting from base. Before calling, make sure the base points to the starts of the frame buffer
*       or there might be an error related to memory

*/

#ifndef BITMAPS_H
#define BITMAPS_H

#include "macros.h"

extern const UINT32 player_img[];
extern const UINT32 ground_img[];
extern const UINT32 triangle_img[];
extern const UINT32 background_img[];
extern const UINT32 platform_32_32 [];
extern const UINT32 platform_32_16[];
extern const UINT32 brick_32_32[];
extern const UINT32 brick_32_32_2[];
extern const UINT32 *game_object_images[];


extern const UINT8 *scores [];

extern const UINT8 score_0[];
extern const UINT8 score_10[];
extern const UINT8 score_20[];
extern const UINT8 score_30[];
extern const UINT8 score_40[];
extern const UINT8 score_50[];
extern const UINT8 score_60[];
extern const UINT8 score_70[];
extern const UINT8 score_80[];
extern const UINT8 score_90[];
extern const UINT8 score_100[];


extern const UINT8 explosion_f1 [];
extern const UINT8 explosion_f2 [];
extern const UINT8 explosion_f3 [];
extern const UINT8 explosion_f4 [];
extern const UINT8 explosion_f5 [];
extern const UINT8 explosion_f6 [];
extern const UINT8 explosion_f7 [];
extern const UINT8 explosion_f8 [];

extern const UINT8 *explosion_images [];

extern const UINT8 splash_screen[];






#endif
