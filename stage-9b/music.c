#include "music.h"
#include <stdio.h>
/* Global Variables for Updating Music */
UINT32 melody_timing;
UINT32 bass_timing;
UINT16 tracker_bass;
UINT16 tracker_melody;
MUSIC_STATE music_state_tracker;

/*
* Purpose: Initializes and sets the tone, channel, envelope, and timing 
*          variables as necessary to play the very first instance of music
*
* Reference: Back on Track by DJVI (Geometry Dash Soundtrack)
*
*/
void start_music() {
    stop_sound();
    tracker_bass = 0;
    tracker_melody = 0;
    music_state_tracker = MUSIC_STATE_1;
    melody_timing = melody_notes[tracker_melody].timing;
    bass_timing = EIGHTH_NOTE;
    set_tone(CHANNEL_B, melody_notes[tracker_melody].note);
    set_tone(CHANNEL_A, bass_line[tracker_bass]);
    set_envelope(0x1000, 3);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    set_volume(CHANNEL_A, 0x10);
    set_volume(CHANNEL_B, 0xC);
    set_volume(CHANNEL_C, 0xA);
    tracker_bass++;
    tracker_melody++;
}

/*
* Purpose: Updates the tone, channel, envelope, and timing variables as
*          necessary to play the next instance of music
*
* Reference: Back on Track by DJVI (Geometry Dash Soundtrack)
*
* Input:
*       time_elapsed_melody - Pointer reference to the timing variable to indicate
*                             when the next melody note array element should be played
*
*       time_elapsed_bass - Pointer reference to the timing variable to indicate
*                             when the next bass note array element should be played
*
* Limitations: Must be called from main.
*/
void update_music(UINT32 *time_elapsed_melody, UINT32 *time_elapsed_bass) {

    if (*(time_elapsed_melody) > melody_timing) {
            melody_timing = melody_notes[tracker_melody].timing;

            if (melody_notes[tracker_melody].note != NOTE_PAUSE) {
               set_tone(CHANNEL_B, melody_notes[tracker_melody].note);
                enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
            } else {
               enable_channel(CHANNEL_B, TONE_OFF, NOISE_OFF);
            }
            if (music_state_tracker >= MUSIC_STATE_3) {
                if (melody_notes2[tracker_melody].note != NOTE_PAUSE) {
                   set_tone(CHANNEL_C, melody_notes2[tracker_melody].note);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
                } else {
                   enable_channel(CHANNEL_C, TONE_OFF, NOISE_OFF);
                }
            }
            tracker_melody++;
            if (tracker_melody == 22) {
                tracker_melody = 0;
                music_state_tracker++;
            }
            *time_elapsed_melody = 0;
        }
        if (*(time_elapsed_bass) > bass_timing) {
            if (tracker_bass > 62) {
                tracker_bass = 0;
            }
            if (bass_line[tracker_bass] != NOTE_PAUSE) {
                set_tone(CHANNEL_A, bass_line[tracker_bass]);
                enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                set_envelope(0x1000, 3);
                bass_timing = EIGHTH_NOTE;
            } else {
                enable_channel(CHANNEL_A, TONE_OFF, NOISE_OFF);
                bass_timing = NOTE_BUFFER;
            }
            tracker_bass++;
            *time_elapsed_bass = 0;
        }

     }