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


CURSOR_STATUS  user_mouse_input() {
    CURSOR_STATUS status = NO_SELECTION;
    UINT8 value = mouse_button;
    if(value ==MOUSE_LEFT_CLICK_VALUE) {
        if(mouse_curr_y >= ALL_BUTTONS_MIN_Y && mouse_curr_y <= ALL_BUTTONS_MAX_Y) {
            if(mouse_curr_x >=ONE_PLAYER_BUTTON_MIN_X && mouse_curr_x <= ONE_PLAYER_BUTTON_MAX_X){
                status = SELECTED_1_PLAYER;
            } else if(mouse_curr_x >=PAUL_MODE_BUTTON_MIN_X && mouse_curr_x <= PAUL_MODE_BUTTON_MAX_X) {
                status = SELECTED_PAUL_MODE;
            } else if(mouse_curr_x >=EXIT_BUTTON_MIN_X && mouse_curr_x <= EXIT_BUTTON_MAX_X) {
                status = SELECTED_EXIT;
            }

        }

    }
    mouse_button = 0;

    return status;

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
