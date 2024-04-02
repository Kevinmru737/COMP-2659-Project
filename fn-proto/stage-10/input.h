#ifndef INPUT_H
#define INPUT_H

#include "consts.h"
#include "kbd.h"

typedef enum {
    NO_SELECTION,
    SELECTED_PAUL_MODE,
    SELECTED_1_PLAYER,
    SELECTED_EXIT
}CURSOR_STATUS;

bool user_pressed_space();
CURSOR_STATUS  get_user_mouse_input();



#endif