
#include "t_driver.h"
#include "PSG.h"
#include <stdio.h>
#include <osbind.h>
#include "input.h"
#include "effects.h"
#include "music.h"

UINT32 get_time();

int main(){
    UINT32 time_now, time_then, time_elapsed;
    UINT32 time_elapsed_bass = 0, 
    time_elapsed_melody = 0;
    char input = NO_INP_CHAR;
    bool t1_is_done = FALSE;
    bool t2_is_done = FALSE;
    bool music_started = FALSE;
    
    time_then = get_time();
    while (input != ESC_KEY) {

        user_input(&input);
        time_now = get_time();
        time_elapsed = time_now - time_then;
        
        if (t1_is_done == FALSE) {
            t1_is_done = test_driver_1();
        }
        if (t2_is_done == FALSE) {
            t2_is_done = test_driver_2();
        }
        if (music_started == FALSE && input == ' ') {
            stop_sound();
            printf("Playing Game Music...\n\n");
            printf("Press ESC to exit the program at any time");
            start_music();
            music_started = TRUE;
        }
        if (music_started == TRUE) {
            if (time_elapsed > 0) {
                time_elapsed_melody++;
                time_elapsed_bass++;
                update_music(&time_elapsed_melody, &time_elapsed_bass);
                time_then = time_now;
            }
        }
    }
    stop_sound();
    return 0;
}




/*
* Purpose: returns the longword address 0x462 used as a measure of time.
*
* Details: the address should be auto incremented 70 times per second.
*
* Output: Returns a 32 bit unsigned value that represents the time passed.
*
*/
UINT32 get_time(){
	UINT32 time_now_bass;
	UINT32 old_ssp;
	UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */
	
	old_ssp = Super(0); /* enter privileged mode */
	time_now_bass = *timer;
	Super(old_ssp); /* exit privileged mode */
	
	return time_now_bass;
	
}
