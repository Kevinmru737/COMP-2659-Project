#ifndef PSG_H
#define PSG_H
#include "types.h"
#include <osbind.h>

#define PSG_REG_SELECT_ADDRESS 0xFF8800
#define PSG_REG_WRITE_ADDRESS 0xFF8802
#define PSG_ENABLE_CHANNEL_REG 0 /*change this*/



#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

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

#define MIXER_MASK_A 0x3E
#define MIXER_MASK_B 0x3C
#define MIXER_MASK_C 0x38

#define TONE_ON 1
#define NOISE_ON 1
#define TONE_OFF 0
#define NOISE_OFF 0

#define D6_FLAT_FINE 0x5f
#define D6_FLAT_COARSE 0x0 

#define A5_SHARP_FINE 0x78
#define A5_SHARP_COARSE 0x0


#define G6_FLAT_FINE 0x47
#define G6__FLAT_COARSE 0x0

#define F6_FLAT_FINE 0x50
#define F6__FLAT_COARSE 0x0


#define D6_SHARP_FINE 0x5a
#define D6_SHARP_COARSE 0x0

#define A5_SHARP_FINE 0x78
#define A5_SHARP_COARSE 0x0

#define B5 0x071

#define G5 0x08F

#define B6 0x0039

#define C6_FLAT_FINE  0x6b
#define C6_FLAT_COARSE 0x0
/* notes1 */
#define G3       0x23B

#define D3_SHARP 0x02CF

#define F3       0x281

#define A2_SHARP 0x0C03

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


#define NOTE_PAUSE 0

/* bass_line */
#define G1       0x8EB
#define D1_SHARP 0xB3C
#define F1       0xA02
#define A1_SHARP 0x780



/* TIMING CONSTANTS */
/*
#define WHOLE_NOTE 70
#define HALF_NOTE 35
#define QUARTER_NOTE 15
#define EIGTH_NOTE 7
*/

/* stuff Michael added */
#define NOTE_BUFFER 0
#define EIGHTH_NOTE   (12)
#define QUARTER_NOTE (EIGHTH_NOTE << 1)
#define HALF_NOTE    (QUARTER_NOTE << 1)
#define WHOLE_NOTE   (HALF_NOTE << 1)
/* Remove if you want */


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
void set_envelope(UINT16 envelope, UINT8 shape);
void stop_sound();


extern const Note melody_notes[];
extern const UINT16 bass_line[];
extern const Note melody_notes2[];
#endif
