#ifndef RASTER_H
#define RASTER_H


#include "types.h"

/*
 * Purpose: Draws a bitmap with a width that is multiple of 32 bits
 *
 * Parameters:
 *   base       - Pointer to the base frame buffer
 *   x          - X-coordinate on the screen for the top left the bitmap
 *   y          - X-coordinate on the screen for the top left the bitmap
 *   height     - height of the bitmap
 *   width      - width of the bitmap
 *   bitmap     - pointer to the bitmap data
 *
 * Details:
 *      The function calculates the starting position of drawing the bitmap
 *      in the frame buffer based on the provided  coordinates (x, y).
 *      It then iterates through each row of the bitmap, XORing the bits
 *      with the corresponding bits in the destination memory.
 *      The function accounts for aligned and unaligned starting columns.
 *
 * Restrictions/Assumption:
 *  It supports bitmaps with widths that are multiples of 32 bits such as ( 32 x 32, 64 x 94, 96 x 1 ,etc ..)
 *  Behaviour will be undefined if the input parameters are not correct
 *  No error and bounds checking is provided
 *  User is responsible for providing the correct parameters
 *  Height, width, x and y inputs are to be given in pixels
 *
 *  Sample call:
 *  draw_multi_of_32_bitmap(buffer, x, y, height, width, sprite);
 */




void draw_multi_of_32_bitmap(UINT32 *base, int x, int y, int height, int width, UINT32 *bitmap);
void draw_multi_of_8_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap );
void clear_screen(UINT32 *base);
void draw_horizontal_line(UINT16 *base, int x1, int x2, int y, int thickness);
void draw_vertical_line(UINT16 *base, int x, int y1, int y2);
void draw_triangle (UINT16 *base, int x, int y);
void plot_pixel(UINT8 *base, int x, int y);




#endif
