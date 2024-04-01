#ifndef INPUT_H
#define INPUT_H

#include "macros.h"
#include "kbd.h"

#define MOUSE_LEFT_CLICK_VALUE      0xFA
#define MOUSE_RIGHT_CLICK_VALUE     0xF9
#define ALL_BUTTONS_MAX_Y           380
#define ALL_BUTTONS_MIN_Y           355

#define ONE_PLAYER_BUTTON_MIN_X     115
#define ONE_PLAYER_BUTTON_MAX_X     180

#define PAUL_MODE_BUTTON_MIN_X      340
#define PAUL_MODE_BUTTON_MAX_X      405

#define EXIT_BUTTON_MIN_X           450
#define EXIT_BUTTON_MAX_X           515


typedef enum {
    NO_SELECTION,
    SELECTED_PAUL_MODE,
    SELECTED_1_PLAYER,
    SELECTED_EXIT
}CURSOR_STATUS;

bool user_pressed_space();
CURSOR_STATUS  get_user_mouse_input();



#endif