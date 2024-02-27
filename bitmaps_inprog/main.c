#include "bitmap.h"
#include "raster.h"
#include <osbind.h>

int main () {

    UINT32* base = Physbase();
    
    draw_32_bit_bitmap(base,250,200,32,32,platform_32_32);
    draw_32_bit_bitmap(base,400,200,32,32,platform_32_32);

    draw_32_bit_bitmap(base,100,200,32,32,brick_32_32);
    draw_32_bit_bitmap(base,132,200,32,32,brick_32_32);

    draw_32_bit_bitmap(base,200,198,32,32,brick_32_32);
    draw_32_bit_bitmap(base,200,167,32,32,brick_32_32);
    draw_32_bit_bitmap(base,200,136,32,32,brick_32_32);
/*
    draw_32_bit_bitmap(base,164,198,32,32,brick_32_32_2);
    draw_32_bit_bitmap(base,164,168,32,32,brick_32_32_2);
    draw_32_bit_bitmap(base,164,138,32,32,brick_32_32_2);
*/

    draw_32_bit_bitmap(base,250,168,32,32,player);

    draw_32_bit_bitmap(base,300,168,16,32,platform_32_16);
    draw_32_bit_bitmap(base,330,168,16,32,platform_32_16);

    return 0;
}