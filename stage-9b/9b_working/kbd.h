#ifndef kbd_h
#define kbd_h
#include "vct_inst.h"
#include <osbind.h>
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0



typedef unsigned char SCANCODE;


#define KBD_STATE_NO_MOUSE 0
#define KBD_STATE_2nd_MOUSE 1
#define KBD_STATE_3rd_MOUSE 2

#define KBD_VEC_NUM 70
#define KBD_BUFFER_SIZE 64
#define BUFFER_EMPTY_VALUE -1




void restore_keyboard_isr();
void init_keyboard_isr();
void kbd_isr();
unsigned char get_value_from_buffer();
bool is_buffer_empty();

void put_value_in_buffer(unsigned char value);
void kbd_driver();


typedef struct {
   unsigned char buffer[KBD_BUFFER_SIZE];
   int front;
   int rear;
}Kbd_Buffer;




#endif