#include "kbd.h"

Kbd_Buffer kbd_buffer;
Vector orig_kbd_vector;

short mouse_state = NO_MOUSE_STATE;

volatile const unsigned char *const IKBD_RDR  = 0xFFFFFC02;
volatile unsigned char *const INTERUPT_ENABLE	= 0xFFFFFA09;
#define NULL_CHAR '\0'

typedef enum {
    No_Special_Key,
    Caps_Lock_On,
    Left_Shift_Held,
    Right_Shift_Held
} KEY_STATE;

KEY_STATE key_state = No_Special_Key;

/*KEY tables, scancodes are used as indeces. Each element is an asci value*/
unsigned char caps_lock[] = {
0x0, 0x1b, 0x31, 0x32,
0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 
0x2d, 0x3d, 0x8, 0x9, 0x51, 0x57, 0x45, 0x52, 0x54, 
0x59, 0x55, 0x49, 0x4f, 0x50, 0x5b, 0x5d, 0xd, 0x0, 
0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4a, 0x4b, 0x4c, 0x3b, 0x27, 
0x60, 0x0, 0x5c, 0x5a, 0x58, 0x43, 0x56, 0x42, 0x4e, 0x4d, 0x2c, 0x2e, 
0x2f, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x0, 0x2b, 0x0, 0x0, 0x0, 
0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x28, 0x29, 0x2f, 0x2a, 0x37, 0x38, 0x39, 0x34, 0x35, 0x36, 0x31, 0x32, 0x33, 
0x30, 0x2e, 0xd };

unsigned char shifted[] = {
0x0, 0x1b, 0x21, 0x40, 0x23, 0x24, 0x25, 
0x5e, 0x26, 0x2a, 0x28, 0x29, 0x5f, 0x2b, 
0x8, 0x9, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59,
0x55, 0x49, 0x4f, 0x50, 0x7b, 0x7d, 0xd, 0x0, 
0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4a, 0x4b, 
0x4c, 0x3a, 0x22, 0x7e, 0x0, 0x7c, 0x5a, 0x58, 
0x43, 0x56, 0x42, 0x4e, 0x4d, 0x3c, 0x3e, 0x3f, 
0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x37, 0x38, 0x0, 
0x2d, 0x34, 0x0, 0x36, 0x2b, 0x0, 0x32, 0x0, 0x30, 
0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 0x29, 0x2f, 0x2a, 0x37, 
0x38, 0x39, 0x34, 0x35, 0x36, 0x31, 0x32, 0x33, 0x30, 
0x2e, 0xd };

unsigned char unshifted[] = {
0x0,0x1b, 0x31, 0x32, 0x33, 0x34, 
0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 
0x2d, 0x3d, 0x8, 0x9, 0x71, 0x77, 0x65, 
0x72, 0x74, 0x79, 0x75, 0x69, 0x6f, 0x70, 
0x5b, 0x5d, 0xd, 0x0, 0x61, 0x73, 0x64, 
0x66, 0x67, 0x68, 0x6a, 0x6b, 0x6c, 0x3b, 
0x27, 0x60, 0x0, 0x5c, 0x7a, 0x78, 0x63,
0x76, 0x62, 0x6e, 0x6d, 0x2c, 0x2e, 0x2f, 
0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x0, 0x2b, 0x0, 
0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 
0x29, 0x2f, 0x2a, 0x37, 0x38, 0x39, 0x34, 0x35, 0x36, 
0x31, 0x32, 0x33, 0x30, 0x2e, 0x0d 
};


/*
* PUrpose: INitializes the keyboard isr. Must be called in the begining of the program
*/
void init_keyboard_isr() {
    kbd_buffer.rear = 0;
    kbd_buffer.front = 0;

    enter_super();
    *INTERUPT_ENABLE &= 0xBF; /*masking interupts*/
    exit_super();
    
    orig_kbd_vector = install_vector(KBD_VEC_NUM, kbd_isr);

    enter_super();
    *INTERUPT_ENABLE |= 0x40; /*unmasking interupts*/
    exit_super();
}
/*
* PUrpose: Restores the keyboard isr. Must be called at the end of the program
*/

