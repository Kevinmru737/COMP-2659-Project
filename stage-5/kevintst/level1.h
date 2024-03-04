#ifndef LEVEL1_H
#define LEVEL1_H

#include "types.h"
#include "MODELS.H"
#include "bool.h"



typedef struct
{
    UINT32 time;
    Triangle triangle;
    Platform platform;
    bool draw_triangle;
    bool draw_platform;

} Level;


void load_level1 (Level level []);




#endif