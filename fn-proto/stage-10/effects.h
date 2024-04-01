#ifndef EFFECTS_H
#define EFFECTS_H

#include "rast_asm.h"
/*
* effects.h contains the various sound effects used for the game
*
* Note: Because they both use an envelope that dies off after a short
*       time interval, they can be used without clearing the PSG
*       registers afterwards.
*/
void play_explosion_sound();
void play_select_sound();

#endif