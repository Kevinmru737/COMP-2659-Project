

#ifndef LEVEL_H
#define LEVEL_H
#include "models.h"
#include "bool.h"
#include "types.h"
typedef void (*LEVEL_UPDATE_FUNCTIONS)(Model*, UINT8*);

void update_level(Model *model, UINT8 *game_state);
void lvl_1(Model *model, UINT8* game_state);
void lvl_2(Model*model, UINT8* game_state);
void lvl_3(Model *model, UINT8 *game_state);
void lvl_4(Model*model, UINT8* game_state);
void lvl_5(Model *model, UINT8 *game_state);
void lvl_6(Model*model, UINT8 *game_state);
void lvl_7(Model *model, UINT8 *game_state);
void lvl_8(Model*model, UINT8 *game_state);
void lvl_9(Model*model, UINT8 *game_state);
void lvl_10(Model*model, UINT8 *game_state);


extern LEVEL_UPDATE_FUNCTIONS lvl_update_functions[];
#endif
