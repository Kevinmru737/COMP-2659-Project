#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"


typedef void TEST;
TEST draw_multiple_of_32_bit_bitmaps();




int main()
{
    int x = 0;

    UINT16* base = Physbase();
    UINT32* base2 = Physbase();

    draw_multi_of_32_bitmap(base2, 0, 272, 128, 640, ground_640_x_128);
  /* 
    while(!Cconis()) {

        draw_multi_of_32_bitmap(base2, x, 240, 32, 32, cube_32_x_32);
    
        Vsync();
        draw_multi_of_32_bitmap(base2, x, 240, 32, 32, cube_32_x_32);

     x +=1;
	
	    if(x > 607) {
    	    x = 0;
        }
    }
*/

while(!Cconis()) {

    draw_multi_of_16_bitmap(base, x, 33, 16, 16, invader_16_x_16);    
    
    Vsync();
    
    draw_multi_of_16_bitmap(base, x, 33, 16, 16, invader_16_x_16);
    
    x +=1;
	
    if(x > 607) {
   	    x = 0;
    }



}
   


    return 0;
}

/*
*Purpose: This function is for testing draw_multi_of_32_bitmap
*
*Details:
*
*
*Test Cases: 
*           1: Draws a bitmap with the smallest posiible width
*           2: Draws a bitmap with the largest possible width
*           3: Draws properly even if the starting drawing position is not alligned
*           4: Drawing the same image twice will restore the area where the image was drawn
*           5: A reduntant check to make sure it can draw bitmap of variable lengths within its limits
*/

TEST draw_multiple_of_32_bit_bitmaps() {

int x = 0, y = 0;
/*--------TEST 1-----*/

draw_multi_of_32_bitmap(Physbase(), x, 240, 32, 32, cube_32_x_32);

draw_multi_of_16_bitmap(Physbase(), 40, 240, 16, 16, invader_16_x_16);


}
