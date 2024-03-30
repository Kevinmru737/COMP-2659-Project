#include "PSG.h"
#include <stdio.h>

/*
* Purpose: Writes a value to a specified register
*
* Input: 
*       reg - The register number to be written to
*       val - The value to be written to the specified register
*
* Limitations: Acceptable range of values for reg is 0 - 15.
*              The range of "valid" values vary from register to register
*              and should be checked via the YM2149 manual
*
*/
void write_psg(UINT8 reg, UINT8 val){
    volatile UINT8 *PSG_reg_select = PSG_REG_SELECT_ADDRESS;
    volatile UINT8 *PSG_reg_write  = PSG_REG_WRITE_ADDRESS;
    if(reg >= 0 && reg <=15) {
        *PSG_reg_select = reg;
        *PSG_reg_write = val;
    }

}

/*
* Purpose: Reads the value written to a specified register
*
* Input: 
*       reg - The register number to be read
*
* Output: Returns the value that the specified register holds
*
* Limitations: Acceptable range of values for reg is 0 - 15
*
*/
UINT8 read_psg(UINT8 reg){
    volatile UINT8 *PSG_reg_select = PSG_REG_SELECT_ADDRESS;
    UINT8 PSG_value;

    if (reg >= 0 && reg <= 15) {
        *PSG_reg_select = reg;
        PSG_value = *PSG_reg_select;        
    }


    return PSG_value;
}

/*
* Purpose: Changes the fine and coarse frequency of the tone of a specified channel
*
* Input: 
*       channel - Specifies the channel to be changed
*
*                 Channel A = 0
*                 Channel B = 1
*                 Channel C = 2
*
*       tuning - Must be passed as a 16 bit value where the MS byte is the coarse
*                  tuning value and the LS byte is the fine tuning value
*
*/
void set_tone(UINT8 channel, UINT16 tuning){
    UINT16 coarse_tuning, fine_tuning;

    if(channel >= 0 && channel <= 2 && tuning >= 0 && tuning <= 0xFFF) {
        coarse_tuning = (tuning >> 8);  
        fine_tuning = tuning & 0xFF;
        write_psg(channel << 1,(UINT8) fine_tuning);
        write_psg((channel << 1) + 1, (UINT8) coarse_tuning);
    }

}

/*
* Purpose: Changes the volume for a specified channel
*
* Input: 
*       channel - Specifies the channel to be changed
*
*                 Channel A = 0
*                 Channel B = 1
*                 Channel C = 2
*
*        volume - Specifies the new volume settings
*
* Limitations: Acceptable volume values range from 0x00 to 0x1F
*
*/
void set_volume(UINT8 channel, UINT8 volume){
    if(channel >= 0 && channel <= 2 && volume >= 0 && volume <= 0x1F) {
        write_psg(8 + channel, volume);
    }
}


/*
* Purpose: Enables or disables tones and noises for a specified channel
*
* Input: 
*       channel - Specifies the channel to be changed
*
*                 Channel A = 0
*                 Channel B = 1
*                 Channel C = 2
*
*       tone_on - Specifies whether the tone should be turned on or off
*
*                 tone_on == 1 /*indicates to turn the tone on
*                 tone_on == 0 /*indicates to turn the tone off
*
*      noise_on - Specifies whether the tone should be turned on or off
*
*                 noise_on == 1 /*indicates to turn the noice on
*                 tone_on == 0 /*indicates to turn the noise off
*
*/
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on) {
    UINT8 tone_bit, noise_bit, new_mixer_setting;

    if (channel >= 0 && channel <= 2 && tone_on <= 1 && tone_on >= 0 &&
        noise_on <= 1 && noise_on >= 0) {
        
        tone_bit = 1 << channel;
        noise_bit = 1 << (channel + 3);
        new_mixer_setting = read_psg(MIXER);

        if (tone_on == 1) {                 /*indicates a request to turn the tone on*/
            new_mixer_setting &= ~tone_bit;
        } else {                            /*indicates a request to turn the tone off*/
            new_mixer_setting |= tone_bit;
        }
        if (noise_on == 1) {                /*indicates a request to turn the noise on*/
            new_mixer_setting &= ~noise_bit;
            
        } else {                            /*indicates a request to turn the noise off*/
            new_mixer_setting |= noise_bit;
        }
        write_psg(MIXER, new_mixer_setting);
    }
}

/*
* Purpose: Sets noise frequency
*
* Input: 
*       tuning - The frequency to be written to the right register
*
* Limitations: Noise frequency has an allowable range of 0x00 to 0x1F
*
*/
void set_noise(UINT8 tuning) {
    write_psg(NOISE_FREQ, tuning);
}

