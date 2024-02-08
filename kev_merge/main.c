#include <osbind.h>
#include "raster.h"
#include "rast_asm.h"

int main() 
{
    
  int x1 = 0;
  int x2 = 15;

    UINT16* base = Physbase();
    char*   base2 = Physbase();
    UINT32* base3 = Physbase();

 
while(!Cconis()) {

    draw_horizontal_line(base, x1, x2, 144, 1);    
    
    Vsync();
    
    clear_screen(base3);
   /* draw_horizontal_line(base, x1, x2, 144, 1); */
    
    x1 +=1;
    x2 += 1;
	
    if(x2 > 639) {
   	    x1 = 0;
        x2 = 15;
    }



}
   


    return 0;
}