
 /* 
Last modifed by Depanshu on 1 April 2024
*/

#include "raster.h"

/*****************************************************************************
 * Purpose: Restores the area at the previous cursor position
 *          by copying from a splash screen buffer(bitmap array).
******************************************************************************/
void restore_prev_drawn_cursor_position(UINT16 * base, int x, int y,
     UINT16 * splash_screen) {
    int row = 0;
    splash_screen += OFFSET_TO_UINT16(x,y);
    base += OFFSET_TO_UINT16(x,y);

    /*Restoring the space where the cursor was drawn previously*/
    for(row = 0;row < MOUSE_HEIGHT; row++) {
        *base++ = *splash_screen++;
        *base = *splash_screen;
        base += UINT16_PER_SCANLINE - 1;
        splash_screen += UINT16_PER_SCANLINE - 1;
    }

}


/*****************************************************************************
 * Purpose: Draws a 16x16 cursor at the specified coordinates on the frame buffer.
 ******************************************************************************/
void draw_16_x_16_cursor(UINT16 * base, int x, int y, UINT16* cursor) {
    int row = 0;
    int start_bit_position = x & 15;    /*which bit to start drawning on*/
    int bits_in_first_word = UINT16_SIZE_BITS - start_bit_position;

    base += OFFSET_TO_UINT16(x,y);

    for(row;row < MOUSE_HEIGHT; row++) {
        *base |= (*cursor) >> start_bit_position;
        base++;
        *base |= (*cursor) << bits_in_first_word;
        cursor++;
        base += UINT16_PER_SCANLINE - 1;
    }

}


/*****************************************************************************
 * Purpose: Draws player bitmap.
 *
 * Details: Renders a 32x32 bitmap representing the player at a specified
 *          vertical position on the screen buffer.The x is always fixed.
 *          
 * Input:   base - Pointer to screen buffer base.
 *          y    - Y-coordinate for the top-left corner of the player bitmap.
 *          bitmap - Pointer to player bitmap data.
 *
 * Output:  Updates the screen buffer with the player's bitmap at
 *          the specified location.
 ******************************************************************************/
void draw_player(UINT32 *base,int y,const UINT32 *bitmap )
{
    int row = 0;
    /* The player's x is always the same, fixed at 160. 160 / 32 = 5*/
    base += 5 + ( (y << 4) + (y << 2) ); 

    for(row;row < DEFAULT_OBJECT_HEIGHT; row++) {
	    *base = *bitmap;
        base += UINT32_PER_SCANLINE;
        bitmap++;
	} 
		
}
/******************************************************************************
 * Purpose: Draws platform triangle bitmap.
 *
 * Details: Renders a bitmap representing the platform or a triangle at a
 *          specified position on the screen buffer.
 *          
 * Input:   
 *       - base: Pointer to screen buffer base.
 *       - x: X-coordinate for the top-left corner of the platform triangle bitmap.
 *       - y: Y-coordinate for the top-left corner of the platform triangle bitmap.
 *       - bitmap: Pointer to platform triangle bitmap data.
 *       - is_short_platform: Boolean indicating if the platform is of a shorter 
 *                            type.
 *
 * Output:  Updates the screen buffer with the platform triangle's bitmap 
******************************************************************************/
void draw_platform_triangle(UINT32 *base,int x,int y,const UINT32 *bitmap,
                            bool is_short_platform )
{
	int row = 0;
    /*ALl objects expect for a short platform have a height of 32*/
	int height = is_short_platform ? PLATFORM_HEIGHT_SHORT : DEFAULT_OBJECT_HEIGHT;    

    int start_bit_position = x & 31; /*which bit to start drawning on*/

    /*how many bits were draw on the first long */
    int bits_in_first_long = UINT32_SIZE_BITS - start_bit_position;
	
    base += OFFSET_TO_UINT32(x,y); /*which long to start drawing on*/

	for(row;row < height; row++) {
         *base |= (*bitmap) >> start_bit_position;
         base++;
         *base |= (*bitmap) << bits_in_first_long;
         bitmap++;
		base += UINT32_PER_SCANLINE - 1;
    }	
	
 } 
	
	

