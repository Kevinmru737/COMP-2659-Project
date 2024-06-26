#include "kbd.h"


/*globals*/
Kbd_Buffer kbd_buffer;
Vector orig_kbd_vector;
bool keyboard_enabled;
short mouse_state;
unsigned short mouse_button;
int mouse_curr_x, mouse_curr_y;
bool mouse_enabled;

volatile const UINT8 *const IKBD_RDR  = 0xFFFFFC02;
volatile UINT8 *const INTERRUPT_MASK  = 0xFFFA15;

typedef enum {
    No_Special_Key,
    Caps_Lock_On,
    Left_Shift_Held,
    Right_Shift_Held
} KEY_STATE;


void handle_no_special_key(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state);
void handle_caps_lock_on(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state);
void handle_shift_held(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state);
void put_value_in_buffer(UINT8 value);
void mask_kbd_interrupts();
void unmask_kbd_interrupts();


/*KEY tables, scancodes are used as indices. Each element is an ascii value*/
UINT8 caps_lock[] = {
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
0x30, 0x2e, 0xd
};

UINT8 shifted[] = {
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
0x2e, 0xd
};

UINT8 unshifted[] = {
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

/*****************************************************************************
* Purpose: Initializes the keyboard isr. Must be called in the beginning of
*          the program. Uses a global to stor the original kbd vector
*****************************************************************************/
void init_keyboard_isr() {
    kbd_buffer.rear = 0;
    kbd_buffer.front = 0;

    mouse_state = NO_MOUSE_STATE;
    keyboard_enabled = mouse_enabled = FALSE;
    mouse_button = 0;
    mouse_curr_x = DEFAULT_MOUSE_X;
    mouse_curr_y = DEFAULT_MOUSE_Y;
    
    mask_kbd_interrupts();
    orig_kbd_vector = install_vector(KBD_VEC_NUM, kbd_isr);
    unmask_kbd_interrupts();
}




/*****************************************************************************
* Purpose: Restores the keyboard isr. Must be called at the end of the
*          program. Uses a global to restore the original kbd vector
*****************************************************************************/
void restore_keyboard_isr() {
    mask_kbd_interrupts();
    install_vector(KBD_VEC_NUM, orig_kbd_vector);
    unmask_kbd_interrupts();
}



/*****************************************************************************
 * Purpose: Main keyboard and mouse input driver. This function handles input
*           from both the keyboard and the mouse. Only updates mouse or 
*           keyboard(global properties) if they are enabled.
*****************************************************************************/
void kbd_driver() {
    UINT8 value = *IKBD_RDR;
    
    switch (mouse_state) {
    
        case NO_MOUSE_STATE:
            if (value >= 0xF8) {
               if(mouse_enabled == TRUE) {
                    mouse_button = value; 
                }
                mouse_state = MOUSE_2nd_PACKET_STATE;
            } else if(keyboard_enabled == TRUE) {
                kbd_buffer.buffer[kbd_buffer.rear++] = value;
            }
            break;

        case MOUSE_2nd_PACKET_STATE:
            if(mouse_enabled == TRUE) {
                mouse_curr_x += (int)(char) value; 
                if(mouse_curr_x > MOUSE_MAX_X) mouse_curr_x = MOUSE_MAX_X;
                if(mouse_curr_x < 0) mouse_curr_x = 0;
            }
            mouse_state = MOUSE_3rd_PACKET_STATE;
            break;

        case MOUSE_3rd_PACKET_STATE:
            if(mouse_enabled == TRUE) {
                mouse_curr_y += (int)(char) value; 
                if(mouse_curr_y > MOUSE_MAX_Y) mouse_curr_y = MOUSE_MAX_Y;
                if(mouse_curr_y < 0) mouse_curr_y = 0;           
            }
            mouse_state = NO_MOUSE_STATE;
            break;
    }
}



/*****************************************************************************
* Purpose: Checks if the keyboard buffer is empty. Returns TRUE if it is,
*          FALSE otherwise
*****************************************************************************/
bool is_buffer_empty() {
    return kbd_buffer.front == kbd_buffer.rear ? TRUE: FALSE;
}



/*****************************************************************************
* Purpose: Enables mouse input processing.
*****************************************************************************/
void enable_mouse() {
    mouse_enabled = TRUE;
    mouse_button = 0;
}


/*****************************************************************************
* Purpose: Enables keyboard input processing.
*****************************************************************************/
void enable_keyboard() {
    keyboard_enabled = TRUE;
}


/*****************************************************************************
* Purpose: Disables mouse input processing.
*****************************************************************************/
void disable_mouse() {
    mouse_enabled = FALSE;
}


/*****************************************************************************
* Purpose: Disables keyboard input processing and resets the keyboard buffer.
*****************************************************************************/
void disable_keyboard() {
    keyboard_enabled = FALSE;
    kbd_buffer.rear = kbd_buffer.front = 0;
}


/*****************************************************************************
* Purpose: Masks keyboard interrupts by clearing the 6th bit in the
*          interrupt mask b register of the mfp
*****************************************************************************/
void mask_kbd_interrupts() {
    enter_super();
    *INTERRUPT_MASK &= 0xBF;
    exit_super();

}


/*****************************************************************************
* Purpose: Unmasks keyboard interrupts by setting the 6th bit in the interrupt
*          mask b register of the mfp
*****************************************************************************/
void unmask_kbd_interrupts(){
    enter_super();
    *INTERRUPT_MASK |= 0x40;
    exit_super();

}

/*
 * Purpose: Retrieves the current X coordinate of the mouse cursor.
 */
int get_mouse_curr_x(){
    return mouse_curr_x;

}
/*
 * Purpose: Retrieves the current y coordinate of the mouse cursor.
 */
int get_mouse_curr_y(){
    return mouse_curr_y;
}

/*
* Purpose: Retrieves the current value of the mouse button.
 */
UINT8 get_mouse_button_value(){
    UINT8 value = mouse_button;
    mouse_button = 0;
    return value;
}

/*
* Purpose: Returns true if the mouse is currently enabled, False otherwise
*/
bool is_mouse_enabled() {
    return mouse_enabled;
}







/*****************************************************************************
* Purpose: Returns the next character from the keyboard buffer if it
*          corresponds to a non-special key make code.
*          Converts the scancode into an ASCII character, considering the
*          current state of shift keys (left and right) and caps lock.
*          Returns a null character if non special make codes are not
*          present in the buffer
*****************************************************************************/
UINT8 get_value_from_buffer() {
    static KEY_STATE key_state = No_Special_Key;
    UINT8 scan_code;
    UINT8 value = NULL_CHAR;
    
    while (is_buffer_empty() == FALSE && value == NULL_CHAR) {
        scan_code = kbd_buffer.buffer[kbd_buffer.front++];

        /*Skip all break scan codes except the shift ones*/
        if((scan_code & BREAK_CODE) == BREAK_CODE &&
         IS_A_SHIFT_BREAK_CODES(scan_code) == FALSE) {
            continue; 
         }

        switch (key_state) {
         
            case No_Special_Key:   
                handle_no_special_key(&scan_code, &value, &key_state); 
                break;

            case Caps_Lock_On: 
                handle_caps_lock_on(&scan_code, &value, &key_state); 
                break;

            default: 
                handle_shift_held(&scan_code, &value, &key_state); 
                break;
        
        }
    }

    return value;
}


/*****************************************************************************
* Purpose: Adjusts key_state if a special keys (Caps Lock, Shift) were 
*          detected translates scancodes
*****************************************************************************/
void handle_no_special_key(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state) {
    switch(*scan_code) {

        case CAPS_ON_MAKE_CODE:
            *key_state = Caps_Lock_On;
            break;
    
        case LEFT_SHIFT_MAKE_CODE:
            *key_state = Left_Shift_Held;
            break;
    
        case Right_SHIFT_MAKE_CODE:
            *key_state = Right_Shift_Held;
            break;
    
        default:
            *value = unshifted[*scan_code];
                  
    }
}


/*****************************************************************************
* Purpose: Manages caps lock on state, resets key state if a caps lock make
*          code is detected or translates scancodes to uppercase ascii
*           characters if caps lock is active. Sets value to corresponding caps
*           lock character in the caps key table if caps lock lock make is 
*           not detected
*****************************************************************************/
void handle_caps_lock_on(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state) {
    
    if (*scan_code == CAPS_ON_MAKE_CODE) {
        *key_state = No_Special_Key;
    } else {
        *value = caps_lock[*scan_code];
    }

}



/*****************************************************************************
 * Purpose: Manages shift key state, resets shift state or translates
 *          scancodes to the shifted ascii characters if the shift key is
 *          active. Sets value to corresponding shifted character in the
 *          shifted key table
*****************************************************************************/
void handle_shift_held(UINT8 *scan_code, UINT8 *value,  KEY_STATE *key_state) {

    if ((*key_state == Left_Shift_Held && *scan_code == LEFT_SHIFT_BREAK_CODE) ||
       (*key_state == Right_Shift_Held && *scan_code == Right_SHIFT_BREAK_CODE)) {   
        *value = NULL_CHAR;
        *key_state = No_Special_Key;

    } else if (*scan_code == CAPS_ON_MAKE_CODE) {
        *key_state = Caps_Lock_On;
    } else {
        *value = shifted[*scan_code];
    }

}

