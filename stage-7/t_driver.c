#include "t_driver.h"
#include <stdio.h>

typedef enum {
    TEST_WRITE_PSG_1,
    TEST_WRITE_PSG_2,
    TEST_WRITE_PSG_3,
    TEST_WRITE_PSG_4,
    TEST_WRITE_PSG_5,
    TEST_WRITE_PSG_6,
    TEST_WRITE_PSG_7,
    TEST_WRITE_PSG_8,
    TEST_WRITE_PSG_9,
    TEST_WRITE_PSG_10,
    TEST_WRITE_PSG_11,
    TEST_WRITE_PSG_12,
    TEST_WRITE_PSG_13,
    TEST_WRITE_PSG_14,
    TEST_WRITE_PSG_15,
    TEST_WRITE_PSG_16,
    TEST_WRITE_PSG_17,
    TEST_WRITE_PSG_18,
    TEST_WRITE_DONE
} TEST_CASES_WRITE_PSG;



UINT8 test_values [] = {
    0xCD, 0xA, 0x34, 0x1, 0x78, 0x5,
    0x1A, 0x3E, 0x1F, 0x1A, 0x05, 0x4F,
    0x8D, 0x04
};

UINT8 expected_values [] = {
    0xCD, 0xA, 0x34, 0x1, 0x78, 0x5,
    0x1A, 0x3E, 0x1F, 0x1A, 0x05, 0x4F,
    0x8D, 0x04
};

const char *channel_strings [] = {
    "Channel A - Fine",
    "Channel A - Coarse",
    "Channel B - Fine",
    "Channel B - Coarse",
    "Channel C - Fine",
    "Channel C - Coarse",
    "Noise Frequency",
    "Mixer Settings",
    "A Level Control",
    "B Level Control",
    "C Level Control",
    "Envelope Fine Freq",
    "Envelope Coarse Freq",
    "Envelope Shape"
};

