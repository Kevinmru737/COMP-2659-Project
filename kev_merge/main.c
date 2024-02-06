#include <osbind.h>
#include "raster.h"

int main() 
{
    UINT16* base = Physbase();
    UINT8* base2 = Physbase();
    UINT8 sprite[8] =
        {
            0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c
        };
    /*
    draw_horizontal_line(base, 25, 256, 100, 1);
    draw_horizontal_line(base, 25, 263, 105, 8);

    draw_horizontal_line(base, 16, 263, 95, 1);

    draw_horizontal_line(base, 25, 267, 90, 3);

    draw_horizontal_line(base, 25, 31, 80, 3);
    draw_horizontal_line(base, 32, 47, 83, 3);

    draw_vertical_line(base, 250, 100, 300);
    draw_vertical_line(base, 460, 256, 300);

*/
    draw_multi_of_8_bitmap(base2, 400, 300, 8, 8, sprite);


    return 0;
}