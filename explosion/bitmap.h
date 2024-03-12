#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"


extern const UINT32 platform_32_32 [];
extern const UINT32 player[];
extern const UINT32 platform_32_16[];
extern const UINT32 brick_32_32[];
extern const UINT32 brick_32_32_2[];

extern const UINT8 explosion_f1 [];
extern const UINT8 explosion_f2 [];
extern const UINT8 explosion_f3 [];
extern const UINT8 explosion_f4 [];
extern const UINT8 explosion_f5 [];
extern const UINT8 explosion_f6 [];
extern const UINT8 explosion_f7 [];
extern const UINT8 explosion_f8 [];
extern const UINT8 *explosion_images [];

typedef enum  {
	EXPLOSION_FRAME_1,
	EXPLOSION_FRAME_2,
	EXPLOSION_FRAME_3,
	EXPLOSION_FRAME_4,
	EXPLOSION_FRAME_5,
	EXPLOSION_FRAME_6,
	EXPLOSION_FRAME_7,
	EXPLOSION_FRAME_8
} Explosion_Animation;

#endif