/******************************************************************************
/* Author: Depanshu
 * Purpose: Draws a bitmap with  32 bit values 
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
 *      in the frame buffer based on the provided  coordinates (x, y). It calculates
 *      whether the function starts at an unaligned drawing position. 
 *      It then iterates through each row of the bitmap, using the helper function
 *      to draw each row of the bitmap. 
 *      The alpha mask is to ensure that the pixels where the bitmap is to be drawn
 *      is cleared as drawing using XOR at uncleard pixels will lead to drawing
 *      that does not represents the bitmap.
 *
 * Restrictions/Assumption:
 *  It  only supports bitmaps with that are 32 bits(0x00000000, or 0xffffffff)
 *  Behaviour will be undefined if the input parameters are not correct
 *  No error and bounds checking is provided
 *  User is responsible for providing the correct parameters
 *  Height, width, x and y inputs are to be given in pixels
 *
 *  Sample call:
 *  draw_multi_of_32_bitmap(buffer, x, y, height, width, sprite);
*
*   NOTE:first_long_mask is used to zero out the bits right of start_bit_position. 
*        second_long_mask zeros out remaining bits on the second long where the 
*        bitmap is to be drawn
******************************************************************************/

void draw_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width, 
const UINT32 *bitmap )
{
    int longs_per_row;

    UINT32 first_long_mask = 0xffffffff, second_long_mask  = 0xffffffff;

    int start_bit_position = x & 31; /*which bit to start drawning on*/

    /*how many bits were draw on the first long */
    int bits_in_first_long = UINT32_SIZE_BITS - start_bit_position;

    first_long_mask = first_long_mask << (32 -start_bit_position);
    second_long_mask = second_long_mask >> start_bit_position;


    /*how many longs wide is the bitmap*/   
    longs_per_row = width >> 5;
    base += OFFSET_TO_UINT32(x,y); /*which long to start drawing on*/

    while (height > 0) {
        draw_32_bit_bitmap_row(base, bitmap, longs_per_row, start_bit_position, 
        first_long_mask, second_long_mask,  bits_in_first_long);
        base += UINT32_PER_SCANLINE;
        bitmap += longs_per_row;
        height--;
    }
    
    return;   

}

/******************************************************************************
/*  Author: Depanshu
 * Purpose: Draws a single row of a 32-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_32_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   For unaligned positions, the longs to draw one increases by one due to the
 *   bitmap data spanning across an additional long . This happens 
 *   because the starting bit offset requires part of the bitmap to be drawn in the 
*    first long, and the remainder spills over into the next long
 *   THe masks are used to clear the pixels where the bitmap is to be drawn.
 * Restriction:
 *  Not called directly by user code; used internally by draw_32_bit_bitmap.
******************************************************************************/
void draw_32_bit_bitmap_row(UINT32 *base, const UINT32 *bitmap, 
        int longs_per_row, int start_bit_offset, UINT32 first_long_mask, 
        UINT32 second_long_mask, int bits_in_first_long) {
    
    int i = 0;
    if (start_bit_offset == 0) {
        for (i; i < longs_per_row; i++) {
            *base++ = *bitmap++;
        }
    } else {

        for (i; i < longs_per_row; i++) {
            *base &= first_long_mask;
            *base ^= (*bitmap) >> start_bit_offset;
            base++;
            *base &= second_long_mask;
            *base ^= (*bitmap) << bits_in_first_long;
            bitmap++;
        }
    }
}


/******************************************************************************
/* Author: Depanshu
 * Purpose: Draws a bitmap with 16 bit values 
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
 *  It  only supports bitmaps with that are 16 bits(0x0000, or 0xffff) 
 *  Behaviour will be undefined if the input parameters are not correct
 *  No error and bounds checking is provided
 *  User is responsible for providing the correct parameters
 *  Height, width, x and y inputs are to be given in pixels
 *
 *  Sample call:
 *  draw_multi_of_16_bitmap(buffer, x, y, height, width, sprite);
 *  
 *  NOTE:first_word_mask is used to zero out the bits right of start_bit_position. 
 *        second_word_mask zeros out remaining bits on the second word where the 
 *          bitmap is to be drawn
******************************************************************************/
void draw_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width,
 const UINT16 *bitmap )
{
    int words_per_row;

    UINT16 first_word_mask = 0xffff, second_word_mask  = 0xffff;

    int start_bit_position = x & 15; /*which bit to start drawning on*/


    /*how many bits to draw on the second word */
    int bits_in_first_word = UINT16_SIZE_BITS - start_bit_position;

    first_word_mask = first_word_mask << (16 -start_bit_position);
    second_word_mask = second_word_mask >> start_bit_position;

   /*how many words wide is the bitmap*/   
    words_per_row = width >> 4;
    base += OFFSET_TO_UINT16(x,y);/*which word to start drawing on*/

    while (height > 0) {
        draw_16_bit_bitmap_row(base, bitmap, words_per_row, start_bit_position,
        first_word_mask, second_word_mask,  bits_in_first_word);
        base += UINT16_PER_SCANLINE;
        bitmap += words_per_row;
        height--;
    }

    return;

}

