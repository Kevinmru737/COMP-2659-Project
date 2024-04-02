#ifndef PSG_H
#define PSG_H
#include "consts.h"
#include "rast_asm.h"

/*
* PSG.h is a library of functions designed to write and read to the
* Atari's PSG.
*
* Included within this library are a number of constants defining notes,
* note timings and other useful constants for writing to registers.
*
* See the YM2149 Manual for further details...
*
*/

#define PSG_REG_SELECT_ADDRESS 0xFF8800
#define PSG_REG_WRITE_ADDRESS 0xFF8802
#define PSG_ENABLE_CHANNEL_REG 0 /*change this*/

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

/* YM2149 Register Values */
#define CHANNEL_A_FINE 0
#define CHANNEL_A_COARSE 1
#define CHANNEL_B_FINE 2
#define CHANNEL_B_COARSE 3
#define CHANNEL_C_FINE 4
#define CHANNEL_C_COARSE 5
#define NOISE_FREQ 6
#define MIXER 7
#define A_LEVEL 8
#define B_LEVEL 9
#define C_LEVEL 10
#define ENV_FREQ_FINE 11
#define ENV_FREQ_COARSE 12
#define ENV_SHAPE 13

#define TONE_ON 1
#define NOISE_ON 1
#define TONE_OFF 0
#define NOISE_OFF 0

/* melody */
#define D4       0x17D
#define A3_SHARP 0X1E0
#define G4       0X11D
#define F4       0X140
#define D4_SHARP 0X168
#define C4       0x1AC

/* melody 2*/
#define D6       0x05F
#define A5_SHARP 0X078
#define G6       0X047
#define F6       0X050
#define D6_SHARP 0X05A
#define C6       0x06B

/* bass_line */
#define G1       0x8EB
#define D1_SHARP 0xB3C
#define F1       0xA02
#define A1_SHARP 0x780

/* extra useful note things*/
#define NOTE_BUFFER  0
#define NOTE_PAUSE 0

/* effect notes */
#define G3 0x23B

/* TIMING CONSTANTS */
#define EIGHTH_NOTE  6
#define QUARTER_NOTE 12
#define HALF_NOTE    24
#define WHOLE_NOTE   48


typedef struct {
    UINT16 note;
    UINT8 timing;
}Note;

typedef enum {
    MUSIC_STATE_1,
    MUSIC_STATE_2,
    MUSIC_STATE_3,
    MUSIC_STATE_4,
    MUSIC_STATE_5,

}MUSIC_STATE;

void write_psg(UINT8 reg, UINT8 val);
UINT8 read_psg(UINT8 reg);
void set_tone(UINT8 channel, UINT16 tuning);
void set_volume(UINT8 channel, UINT8 volume);
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on);
void set_noise(UINT8 tuning);
void set_envelope(UINT16 envelope, UINT8 shape);
void stop_sound();

extern const Note melody_notes[];
extern const UINT16 bass_line[];
extern const Note melody_notes2[];
#endif
