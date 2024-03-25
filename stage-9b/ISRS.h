
#ifndef ISRS_H
#define ISRS_H
#include <osbind.h>
#include "events.h"
#include "level.h"
#include "global.h"
#define KBD_BUFFER_SIZE 64
#define BUFFER_EMPTY_VALUE -1
extern short timer;


typedef unsigned char bool;
#define TRUE 1
#define FALSE 0



void vbl_isr();
typedef void (*Vector)();
Vector install_vector(int num, Vector vector);
void process_vbl_isr();
void _keyboard_driver_isr();
void _process_keyboard_driver_isr();
void restore_keyboard_isr();
void init_keyboard_isr();



typedef struct {
   unsigned char buffer[KBD_BUFFER_SIZE];
   short front;
   short rear;
}Input_Buffer;

extern Input_Buffer input_buffer;


#endif