void restore_keyboard_isr() {
    enter_super();
    *INTERUPT_ENABLE &= 0xBF; /*masking interupts*/
    exit_super();

    install_vector(KBD_VEC_NUM, orig_kbd_vector);

    enter_super();
    *INTERUPT_ENABLE |= 0x40; /*unmasking interupts*/
    exit_super();
}


                                                                                                                                      

/*
 * Purpose: Main keyboard driver. Handles mouse as well as keyboard input
 */
void kbd_driver() {
    unsigned char value = *IKBD_RDR; 

    switch (mouse_state) {
        case NO_MOUSE_STATE:
            if (value >= 0xF8) {
                mouse_state = MOUSE_2nd_PACKET_STATE;
            } else {
                kbd_buffer.buffer[kbd_buffer.rear++] = value;
            }
            break;

        case MOUSE_2nd_PACKET_STATE:
            mouse_state = MOUSE_3rd_PACKET_STATE;
            break;

        case MOUSE_3rd_PACKET_STATE:
            mouse_state = NO_MOUSE_STATE;
            break;
    }

}




/*
 * Purpose: Checks if the keyboard buffer is empty. Returns TRUE if it is, FALSE otherwise
 *
 */
bool is_buffer_empty() {
    return kbd_buffer.front == kbd_buffer.rear ? TRUE: FALSE;
}




/*
 * Purpose:  Gets the next character from the keyboard buffer. Converts the scancode into ascii using KEy tables and also
 *          takes into account shift(left and right) and caps lock key. Non-character and special break codes (excluding shifts)
 *          return a null character */
unsigned char get_value_from_buffer() {
    unsigned char value = NULL_CHAR; 

    while (is_buffer_empty() == FALSE && value == NULL_CHAR) {
        value = kbd_buffer.buffer[kbd_buffer.front++];

        /*skip if it is a non shift break scan code*/
        if((value & BREAK_CODE) == BREAK_CODE && IS_A_SHIFT_BREAK_CODES(value) == FALSE)  {
            value = NULL_CHAR; 
            continue; 
        }

        switch (key_state) {
            case No_Special_Key: 
                handle_no_special_key(&value); 
                break;
            case Caps_Lock_On: 
                handle_caps_lock_on(&value); 
                break;
            default: 
                handle_shift_held(&value); 
                break;
        }

    }

    return value;
}
/*
 * Purpose: Adjusts key_state if special keys (Caps Lock, Shift) were detected or translates scancodes 
 *          to unshifted asci characters. Special keys set the output to NULL_CHAR, indicating non-printable input
 */
void handle_no_special_key(unsigned char* value) {

    switch(*value) {
        case CAPS_ON_MAKE_CODE:     key_state = Caps_Lock_On;      break;
        case LEFT_SHIFT_MAKE_CODE:  key_state = Left_Shift_Held;   break;
        case Right_SHIFT_MAKE_CODE: key_state = Right_Shift_Held;  break;
        default: *value = unshifted[*value];  return; /*Non special key case*/
    }

    *value = NULL_CHAR; /*Special Key was detected*/

}

/*
 * Purpose: Manages caps lock on state,  resets caps lock state if a caps lock make code is detected 
 *          or translates scancodes to uppercase ascii characters if caps lock is active. 
 *          Sets value to NULL_CHAR for Caps Lock make code, else to corresponding caps lock  character in the caps key table
 */
void handle_caps_lock_on(unsigned char* value) {
    if (*value == CAPS_ON_MAKE_CODE) {
        key_state = No_Special_Key;
        *value = NULL_CHAR;
    } else {
        *value = caps_lock[*value];
    }
}

/*
 * Puspose: Manages shift key state, resets shift state or translates scancodes to shfited ascii characters if shift key is active. 
 *           Sets value to NULL_CHAR for shift release, else to corresponding shifted character in the shifted key table
 */
void handle_shift_held(unsigned char* value) {
    if((key_state == Left_Shift_Held && *value == LEFT_SHIFT_BREAK_CODE) ||
       (key_state == Right_Shift_Held && *value == Right_SHIFT_BREAK_CODE)) {
        *value = NULL_CHAR;
        key_state = No_Special_Key;
    }else {
        if(*value == CAPS_ON_MAKE_CODE) {
            *value = NULL_CHAR;
            key_state = Caps_Lock_On;
        } else {
            *value = shifted[*value];
        }

    }

}