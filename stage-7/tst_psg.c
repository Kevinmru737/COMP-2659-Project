
#include "t_driver.h"
#include "PSG.h"
#include <stdio.h>
#include <osbind.h>
#include "input.h"



UINT32 get_time();


int main(){
    UINT32 time_now, time_then, time_elapsed;
    UINT32 time_now_melody, time_then_melody, time_elapsed_melody;
    int B_ON = 0;
    char input = NO_INP_CHAR;
    int tracker = 0;
    int tracker_melody = 0;
    int flopper = TRUE;
    int flopper_melody = TRUE;
    UINT8 melody_note_timing = QUARTER_NOTE;
    UINT8 bass_timing = QUARTER_NOTE;
    bool t1_is_done = FALSE;
    bool t2_is_done = FALSE;
    MUSIC_STATE music_state_tracker = MUSIC_STATE_1;
    /*
    write_psg(A_LEVEL, 0x1F); 
    write_psg(MIXER, MIXER_MASK_A);
    set_envelope(0x3, 9);
    set_volume(CHANNEL_A, 15);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_ON);
    */
    time_then = get_time();
    time_then_melody = get_time();

    
    while (input != ESC_KEY) {

        user_input(&input);

        time_now = get_time();
        time_elapsed = time_now - time_then;
        time_now_melody = get_time();
        time_elapsed_melody = time_now_melody - time_then_melody;
        /*
        if (t1_is_done == FALSE) {
            t1_is_done = test_driver_1();
        }
        if (t2_is_done == FALSE) {
            t2_is_done = test_driver_2();
        }*/

        if (time_elapsed_melody > melody_note_timing) {

            melody_note_timing = melody_notes[tracker_melody].timing;

            if (melody_notes[tracker_melody].note != NOTE_PAUSE) {
                set_tone(CHANNEL_B, melody_notes[tracker_melody].note);
                enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
                set_volume(CHANNEL_B, 0xC);
            } else {
                enable_channel(CHANNEL_B, TONE_OFF, NOISE_OFF);
            }

            

            if (music_state_tracker > MUSIC_STATE_3) {
                if (melody_notes2[tracker_melody].note != NOTE_PAUSE) {
                    set_tone(CHANNEL_C, melody_notes2[tracker_melody].note);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
                    set_volume(CHANNEL_C, 0xC);
                } else {
                enable_channel(CHANNEL_C, TONE_OFF, NOISE_OFF);
                }
            }
/*
            if (music_state_tracker >= MUSIC_STATE_5) {
                if (melody_notes2[tracker_melody].note != NOTE_PAUSE) {
                    set_tone(CHANNEL_C, melody_notes2[tracker_melody].note);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_ON);
                    write_psg(NOISE_FREQ, 0x00);
                    set_volume(CHANNEL_C, 0xC);
                } else {
                    enable_channel(CHANNEL_B, TONE_OFF, NOISE_OFF);
                }
                
            }*/
                
            

            tracker_melody++;

            if (tracker_melody == 22) {
                tracker_melody = 0;
                music_state_tracker++;
            }
            time_then_melody = time_now_melody;
        }



        if (time_elapsed > bass_timing) {

            if (tracker > 31) {
                tracker = 0;
            }
            if (flopper == TRUE) {
                set_tone(CHANNEL_A, bass_line[tracker]);
                enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                set_envelope(0x1000, 3);
                set_volume(CHANNEL_A, 0x10);
                tracker++;
                bass_timing = EIGHTH_NOTE;
                flopper = FALSE;
            } else {
                enable_channel(CHANNEL_A, TONE_OFF, NOISE_OFF);
                set_volume(CHANNEL_A, 0x0C);
                bass_timing = NOTE_BUFFER;
                flopper = TRUE;
                
            }

            time_then = time_now;
                
   
            
        }
        
        
        
        
    }


    stop_sound();
    

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

