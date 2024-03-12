#ifndef PSG_H
#define PSG_H
#include "types.h"
#include <osbind.h>

#define PSG_REG_SELECT_ADDRESS 0xFF8800
#define PSG_REG_WRITE_ADDRESS 0xFF8802
#define MIXER_REGISTER 7


#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2



void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);

void stop_sound();

#endif PSG_H
