#include "raster.h"
/*
 * Author: Kevin Oh
 * 
 * Purpose: Draws a horizontal line with varying thickness
 *
 * Parameters:
 *   base       - Word sized pointer to the base frame buffer
 *   x1         - X-coordinate on the screen for the left of the line
 *   x2         - X-coordinate on the screen for the right of the line
 *   y          - y-coordinate on the screen for the top left of the line
 *   thickness  - starting from the first line, working downwards,
 *				  adds extra lines simulating a thicker line drawn
 * 
 * Details:
 *      The function checks if the x1 and x2 coordinates are word aligned and if they
 *      are, a simpler drawing scheme is used that simply fills in word sized chunks of *base
 *      until x1 to x2 are drawn. If either of x1 or x2 are not word aligned,
 *		calculations and shifting will be done to correctly place the horizontal line
 *    	appropriately. This involves going to the first byte that requires shifting making
 *		the adjustments, drawing the inbetween word-aligned line, and shifting and adjusting 
 *		again for the very last byte. The above processes are simply repeated if thickness > 1.
 *
 * Restrictions/Assumptions:
 * 		This function assumes all input values to be valid/within bounds:
 *		x1 >= 0 && x1 < 640
 *  	x2 > x1 && x2 < 640 (in the case where x1 == x2 nothing will be drawn)
 *  	y >= 0 && y < 400
 *  	thickness > 0 (and that thickness will not cause attempted drawing outside the screen)
 *
 *  	All parameters are to be given in pixels
 *  
 *	  	This function CAN draw within a single word-sized memory location, however, there are some
 *		restrictions. If x1 is in bit 25, it will always fill in bits 25 - 31, until the next word
 *	  	aligned memory location. Thus drawing within a byte can only be correctly done if x2 is a 
 *  	memory location on the "edge" of a word-sized location. In otherwords to draw inside 
 *  	byte 1 exclusively, which contains bits 15 - 31, x2 must be 31. Drawing for example 
 *  	x1 = 25 and x2 = 28 will not draw correctly, and bits 25-31 will be filled in anyways.
 *
 *  Sample call:
 *  	draw_horizontal_line(base, 0, 250, 300, 14);
 */
void draw_horizontal_line (UINT16 *base, int x1, int x2, int y, int thickness) {

	int curr_thick = 0;
	base += (x1 / 16) + (y * 40);
	if ((x1 % 16 != 0) || (x2 % 16 != 0)) {
		int x1_draw = x1 % 16; /* for drawing the first partial byte*/
		int x2_draw = x2 % 16; /* for drawing the second partial byte*/
		int x_next_draw = (x2 / 16) - (x1 / 16); /* to find next drawing location*/
		/* repeatedly drawing lines underneath the first for thickness */
		while (curr_thick < thickness) {
			int dif_unaligned = (x_next_draw - 1);
			*base = x1_draw == 0 ? 0xFFFF : (0xFFFF) >> (x1_draw);
			base++;	
			/* drawing the full bytes between x1 and x2 */
			while (dif_unaligned > 0) {
				*base = 0xFFFF;
				base++;
				dif_unaligned--;
			}
			/* incase the user tries to draw within a single byte*/
			if (x_next_draw != 0) {
				*base = /*x2_draw == 0 ? 0 : */(0xFFFF) << (16 - x2_draw);
				base += (40 - (x_next_draw));
			}
			else {
				base += (39 - (x_next_draw));
			}
			curr_thick++;
		}
	}
	else {
		while (curr_thick < thickness) {
			int dif = (x2 - x1) / 16;  
			while (dif > 0) {
				*base = 0xFF00;
				base++;
				dif--;
			}
			base += (40 - ((x2 - x1) / 16));
			curr_thick++;
		}
	}
}
/*
 * Reference: Paul Pospisil (January 2023)
 * 
 * Author: Kevin Oh 
 *
 * Purpose: Draws a single pixel to the screen
 *
 * Parameters:
 *   base       - byte sized pointer to the base frame buffer
 *   x          - X-coordinate on the screen
 *   y          - y-coordinate on the screen
 * 
 * Details:
 *      This function does bounds check for the screen size of the Atari ST,
 *		640 X 400 pixels and draws a single pixel to the x and y coordinate
 * 		specified by the user.
 *
 * Restrictions/Assumption:
 *  	x and y coordinates outside of the screen width/height will cause the function to not
 *		draw anything.
 *
 *  	All parameters are to be given in pixels
 *
 *  Sample call:
 *  	plot_pixel(base, 200, 350);
 */
void plot_pixel(char *base, int x, int y)
{
  	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
  	{
  	  	*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
  	}
}
/*
 * Author: Kevin Oh
 * 
 * Purpose: Draws a vertical line that is 16 bits thick
 *
 * Parameters:
 *   base       - Word sized pointer to the base frame buffer
 *   x          - X-coordinate on the screen for the top left of the line
 *   y1         - Y-coordinate on the screen for the top or bottom left of the line
 *   y2         - y-coordinate on the screen for the top or bottom left of the line
 * 
 * Details:
 *      The function draws a vertical line, with a specified y1 and y2 coordinate
 * 		that will indicate the top and bottom of the line for which the order specfied
 *		does not matter. This line will always be 16 pixels in width. 
 *
 * Restrictions/Assumptions:
 *  	This function assumes all input values to be valid/within bounds:
 *		x >= 0 && x < 640
 *		y1 >= 0 && y2 < 400
 *  	y2 >= 0 && y2 < 400
 *  
 *  	This function will draw to the closest word-aligned memory location smaller than x
 *  	if x is not evenly divisible by 16. 
 *  	i.e. 
 *			if x = 25, the vertical line will be drawn aligned with the top left bit
 *			in bit 16.
 *
 *  	All parameters are to be given in pixels
 *  	There are no restrictions on y1 or y2 other than the bounds stated above.
 *
 *  Sample call:
 *  	draw_vertical_line(base, 0, 256, 300);
 */
void draw_vertical_line(UINT16 *base, int x, int y1, int y2)
{
	int dif = 0;
	int curr_y;
	if (y2 > y1)
	{
		curr_y = y1;
		dif = y2 - y1;
	}
	if (y1 > y2)
	{
		curr_y = y2;
		dif = y1 - y2;
	}
	base += (x / 16);
	base += (curr_y * 40);

	while (dif > 0)
	{
		*base = 0xffff;
		base += 40;
		dif--;
	}

}
/*
 * Reference: Depanshu (February 2023)
 *
 * Author: Kevin Oh
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
 *  It supports bitmaps with widths that are multiples of 8 bits such as ( 8 x 8, 64 x 94, 96 x 1 ,etc ..)
 *  Behaviour will be undefined if the input parameters are not correct
 *  No error and bounds checking is provided
 *  User is responsible for providing the correct parameters
 *  Height, width, x and y inputs are to be given in pixels
 *
 *  Sample call:
 *  draw_multi_of_8_bitmap(buffer, x, y, height, width, sprite);
 */
void draw_multi_of_8_bitmap(UINT8 *base, int x, int y, int height, int width, UINT8 *bitmap)
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
