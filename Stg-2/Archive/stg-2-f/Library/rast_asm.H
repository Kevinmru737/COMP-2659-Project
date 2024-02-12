/*
*Purpose: Header file for a clear quick function author by Marc Shroeder. Clears the 38k bytes in memory 
*       starting from base. Before calling, make sure the base points to the starts of the frame buffer
*       or there might be an error related to memory

*/

#ifndef RAST_ASM_H
#define RAST_ASM_H

#include "types.h"

void clear_screen(UINT32* base);

#endif
