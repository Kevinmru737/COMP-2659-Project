#include "vct_inst.h"
#include "kbd.h"
#include "consts.h"
#include "stdio.h"
#include <osbind.h>
int main()
{

    unsigned char input = ']';
    init_keyboard_isr();
    enable_keyboard();
    while (input != '\33') {
        if(is_buffer_empty() == FALSE) {
            input = get_value_from_buffer();
            Cconout(input);
        }

    }

    restore_keyboard_isr();

    return 0;
}
