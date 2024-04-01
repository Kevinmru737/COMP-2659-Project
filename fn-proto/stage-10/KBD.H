#ifndef kbd_h
#define kbd_h


#include "vct_inst.h"
#include "macros.h"
#include "rast_asm.h"


#define KBD_BUFFER_SIZE 256
#define NULL_CHAR '\0'

#define NO_MOUSE_STATE 0
#define MOUSE_2nd_PACKET_STATE 1
#define MOUSE_3rd_PACKET_STATE 2
#define DEFAULT_MOUSE_X 320
#define DEFAULT_MOUSE_Y 200


#define KBD_VEC_NUM 70
#define BUFFER_EMPTY_VALUE -1

#define BREAK_CODE 0x80
#define CAPS_ON_MAKE_CODE 0x3A

#define LEFT_SHIFT_MAKE_CODE 0x2A
#define Right_SHIFT_MAKE_CODE 0x36

#define LEFT_SHIFT_BREAK_CODE 0xAA
#define Right_SHIFT_BREAK_CODE 0xB6

#define IS_A_SHIFT_BREAK_CODES(X) ((X == Right_SHIFT_BREAK_CODE) || (X == LEFT_SHIFT_BREAK_CODE))


void restore_keyboard_isr();
void init_keyboard_isr();
void kbd_driver();
void kbd_isr();

void enable_mouse();
void enable_keyboard();
void disable_mouse();
void disable_keyboard();
int set_ipl(int mask);


unsigned char get_value_from_buffer();
bool is_buffer_empty();
int get_mouse_curr_x();
int get_mouse_curr_y();
unsigned char get_mouse_button_value();


typedef struct {
   unsigned char front;
   unsigned char rear;
   unsigned char buffer[KBD_BUFFER_SIZE];
}Kbd_Buffer;



extern bool mouse_enabled;


#endif
