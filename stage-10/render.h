#ifndef RENDER_H
#define RENDER_H

#include "Raster.H"
#include "models.h"
#include "bitmaps.h" 
#include "consts.h"
#include "kbd.h"
#include "rast_asm.h"

void render(const Model* model, UINT32* base, short *num_times_ground_drawn);
void render_object(UINT32* base, Game_Object* const game_object);
void render_score(UINT32* base, int game_state);
void render_explosion(const Model* model, UINT32* base, short explosion_counter);

void render_splash_screen(UINT16 *base);

void render_mouse(UINT16 *base);


#endif