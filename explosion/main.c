#include "bitmap.h"
#include "raster.h"
#include <osbind.h>
#include "types.h"
#include "bool.h"
#include "input.h"
#define NO_INP_CHAR '\0'

UINT32 get_time();

int main () {

    UINT8* base = Physbase();
	UINT32* base2 = Physbase();
    Explosion_Animation explosion_counter = 0;
    

    UINT32 time_then, time_now, time_elapsed;
	char ch = NO_INP_CHAR;  /*value to indicate that a valid key was not pressed*/
    int user_quit = FALSE;



	time_then = get_time();
	draw_32_bit_bitmap(base2, 0, 0, 32, 32, player);
    while (user_quit == FALSE) {
       

		
		time_now = get_time();
		time_elapsed = time_now - time_then;
		
		if (time_elapsed > 7) {

            draw_8_bit_bitmap(base,0,0,32,32,explosion_images[explosion_counter]);
			if (explosion_counter < 7) {
				explosion_counter++;

			}
			else {
				explosion_counter = 0;
			}
            

                
			
                time_then = time_now;
		}
		
		ch = NO_INP_CHAR;
        user_input(&ch);
		user_quit = (ch == '\033');
		
	}






    while (user_quit == FALSE) {

        user_input(&ch);
        user_quit = (ch == '\033');
    }

    return 0;
}

UINT32 get_time(){
	UINT32 time_now;
	UINT32 old_ssp;
	UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */
	
	old_ssp = Super(0); /* enter privileged mode */
	time_now = *timer;
	Super(old_ssp); /* exit privileged mode */
	
	return time_now;
	
}