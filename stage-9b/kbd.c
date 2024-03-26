#include "kbd.h"
Kbd_Buffer kbd_buffer;
Vector orig_kbd_vector;

short kbd_state = KBD_STATE_NO_MOUSE;
volatile unsigned char *const IKBD_control  = 0xFFFFFC00;
volatile const unsigned char  *const IKBD_status  = 0xFFFFFC00;
volatile const SCANCODE *const IKBD_RDR  = 0xFFFFFC02;




void init_keyboard_isr() {
    kbd_buffer.rear = -1;
    kbd_buffer.front = -1;
    orig_kbd_vector = install_vector(KBD_VEC_NUM, kbd_isr);

}

void restore_keyboard_isr() {
    install_vector(KBD_VEC_NUM, orig_kbd_vector);
}



void kbd_driver() {
    unsigned char value = *IKBD_RDR;
    
    if (kbd_state == KBD_STATE_NO_MOUSE) {
        if ((value >> 2) == 0x3E) {
            kbd_state = KBD_STATE_2nd_MOUSE;
        } else {
            put_value_in_buffer(value);
        }

    } else if (kbd_state == KBD_STATE_2nd_MOUSE) {
        kbd_state = KBD_STATE_3rd_MOUSE;
    } else {
        kbd_state = KBD_STATE_NO_MOUSE;
    }
    
}




void put_value_in_buffer(unsigned char value) {
    char *scancode_2_ascii = (char *)((Keytbl(-1, -1, -1))->unshift);

    if( kbd_buffer.rear != kbd_buffer.front || is_buffer_empty() == TRUE)
    {
        if(kbd_buffer.front == BUFFER_EMPTY_VALUE)
            kbd_buffer.front = kbd_buffer.rear = 0;

        kbd_buffer.buffer[(kbd_buffer.rear)++] = scancode_2_ascii[value];
        kbd_buffer.rear &= KBD_BUFFER_SIZE - 1;
    }

}

bool is_buffer_empty() {
    return kbd_buffer.front == BUFFER_EMPTY_VALUE ? TRUE: FALSE;
}




unsigned char get_value_from_buffer() {
    unsigned char value = '\0';

    if(is_buffer_empty() == FALSE)
    {
        value = kbd_buffer.buffer[kbd_buffer.front++];

        kbd_buffer.front &= KBD_BUFFER_SIZE - 1;

        if(kbd_buffer.front == kbd_buffer.rear)
            kbd_buffer.front = kbd_buffer.rear = BUFFER_EMPTY_VALUE;
    }

    return value;


}