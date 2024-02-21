#ifndef RENDER_H
#define RENDER_H

#include "Raster.H"
#include "models.h"
#include "types.h"
#include "bitmaps.h" 

void render(const Model* model, UINT32* base);
void render_all_active_platforms (Model * model, UINT32 *base);
void render_all_active_triangles (Model * model, UINT32 *base);
void render_all_active_players(Model * model,  UINT32 *base);













#endif