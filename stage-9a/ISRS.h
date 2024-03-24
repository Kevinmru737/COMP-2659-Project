
#ifndef ISRS_H
#define ISRS_H
#include <osbind.h>
#include "events.h"
#include "level.h"
#include "global.h"

extern short timer;






void vbl_isr();
typedef void (*Vector)();
Vector install_vector(int num, Vector vector);
void process_vbl_isr();





#endif
