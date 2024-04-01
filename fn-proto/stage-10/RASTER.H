#ifndef RASTER_H
#define RASTER_H

/* Headers for the Raster function library
 Last modifed by Depanshu on 12 Feb 2024
*/
#include "macros.h" 
#define MOUSE_HEIGHT 16
void draw_platform_triangle(UINT32 *base,int x,int y,const UINT32 *bitmap, bool is_short_platform );
void draw_player(UINT32 *base,int y,const UINT32 *bitmap );





void draw_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width, const UINT32 *bitmap);
void draw_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width, const UINT16 *bitmap);
void draw_8_bit_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap);


void draw_32_bit_bitmap_row(UINT32 *base, const UINT32 *bitmap, int longs_per_row, int start_bit_offset, UINT32 first_long_mask, UINT32 second_long_mask, int bits_in_first_long);
void draw_16_bit_bitmap_row(UINT16 *base, const UINT16 *bitmap, int words_per_row, int start_bit_offset, UINT16 first_word_mask, UINT16 second_word_mask, int bits_in_first_word);
void draw_8_bit_bitmap_row(UINT8 *base, const UINT8 *bitmap, int bytes_per_row, int start_bit_offset, UINT8 first_byte_mask, UINT8 second_byte_mask, int bits_in_first_byte);

void clear_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width );
void clear_32_bit_bitmap_row(UINT32 *base, int longs_per_row, int start_bit_position, UINT32 first_long_mask,  UINT32 second_long_mask);

void clear_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width );
void clear_16_bit_bitmap_row(UINT16 *base, int words_per_row, int start_bit_position, UINT16 first_word_mask,  UINT16 second_word_mask);

void draw_16_x_16_cursor(UINT16 * base, int x, int y, UINT16 * cursor);
void restore_prev_drawn_cursor_position(UINT16 * base, int x, int y, UINT16 * splash_screen);
void clear_screen(UINT32* base);
void clear_except_ground(UINT32* base);



#endif
