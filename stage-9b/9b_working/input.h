#ifndef INPUT_H
#define INPUT_H



#include <osbind.h>

#include "macros.h"
#include "kbd.h"

/*changes the inp value if a valid key (esc or space) was pressed*/
void user_input(char *inp);

#endif