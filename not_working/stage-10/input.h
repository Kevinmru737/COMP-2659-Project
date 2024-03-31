#ifndef INPUT_H
#define INPUT_H



#include "macros.h"
#include "kbd.h"

/*changes the inp value if a valid key (esc or space) was pressed*/
bool user_pressed_space();
UINT8 get_mouse_button_status();

#endif