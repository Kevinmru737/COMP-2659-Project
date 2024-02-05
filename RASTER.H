#ifndef RASTER_H
#define RASTER_H


#include "types.h"




void draw_multi_of_32_bitmap(UINT32 *base, int x, int y, int height, int width, UINT32 *bitmap);








void draw_multi_of_16_bitmap(UINT16 *base, int x, int y, int height, int width, UINT16 *bitmap );


void clear_screen(UINT32 *base);





#endif
