#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

typedef unsigned int UINT16;

void draw_horizontal_line (UINT16 *base, int x1, int x2, int y, int thickness)
{
  int thick = 0;
  base += x1 + (y * 40);

  while (thick < thickness)
  { 
    int dif = (x2 - x1);  
    while (dif > 0)
    {
 	    *base |= 0xFFFF;
        base++;
        dif--;
    }
    base += (40 - (x2 - x1));
    thick++;
  }


}