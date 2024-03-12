#include "PSG.h"

void write_psg(int reg, UINT8 val){
    volatile unsigned char *PSG_reg_select = PSG_REG_SELECT_ADDRESS;
    volatile unsigned char *PSG_reg_write  = PSG_REG_WRITE_ADDRESS;
    UINT32 old_ssp;
    if(reg >= 0 && reg <=15) {
        old_ssp = Super(0); /* enter privileged mode */
        *PSG_reg_select = reg;
        *PSG_reg_write = val;
        Super(old_ssp); /* exit privileged mode */
    }

}


UINT8 read_psg(int reg){



}



void set_tone(int channel, UINT16 tuning){
    UINT16 coarse_tuning, fine_tuning;
    if(channel >= 0 && channel <= 2 && tuning >= 0 && tuning <= 0xFFF) {
        coarse_tuning= (tuning >> 8);  
        fine_tuning = tuning & 0xFF;
        write_psg(channel << 1,(UINT8) fine_tuning);
        write_psg((channel << 1) + 1, (UINT8) coarse_tuning);
    }

}

void set_volume(int channel, UINT8 volume){
    
    if(channel >= 0 && channel <= 2 && volume >= 0 && volume <= 0x1F) {
        write_psg(8 + channel, volume);
    }
}



void enable_channel(int channel, UINT8 tone_on, UINT8 noise_on) {
    UINT8 tone_bit, noise_bit, new_mixer_setting;

    if (channel >= 0 && channel <= 2 && tone_on <= 1 && tone_on >= 0 &&
        noise_on <= 1 && noise_on >= 0) {
            
        tone_bit = (UINT8) 1 << channel;
        noise_bit = (UINT8) 1 << (channel + 3);

        new_mixer_setting = read_psg(PSG_ENABLE_CHANNEL_REG);


        if (tone_on == 1) {
            new_mixer_setting |= tone_bit;
        } else {
            new_mixer_setting &= ~tone_bit;
        }

        if (noise_on == 1) {
            new_mixer_setting |= noise_bit;
        } else {
            new_mixer_setting &= ~noise_bit;
        }

    
        write_psg(PSG_ENABLE_CHANNEL_REG, new_mixer_setting);

    }

}



void stop_sound() {
    write_psg(8, 0);
    write_psg(9, 0);
    write_psg(10, 0);
}


