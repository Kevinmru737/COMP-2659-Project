
#include "ISRS.h"

typedef unsigned char SCANCODE;
volatile unsigned char *const IKBD_control  = 0xFFFFFC00;
volatile const unsigned char  *const IKBD_status  = 0xFFFFFC00;
volatile const SCANCODE *const IKBD_RDR  = 0xFFFFFC02;
volatile unsigned char *const MIDI_CONTROLLER  =0xFFFFFA11;

#define DISABLE_RECEIVE_INTERRUPTS_CODE	0x16
#define ENABLE_RECEIVE_INTERRUPTS_CODE	0x96



short timer = 0;

Input_Buffer  input_buffer;

/*
 * Purpose: Process all the synchronous events in the game. Since the game runs at
 *          35 hz, it only processes synchronous events for every second clock tick.
 */

void process_vbl_isr() {
    timer++;
    if (timer == 2)
    {
        update_level(&model, &game_state);
        update_game_objects(&model, &fatal_collision);
        fatal_collision = player_fatal_collision(&model, 0);
        render_request = 1;
        timer = 0;
    }
}



/*
 * Purpose: Installs a new isr at the specified vector location. Num is the vector number
 *          to replace and vector is the new isr.
 */
Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);

    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}







void init_keyboard_isr() {
    *MIDI_CONTROLLER = DISABLE_RECEIVE_INTERRUPTS_CODE;
    input_buffer.back = -1;
    input_buffer.front = -1;
}

void restore_keyboard_isr() {
    *MIDI_CONTROLLER = ENABLE_RECEIVE_INTERRUPTS_CODE;
}



void process_keyboard_driver_isr() {
    unsigned char value = *IKBD_RDR;


    if( input_buffer.rear != input_buffer.front)
    {
        if(input_buffer.front == BUFFER_EMPTY_VALUE)
            input_buffer.front = input_buffer.rear = 0;

        input_buffer.buffer[(input_buffer.rear)++] = value;
        input_buffer.rear &= KBD_BUFFER_SIZE - 1;
    }

}

bool is_buffer_empty() {
    return input_buffer.front == BUFFER_EMPTY_VALUE ? TRUE: FALSE:
}

unsigned char get_value_from_buffer() {
    unsigned char value = '\0';

    if(is_buffer_empty() == FALSE)
    {
        value = input_buffer.buffer[input_buffer.front++];
        input_buffer.front &= KBD_BUFFER_SIZE - 1;

        if(input_buffer.front == input_buffer.rear)
            input_buffer.front = input_buffer.rear = BUFFER_EMPTY_VALUE;
    }

    return value;


}
