#include "input.h"

/*
 * Purpose: Checks if the user has pressed the space bar. It reads the next character from the input buffer
 * and returns TRUE if the character is a space, otherwise FALSE.
 */


bool user_pressed_space() {
    unsigned char ch;
    if (is_buffer_empty() == FALSE) {
        ch =  get_value_from_buffer();

        if (ch == ' ')
            return TRUE;
	}

    return FALSE;



}


/*
 * Purpose: Retrieves the current status of mouse buttons and resets the mouse button to 0.
 * Returns the mouse button status captured since the last call to this function.
 */
UINT8 get_mouse_button_status() {
    UINT8 value = mouse_button;
    mouse_button =0;
    return value;
}
