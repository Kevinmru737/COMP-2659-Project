#ifndef kbd_h
#define kbd_h
#include "vct_inst.h"
#include <osbind.h>
#include "macros.h"

#define KBD_BUFFER_SIZE 256

#define NO_MOUSE_STATE 0
#define MOUSE_2nd_PACKET_STATE 1
#define MOUSE_3rd_PACKET_STATE 2

#define KBD_VEC_NUM 70
#define BUFFER_EMPTY_VALUE -1


#define BREAK_CODE 0x80
#define CAPS_ON_MAKE_CODE 0x3A

#define LEFT_SHIFT_MAKE_CODE 0x2A
#define Right_SHIFT_MAKE_CODE 0x36

#define LEFT_SHIFT_BREAK_CODE 0xAA
#define Right_SHIFT_BREAK_CODE 0xB6

#define SHIFT_BREAK_CODES(X) ((X == Right_SHIFT_BREAK_CODE) || (X == LEFT_SHIFT_BREAK_CODE))




void restore_keyboard_isr();
void init_keyboard_isr();
void handle_no_special_key(unsigned char* value);
void handle_caps_lock_on(unsigned char* value);
void handle_shift_held(unsigned char* value);
void kbd_driver();
void kbd_isr();
void put_value_in_buffer(unsigned char value);

/* SIMILAR TO CCONIS AND CNECIN */

unsigned char get_value_from_buffer();
bool is_buffer_empty();

typedef struct {
   unsigned front;
   unsigned rear;
   unsigned char buffer[KBD_BUFFER_SIZE];
 
}Kbd_Buffer;




#endif