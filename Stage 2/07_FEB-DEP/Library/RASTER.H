#ifndef RASTER_H
#define RASTER_H
 /* 
 Last modifed by Depanshu on 7 Feb 2024
*/

#include "types.h"

void draw_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width, const UINT32 *bitmap);
void draw_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width, const UINT16 *bitmap);
void draw_8_bit_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap);


#endif
