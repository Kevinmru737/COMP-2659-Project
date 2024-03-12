
 /* 
 Last modifed by Depanshu on 12 Feb 2024
*/

#include "raster.h"

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
*        second_long_mask zeros out remaining bits on the second long where the bitmap is to be drawn
*/
void draw_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width, const UINT32 *bitmap )
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
        draw_32_bit_bitmap_row(base, bitmap, longs_per_row, start_bit_position, first_long_mask, second_long_mask,  bits_in_first_long);
        base += UINT32_PER_SCANLINE;
        bitmap += longs_per_row;
        height--;
    }
    
    return;   

}


/*  Author: Depanshu
 * Purpose: Draws a single row of a 32-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_32_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   For unaligned positions, the longs to draw one increases by one due to the
 *   bitmap data spanning across an additional long . This happens 
 *   because the starting bit offset requires part of the bitmap to be drawn in the first long,
 *   and the remainder spills over into the next long
 *   THe masks are used to clear the pixels where the bitmap is to be drawn.
 * Restriction:
 *  Not called directly by user code; used internally by draw_32_bit_bitmap.
 */

void draw_32_bit_bitmap_row(UINT32 *base, const UINT32 *bitmap, int longs_per_row, int start_bit_offset, UINT32 first_long_mask, UINT32 second_long_mask, int bits_in_first_long) {
    
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
 *        second_word_mask zeros out remaining bits on the second word where the bitmap is to be drawn
 */
void draw_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width, const UINT16 *bitmap )
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
        draw_16_bit_bitmap_row(base, bitmap, words_per_row, start_bit_position, first_word_mask, second_word_mask,  bits_in_first_word);
        base += UINT16_PER_SCANLINE;
        bitmap += words_per_row;
        height--;
    }

    return;

}


/*  Author: Depanshu
 * Purpose: Draws a single row of a 16-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_16_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   Look to the draw_32_bit_bitmap_row for more information as it is similar
 * Restriction:
 *  Not called directly by user code; used internally by draw_32_bit_bitmap.
 */

void draw_16_bit_bitmap_row(UINT16 *base, const UINT16 *bitmap, int words_per_row, int start_bit_offset, UINT16 first_word_mask, UINT16 second_word_mask, int bits_in_first_word) {
    
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
 *       second_byte_mask zeros out remaining bits on the second byte where the bitmap is to be drawn
 */

void draw_8_bit_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap)
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
        draw_8_bit_bitmap_row(base, bitmap, bytes_per_row, start_bit_position, first_byte_mask, second_byte_mask,  bits_in_first_byte);
        base += UINT8_PER_SCANLINE;
        bitmap += bytes_per_row;
        height--;
    }

    return;

}



/*  Author: Depanshu and Kevin
 * Purpose: Draws a single row of a 8-bit bitmap onto the frame buffer
 *
 * Details:
 *   This function is a helper for draw_8_bit_bitmap. It dealts with both
 *   situtation when the starting pixel to draw on is not aligned and when it is.
 *   Look to the draw_32_bit_bitmap_row for more information as it is similar to this
 * Restriction:
 *  Not called directly by user code; used internally by draw_8_bit_bitmap.
 */

void draw_8_bit_bitmap_row(UINT8 *base, const UINT8 *bitmap, int bytes_per_row, int start_bit_offset, UINT8 first_byte_mask, UINT8 second_byte_mask, int bits_in_first_byte) {
    
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


/* Author: Depanshu
* Purpose: Clear a 32 bit bitmap
*
*Details: Used for clearing a bitmap that was put into the frame buffer.
*        Each element in the bitmap must be 32 bits for this function to work.
*/          

void clear_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width )
{
    int longs_per_row;

    UINT32 first_long_mask = 0xffffffff, second_long_mask  = 0xffffffff;

    int start_bit_position = x & 31; /*which bit to start clearning on on*/

    first_long_mask = first_long_mask << (32 -start_bit_position);
    second_long_mask = second_long_mask >> start_bit_position;


    /*how many longs wide is the bitmap*/   
    longs_per_row = width >> 5;
    base += OFFSET_TO_UINT32(x,y); /*which long to start clearing on*/

    while (height > 0) {
         clear_32_bit_bitmap_row(base, longs_per_row ,start_bit_position, first_long_mask,  second_long_mask);
         base += UINT32_PER_SCANLINE;
         height--;
    }

}
      


/* Author: Depanshu
* Purpose: Clear a single row of a 32 bit from bitmap from the frame buffer
*/
void clear_32_bit_bitmap_row(UINT32 *base, int longs_per_row, int start_bit_position, UINT32 first_long_mask,  UINT32 second_long_mask) {
   int i = 0;
    if (start_bit_position == 0) {
        for (i; i < longs_per_row; i++) {
            *base++ = 0x0;
        }
    } else {

        for (i; i < longs_per_row; i++) {
            *base &= first_long_mask;
            base++;
            *base &= second_long_mask;
        }

    }

}




/* Author: Depanshu
* Purpose: Clear a 16 bit bitmap
*
* Details: Used for clearing a bitmap that was put into the frame buffer.
*          Each element in the bitmap must be 16 bits for this function to work.
*/          

void clear_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width )
{
    int words_per_row;

    UINT16 first_word_mask = 0xffff, second_word_mask  = 0xffff;

    int start_bit_position = x & 15; /*which bit to start clearning on on*/

    first_word_mask = first_word_mask << (16 -start_bit_position);
    second_word_mask = second_word_mask >> start_bit_position;


    /*how many words wide is the bitmap*/   
    words_per_row = width >> 4;
    base += OFFSET_TO_UINT16(x,y); /*which word to start clearing on*/

    while (height > 0) {
         clear_16_bit_bitmap_row(base, words_per_row, start_bit_position, first_word_mask,  second_word_mask);
         base += UINT16_PER_SCANLINE;
         height--;
    }

}



/* Author: Depanshu
* Purpose: Clear a single row of a 16 bit bitmap from the frame buffer
*/
void clear_16_bit_bitmap_row(UINT16 *base, int words_per_row, int start_bit_position, UINT16 first_word_mask,  UINT16 second_word_mask) {
   int i = 0;
    if (start_bit_position == 0) {
        for (i; i < words_per_row; i++) {
            *base++ = 0x0;
        }
    } else {

        for (i; i < words_per_row; i++) {
            *base &= first_word_mask;
            base++;
            *base &= second_word_mask;
        }

    }

}









































