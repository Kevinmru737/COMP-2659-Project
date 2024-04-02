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

/****************************************************************************************
 * Purpose: Checks if the user left clicked on a button.
 *
 * Details:
 *   This function checks if the user's mouse click falls within the boundaries of any
 *   buttons. It returns the status of the selection, such as selecting a game mode or 
 *   exiting the game, based on the mouse's current X and Y coordinates.
 ****************************************************************************************/
CURSOR_STATUS  get_user_mouse_input() {
    UINT8 value = get_mouse_button_value();
    int current_mouse_x_pos = get_mouse_curr_x();
    int current_mouse_y_pos = get_mouse_curr_y();
    CURSOR_STATUS  status = NO_SELECTION;

    /*Check if the user left-clicked and is within the y bounds of all buttons*/
    if(value == MOUSE_LEFT_CLICK_VALUE && current_mouse_y_pos >= ALL_BUTTONS_MIN_Y &&
        current_mouse_y_pos <= ALL_BUTTONS_MAX_Y)
    {
        /*Checking if the click was on the x bounds of 1 player button*/
        if (current_mouse_x_pos >= ONE_PLAYER_BUTTON_MIN_X && current_mouse_x_pos <= ONE_PLAYER_BUTTON_MAX_X) {
            status =  SELECTED_1_PLAYER;
        }

        /*Checking if the click was on the x bounds of Paul Mode button*/
        if (current_mouse_x_pos >= PAUL_MODE_BUTTON_MIN_X && current_mouse_x_pos <= PAUL_MODE_BUTTON_MAX_X) {
            status = SELECTED_PAUL_MODE;
        }

        /*Checking if the click was on the x bounds of EXIT button*/
        if (current_mouse_x_pos >= EXIT_BUTTON_MIN_X && current_mouse_x_pos <= EXIT_BUTTON_MAX_X) {
            status = SELECTED_EXIT;
        }

    }

    return status;
}
