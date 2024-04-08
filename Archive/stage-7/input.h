#ifndef INPUT_H
#define INPUT_H



#include <osbind.h>

#include "bool.h"

#define NO_INP_CHAR '\0'
#define ESC_KEY '\033'

/*changes the inp value if a valid key (esc or space) was pressed*/
void user_input(char *inp);

#endif