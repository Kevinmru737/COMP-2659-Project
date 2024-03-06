#ifndef RENDER_H
#define RENDER_H

#include "Raster.H"
#include "models.h"
#include "types.h"
#include "bitmaps.h" 
#include "bool.h"
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define RIGHT_EDGE_DRAW 608
void render(const Model* model, UINT32* base);


void render_object(UINT32* base, Game_Object* game_object);







#endif