const UINT8 channel_names [] = {
    CHANNEL_A_FINE,
    CHANNEL_A_COARSE,
    CHANNEL_B_FINE,
    CHANNEL_B_COARSE,
    CHANNEL_C_FINE,
    CHANNEL_C_COARSE,
    NOISE_FREQ,
    MIXER,
    A_LEVEL,
    B_LEVEL,
    C_LEVEL,
    ENV_FREQ_FINE,
    ENV_FREQ_COARSE,
    ENV_SHAPE 
};
/*
* Purpose: test_driver_1 tests write_psg, read_psg, and set_tone from PSG.c
*
* Details: Compares expected values with the actual values of the register using
*          read_psg
*
* Limitations: Register 14-15 are not tested because they are not planned to be used.
*
*/
bool test_driver_1() {
    int i = 0;
    char input = NO_INP_CHAR;
    TEST_CASES_WRITE_PSG test_counter = TEST_WRITE_PSG_1;
    printf("***Test Driver 1 simply tests setting tones and writing to all used \n\tregisters and reading them***\n\n");

    printf("Press ESC to exit the test driver 1...\n\n");

    printf("Press Spacebar to execute the next test...\n");

    printf("Setting tones to Channels A, B and C (Fine and Course)...\n\n");
    
    while (input != ESC_KEY) {
        user_input(&input);


        if(input == ESC_KEY) {
            printf("Returning to main program...\n\nPress ESC to Exit the main program\n\n");
            return TRUE;
        }

        if(input == ' ') {
            input = NO_INP_CHAR;

            if(test_counter == TEST_WRITE_PSG_7) {
                    printf("Writing/reading for register 6 - 13 (registers 14 & 15 are never used)...\n\n");
            }
            if (test_counter < 14) {
                printf("Moving the value '%X' into Register %d (%s)...\n\n",
                    test_values[test_counter], test_counter, channel_strings[test_counter]);
            }

            

            
            switch (test_counter) {
                case TEST_WRITE_PSG_1:
                    
                    set_tone(CHANNEL_A, 0xACD);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_2:
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_3:
                    set_tone(CHANNEL_B, 0x134);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_4:
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_5:
                    set_tone(CHANNEL_C, 0x578);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_6:
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_7:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_8:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_9:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_10:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_11:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_12:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_13:
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_14:
                    set_volume(CHANNEL_A, 0x00);
                    set_volume(CHANNEL_B, 0x00);
                    write_psg(channel_names[test_counter], test_values[test_counter]);
                    test_counter = TEST_WRITE_DONE;
                    break;

                case TEST_WRITE_DONE:
                    printf("Done with Test Driver 1...\n\n");
                    return TRUE;

            }
            if (expected_values[test_counter - 1] == read_psg(channel_names[test_counter - 1])){
                printf("Register value is %u vs expected %u: *** PASSED *** \n\n",
                        read_psg(channel_names[test_counter - 1]), expected_values[test_counter - 1]);
            } else {
                printf("Register value is %u vs expected %u: *** FAILED *** \n\n",
                        read_psg(channel_names[test_counter - 1]), expected_values[test_counter - 1]);
            }



            
            
        }
    }
    


}
/*
* Purpose: test_driver_2 tests set_volume, enable_channel and stop_sound from PSG.c
*
* Details: Testing is done via hearing the audio
*
* Limitations: Need audio turned on
*
*/
bool test_driver_2() {
    int i = 0;
    char input = NO_INP_CHAR;
    TEST_CASES_WRITE_PSG test_counter = TEST_WRITE_PSG_14;
    printf("***Test Driver 2 tests setting volumes and enabling channels (Turn Sound On) ***\n\n");

    printf("Press ESC to exit the test driver 2...\n\n");

    printf("Press Spacebar to execute the next test...\n");

    while (test_counter != TEST_WRITE_DONE && input != ESC_KEY) {
        user_input(&input);

        if(input == ESC_KEY) {
            printf("Returning to main program...\n\nPress ESC to Exit the main program\n\n");
            return TRUE;
        }

        if(input == ' ') {
            
            input = NO_INP_CHAR;

            switch (test_counter) {
                case TEST_WRITE_PSG_1:
                    stop_sound();
                    printf("Setting the tone as 'G1' into Channel A...\n");
                    printf("Volume = 12\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    
                    set_tone(CHANNEL_A, G1);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                    set_volume(CHANNEL_A, 0x0C);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_2:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_3:
                    printf("Setting the tone as 'D1_SHARP' into Channel B...\n");
                    printf("Volume = 12\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    set_tone(CHANNEL_B, D1_SHARP);
                    set_volume(CHANNEL_B, 12);
                    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_4:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_5:
                    printf("Setting the tone as 'F1' into Channel C...\n");
                    printf("Volume = 12\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    set_tone(CHANNEL_C, F1);
                    set_volume(CHANNEL_C, 12);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_6:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;
 
                case TEST_WRITE_PSG_7:
                    printf("Channel A Tone: G3\n");
                    printf("Channel B Tone: D3_SHARP\n");
                    printf("Channel C Tone: F3\n");
                    printf("Volume = 12\n");
                    printf("Enabling Channels...\n\n");
                    printf("Press Spacebar to stop sound\n\n");

                    set_tone(CHANNEL_A, G3);
                    set_volume(CHANNEL_A, 12);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);

                    set_tone(CHANNEL_B, D3_SHARP);
                    set_volume(CHANNEL_B, 12);
                    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);

                    set_tone(CHANNEL_C, F3);
                    set_volume(CHANNEL_C, 12);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_8:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_9:
                    printf("Channel A Tone: G3\n");
                    printf("Volume = 12\n");
                    printf("Envelope Frequency: 0x90\n");
                    printf("Envelope Shape : 0x08\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    set_tone(CHANNEL_A, G3);
                    set_volume(CHANNEL_B, 0x1C); /* enabling envelope */
                    set_envelope (0x90, 0x08);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_10:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_11:
                    printf("Noise Frequency: 1F\n");
                    printf("Tone is off for A, B and C, and only Noise is on for all 3 channels\n");
                    printf("Enabling Channel A, B and C...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    write_psg(NOISE_FREQ, 0x1F);
                    set_volume(CHANNEL_A, 0x10);
                    set_volume(CHANNEL_B, 0x10);
                    set_volume(CHANNEL_C, 0x10); /* enabling envelope */
                    set_envelope (0x3800, 0x00);
                    enable_channel(CHANNEL_A, TONE_OFF, NOISE_ON);
                    enable_channel(CHANNEL_B, TONE_OFF, NOISE_ON);
                    enable_channel(CHANNEL_C, TONE_OFF, NOISE_ON);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_12:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_13:
                    printf("Noise Frequency: 0F\n");
                    printf("Tone is G3, G1 and G1 for A, B and C\nNoise is on for all 3 channels\n");
                    printf("Enabling Channel A, B and C...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    set_tone(CHANNEL_A, G3);
                    set_tone(CHANNEL_B, G1);
                    set_tone(CHANNEL_C, G1);
                    write_psg(NOISE_FREQ, 0x0F);
                    set_volume(CHANNEL_A, 0x10);
                    set_volume(CHANNEL_B, 0x10);
                    set_volume(CHANNEL_C, 0x10); /* enabling envelope */
                    set_envelope (0x3800, 0x00);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_ON);
                    enable_channel(CHANNEL_B, TONE_ON, NOISE_ON);
                    enable_channel(CHANNEL_C, TONE_ON, NOISE_ON);
                    test_counter++;
                    break;
                
                case TEST_WRITE_PSG_14:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_15:
                    printf("Setting the tone as 'G1' into Channel A...\n");
                    printf("Envelope Frequency: 0x1000\n");
                    printf("Envelope Shape: 3\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    
                    set_tone(CHANNEL_A, G1);
                    write_psg(NOISE_FREQ, 0x07);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                    set_envelope(0x1000, 3);
                    set_volume(CHANNEL_A, 0x10);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_16:
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_PSG_17:
                    printf("Setting the tone as 'G3' into Channel A...\n");
                    printf("Volume = 12\n");
                    printf("Noise Frequency:\n");
                    printf("Envelope:\n");
                    printf("Enabling Channel...\n\n");
                    printf("Press Spacebar to stop sound\n\n");
                    
                    set_tone(CHANNEL_A, G1);
                    write_psg(NOISE_FREQ, 0x03);
                    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
                    set_envelope(0xCC, 0xE);
                    set_volume(CHANNEL_A, 0x10);
                    test_counter++;
                    break;
                case TEST_WRITE_PSG_18  :
                    printf("Press Spacebar to continue...\n\n");
                    stop_sound();
                    test_counter++;
                    break;

                case TEST_WRITE_DONE:
                    stop_sound();
                    printf("Returning to main program...\n\nPress ESC to Exit the main program\n\n");
                    return TRUE;
                    break;


            }


            
            
        }
    }
    



    return TRUE;
}