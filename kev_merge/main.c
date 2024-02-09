#include <osbind.h>
#include "raster.h"
#include "rast_asm.h"
#include "bitmaps.h"

int main() 
{
    
  int x1 = 623;
  int x2 = 639;

    UINT16  *base = Physbase();
    UINT8   *base2 = Physbase();
    UINT32  *base3 = Physbase();

    draw_multi_of_32_bitmap(base3, 0, 272, 128, 640, ground_test);

    
    
while(!Cconis()) {

    draw_triangle(base, x1, 240);
    
    Vsync();

    draw_triangle(base, x1, 240);
    x1--;


   /* draw_horizontal_line(base, x1, x2, 144, 1); */
    
}
   


    return 0;
}