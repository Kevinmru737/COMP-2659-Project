#ifndef kbd_h
#define kbd_h


#include "vct_inst.h"
#include "consts.h"
#include "rast_asm.h"


void restore_keyboard_isr();
void init_keyboard_isr();
void kbd_driver();
void kbd_isr();

void enable_mouse();
void enable_keyboard();
void disable_mouse();
void disable_keyboard();
int set_ipl(int mask);


UINT8 get_value_from_buffer();
bool is_buffer_empty();
int get_mouse_curr_x();
int get_mouse_curr_y();
UINT8 get_mouse_button_value();


typedef struct {
    UINT8 front;
    UINT8 rear;
    UINT8 buffer[KBD_BUFFER_SIZE];
}Kbd_Buffer;



bool is_mouse_enabled();


#endif
