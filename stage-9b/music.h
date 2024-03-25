#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#include "macros.h"

/*
* music.h contains 2 functions, start_music and update_music
*
* The functions are hard-coded to play a specific song whose notes
* can be found in PSG.c and are defined in PSG.h (Back on Track)
*
* TO USE: start_music should be called only once, and update music
*         should be called based on a 1/70 Hz time increment.
*/
void start_music();
void update_music(UINT32 *time_elapsed_melody, UINT32 *time_elapsed_bass);

#endif