#include "effects.h"
#include "PSG.h"

/*
* Purpose: Plays an explosion sound (for player death)
*
* Limitations: Uses all 3 audio channels, no other sounds can be played
*              along with this sound effect.
*
*/
void play_explosion_sound() {
    enter_super();
    set_tone(CHANNEL_A, G3);
    set_tone(CHANNEL_B, G1);
    set_tone(CHANNEL_C, G1);
    set_noise(0x0F);
    set_volume(CHANNEL_A, 0x10);
    set_volume(CHANNEL_B, 0x10);
    set_volume(CHANNEL_C, 0x10);
    set_envelope (0x3800, 0x00);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_ON);
    
    enable_channel(CHANNEL_B, TONE_ON, NOISE_ON);
    enable_channel(CHANNEL_C, TONE_ON, NOISE_ON);
    exit_super();
}
/*
* Purpose: Plays a selection sound for menu selection
*
* Limitations: Uses Channel A of the PSG
*
*/
void play_select_sound() {
    enter_super();
    set_tone(CHANNEL_A, G6);
    set_volume(CHANNEL_A, 0x10);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    set_envelope (0x00E0, 0x01);
    exit_super();

}