/******************************************************************************
/*  Author: Depanshu
 * Purpose: Draws a single row of a 16-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_16_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   Look to the draw_32_bit_bitmap_row for more information as it is similar
 * Restriction:
 *  Not called directly by user code; used internally by draw_32_bit_bitmap.
******************************************************************************/

void draw_16_bit_bitmap_row(UINT16 *base, const UINT16 *bitmap,
 int words_per_row, int start_bit_offset, UINT16 first_word_mask,
UINT16 second_word_mask, int bits_in_first_word) {
    
    int i = 0;
    if (start_bit_offset == 0) {
        for (i; i < words_per_row; i++) {
            *base++ = *bitmap++;
        }
    } else {

        for (i; i < words_per_row; i++) {
            *base &= first_word_mask;
            *base ^= (*bitmap) >> start_bit_offset;
            base++;
            *base &= second_word_mask;
            *base ^= (*bitmap) << bits_in_first_word;
            bitmap++;
        }
    }
}

/******************************************************************************
/* Author: Kevin
 * Purpose: Draws a bitmap with 8 bit values 
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
 *      It then iterates through each row of the bitmap, using the helper function
 *      to draw each row of the bitmap. 
 *      The  'masks' are to ensure that the pixels where the bitmap is to be drawn
 *      is cleared as drawing using XOR at uncleard pixels will lead to drawing
 *      that does not represents the bitmap.
 *
 * Restrictions/Assumption:
 *  It  only supports bitmaps with that are 16 bits(0x00, or 0xff) 
 *  Behaviour will be undefined if the input parameters are not correct
 *  No error and bounds checking is provided
 *  User is responsible for providing the correct parameters
 *  Height, width, x and y inputs are to be given in pixels
 *
 *  Sample call:
 *  draw_multi_of_8_bitmap(buffer, x, y, height, width, sprite);
 *
 *  NOTE:first_byte_mask is used to zero out the bits right of start_bit_position. 
 *       second_byte_mask zeros out remaining bits on the second byte where the
 *       bitmap is to be drawn
 ******************************************************************************/

void draw_8_bit_bitmap(UINT8 *base, int x, int y, int height, int width,
 UINT8 *bitmap)
{
   int bytes_per_row;

    UINT8 first_byte_mask = 0xff, second_byte_mask  = 0xff;

    int start_bit_position = x & 7; /*which bit to start drawning on*/


    /*how many bits to draw on the second word */
    int bits_in_first_byte = UINT8_SIZE_BITS - start_bit_position;

    first_byte_mask = first_byte_mask << (8 - start_bit_position);
    second_byte_mask = second_byte_mask >> start_bit_position;

    /*how many bytes wide is the bitmap*/   
    bytes_per_row = width >> 3;
    base += OFFSET_TO_UINT8(x,y); /*which byte to start drawing on*/


    while (height > 0) {
        draw_8_bit_bitmap_row(base, bitmap, bytes_per_row, start_bit_position,
        first_byte_mask, second_byte_mask,  bits_in_first_byte);
        base += UINT8_PER_SCANLINE;
        bitmap += bytes_per_row;
        height--;
    }

    return;

}


/******************************************************************************
/*  Author: Depanshu and Kevin
 * Purpose: Draws a single row of a 8-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_8_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   Look to the draw_32_bit_bitmap_row for more information as it is similar to this
 * Restriction:
 *  Not called directly by user code; used internally by draw_8_bit_bitmap.
******************************************************************************/
void draw_8_bit_bitmap_row(UINT8 *base, const UINT8 *bitmap, int bytes_per_row,
 int start_bit_offset, UINT8 first_byte_mask, UINT8 second_byte_mask,
  int bits_in_first_byte) {
    
    int i = 0;
    if (start_bit_offset == 0) {
        for (i; i < bytes_per_row; i++) {
            *base++ = *bitmap++;
        }
    } else {

        for (i; i < bytes_per_row; i++) {
            *base &= first_byte_mask;
            *base ^= (*bitmap) >> start_bit_offset;
            base++;
            *base &= second_byte_mask;
            *base ^= (*bitmap) << bits_in_first_byte;
            bitmap++;
        }
    }
}