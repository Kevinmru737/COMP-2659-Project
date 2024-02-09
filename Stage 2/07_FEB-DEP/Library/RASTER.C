
 /* 
 Last modifed by Depanshu on 7 Feb 2024
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
 *      in the frame buffer based on the provided  coordinates (x, y).
 *      It then iterates through each row of the bitmap, XORing the bits
 *      with the corresponding bits in the destination memory.
 *      The function accounts for aligned and unaligned starting columns.
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
 */

void draw_32_bit_bitmap(UINT32 *base, int x, int y, int height, int width, const UINT32 *bitmap )
{
    int i;
    int bit_position = x & 31; /*which bit to start drawning on*/


    /*how many bits to draw on the second longword */
    int draw_sec_long = bit_position == 0 ? 0 : UINT32_SIZE_BITS - bit_position;
        
    width = width >> 5;
    base += OFFSET_TO_UINT32(x,y);

    while (height > 0) {
        i = width;
        for (i; i > 0; i--) {
            *base ^= (*bitmap) >> bit_position;
            base++;
            *base ^= draw_sec_long == 0 ? 0 : (*bitmap) << draw_sec_long;
            bitmap++;
        }

        height--;
        base += UINT32_PER_SCANLINE - width;
    }

    
    return;   

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
 */
void draw_16_bit_bitmap(UINT16 *base, int x, int y, int height, int width, const UINT16 *bitmap )
{
    int i;
    int bit_position = x & 15; /*which bit to start drawning on*/


    /*how many bits to draw on the second word */
    int draw_sec_word = bit_position == 0 ? 0 : UINT16_SIZE_BITS - bit_position;

    width = width >> 4;
    base += OFFSET_TO_UINT16(x,y);

    while (height > 0) {
        i = width;
        for (i; i > 0; i--) {
            *base ^= (*bitmap) >> bit_position;
            base++;
            *base ^= draw_sec_word == 0 ? 0 : (*bitmap) << draw_sec_word;
            bitmap++;
        }

        height--;
        base += UINT16_PER_SCANLINE - width;
    }

    return;

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
 *      It then iterates through each row of the bitmap, XORing the bits
 *      with the corresponding bits in the destination memory.
 *      The function accounts for aligned and unaligned starting columns.
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
 */

void draw_8_bit_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap)
{
    int i;
    int bit_position = x & 7; /*which bit to start drawning on*/


    /*how many bits to draw on the second longword */
    int draw_sec_word = bit_position == 0 ? 0 : UINT8_SIZE_BITS - bit_position;

    width = width >> 3;
    base += OFFSET_TO_UINT8(x,y);

    while (height > 0) {
        i = width;
        for (i; i > 0; i--) {
            *base ^= (*bitmap) >> bit_position;
            base++;
            *base ^= draw_sec_word == 0 ? 0 : (*bitmap) << draw_sec_word;
            bitmap++;
        }

        height--;
        base += UINT8_PER_SCANLINE - width;
    }

    return;

}













