/*
* Purpose: Sets the envelope frequency and shape
*
* Input: 
*       envelope - Must be passed as a 16 bit value where the MS byte is the coarse
*                  tuning value and the LS byte is the fine tuning value
*
*       shape    - Defines the envelope shape, see the YM2149 manual for details
*
*/
void set_envelope(UINT16 envelope, UINT8 shape) {
     UINT16 coarse_tuning, fine_tuning;
  
        coarse_tuning = (envelope >> 8);  
        fine_tuning = envelope & 0xFF;
        write_psg(ENV_FREQ_FINE,(UINT8) fine_tuning);
        write_psg(ENV_FREQ_COARSE, (UINT8) coarse_tuning);
        write_psg(ENV_SHAPE, shape);

}

/*
* Purpose: stop_sound clears all sound card registers, which also stops any
*          sound from being output
*
* Details: Sets all register values that may have been changed, to 0
*
* Limitations: Only clears the registers that can be changed via the other functions
*              in this module
*/
void stop_sound() {
    set_tone(CHANNEL_A, 0);
    set_tone(CHANNEL_B, 0);
    set_tone(CHANNEL_C, 0);
    write_psg(NOISE_FREQ, 0);
    write_psg(MIXER, 0xFF);
    write_psg(A_LEVEL, 0);
    write_psg(B_LEVEL, 0);
    write_psg(C_LEVEL, 0);
    set_envelope(0, 0);
}

/**** Note arrays for playing music ****/

const Note melody_notes[] = {
    {D4, QUARTER_NOTE}, {A3_SHARP, QUARTER_NOTE}, {NOTE_PAUSE, QUARTER_NOTE},
    {G4, QUARTER_NOTE}, {F4, QUARTER_NOTE}, {D4_SHARP, QUARTER_NOTE},
    {A3_SHARP, QUARTER_NOTE}, {C4, EIGHTH_NOTE}, {D4, EIGHTH_NOTE},
    {NOTE_PAUSE, NOTE_BUFFER},
    {D4, QUARTER_NOTE}, {A3_SHARP, QUARTER_NOTE}, {NOTE_PAUSE, QUARTER_NOTE},
    {D4_SHARP, EIGHTH_NOTE}, {NOTE_PAUSE, EIGHTH_NOTE}, {C4, QUARTER_NOTE},
    {A3_SHARP, EIGHTH_NOTE}, {C4, EIGHTH_NOTE}, {F4, QUARTER_NOTE},
    {D4_SHARP, EIGHTH_NOTE}, {D4, EIGHTH_NOTE}, {NOTE_PAUSE, NOTE_BUFFER}
};

const UINT16 bass_line[] = {
    G1, NOTE_PAUSE, G1, NOTE_PAUSE, G1, NOTE_PAUSE, 
    G1, NOTE_PAUSE, G1, NOTE_PAUSE, G1, NOTE_PAUSE,
    G1, NOTE_PAUSE, G1, NOTE_PAUSE,
    D1_SHARP, NOTE_PAUSE, D1_SHARP, NOTE_PAUSE,
    D1_SHARP, NOTE_PAUSE, D1_SHARP, NOTE_PAUSE,
    D1_SHARP, NOTE_PAUSE, D1_SHARP, NOTE_PAUSE,
    D1_SHARP, NOTE_PAUSE, D1_SHARP, NOTE_PAUSE,
    F1, NOTE_PAUSE, F1, NOTE_PAUSE, F1, NOTE_PAUSE, 
    F1, NOTE_PAUSE, F1, NOTE_PAUSE, F1, NOTE_PAUSE,
    F1, NOTE_PAUSE, F1, NOTE_PAUSE,
    A1_SHARP, NOTE_PAUSE, A1_SHARP, NOTE_PAUSE,
    A1_SHARP, NOTE_PAUSE, A1_SHARP, NOTE_PAUSE,
    A1_SHARP, NOTE_PAUSE, A1_SHARP, NOTE_PAUSE,
    A1_SHARP, NOTE_PAUSE, A1_SHARP, NOTE_PAUSE
};

const Note melody_notes2[] = {
    {D6, QUARTER_NOTE}, {A5_SHARP, QUARTER_NOTE}, {NOTE_PAUSE, QUARTER_NOTE},
    {G6, QUARTER_NOTE}, {F6, QUARTER_NOTE}, {D6_SHARP, QUARTER_NOTE},
    {A5_SHARP, QUARTER_NOTE}, {C6, EIGHTH_NOTE}, {D6, EIGHTH_NOTE},
    {NOTE_PAUSE, NOTE_BUFFER},
    {D6, QUARTER_NOTE}, {A5_SHARP, QUARTER_NOTE}, {NOTE_PAUSE, QUARTER_NOTE},
    {D6_SHARP, EIGHTH_NOTE}, {NOTE_PAUSE, EIGHTH_NOTE}, {C6, QUARTER_NOTE},
    {A5_SHARP, EIGHTH_NOTE}, {C6, EIGHTH_NOTE}, {F6, QUARTER_NOTE},
    {D6_SHARP, EIGHTH_NOTE}, {D6, EIGHTH_NOTE}, {NOTE_PAUSE, NOTE_BUFFER}
};


