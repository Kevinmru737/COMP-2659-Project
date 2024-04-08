
#ifndef vbl_H
#define vbl_H
#include <osbind.h>
#include "events.h"
#include "level.h"
#include "global.h"

#include "macros.h"
#include "music.h"

void vbl_isr();
void process_vbl_isr();


extern UINT32 time_elapsed_melody;
extern UINT32 time_elapsed_base;




#endif
