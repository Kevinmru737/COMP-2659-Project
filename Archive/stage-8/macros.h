

#ifndef MACROS_H
#define MACROS_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

#define UINT32_SIZE_BITS 32
#define UINT16_SIZE_BITS 16
#define UINT8_SIZE_BITS 8

#define UINT32_PER_SCANLINE 20
#define UINT16_PER_SCANLINE 40
#define UINT8_PER_SCANLINE 80
                                /* (x % 32) + (y *20) */
#define OFFSET_TO_UINT32(X,Y) (X >> 5) + (Y << 4) + (Y << 2) 
#define OFFSET_TO_UINT16(X,Y) (X >> 4) + (Y << 5) + (Y << 3)
#define OFFSET_TO_UINT8(X,Y)  (X >> 3) + (Y << 6) + (Y << 4)

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0


#define EXPLOSION_ANIMATION_TOTAL_FRAMES 8
#define EXPLOSION_FRAME_DELAY 7


#define TRIANGLE_BASE_WIDTH 15
#define DEFAULT_OBJECT_WIDTH 31
#define DEFAULT_OBJECT_HEIGHT 31
#define SHORT_OBJECT_HEIGHT 15
#define DEFAULT_OBJECT_VELOCITY 4
#define GROUND_POS 271

#define PLAYER_INITIAL_JUMP_VELOCITY 25
#define PLAYER_LEFT_EDGE_X_POS 160
#define PLAYER_WIDTH 31
#define PLAYER_RIGHT_EDGE_X_POS 191





#define PLAYER_X_POS 5

#define PLATFORM_HEIGHT_SHORT 16
#define PLAYER_INDEX 0

#define MAX_GAME_STATE 10

/*Exclusively for levels.h*/
#define PLAYER_START_X 160
#define PLAYER_START_Y 240
#define GROUND_Y 271
#define SCREEN_RIGHT_EDGE_FOR_32_X_32 608
#define OFFSET_32_UP_FROM_GROUND 240
#define OFFSET_38_UP_FROM_GROUND 233
#define OFFSET_48_UP_FROM_GROUND 223
#define OFFSET_64_UP_FROM_GROUND 208
#define OFFSET_71_UP_FROM_GROUND 200
#define OFFSET_80_UP_FROM_GROUND 189
#define OFFSET_90_UP_FROM_GROUND 179
#define OFFSET_96_UP_FROM_GROUND 176
#define OFFSET_112_UP_FROM_GROUND 160
#define OFFSET_144_UP_FROM_GROUND 128
/*Exclusively for geodash.c*/
#define NO_INP_CHAR '\0'



#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define RIGHT_EDGE_DRAW 608


/*Exclusively for renderer.c*/
#define SCORE_BAR_WIDTH 160
#define SCORE_BAR_HEIGHT 32
#define SCORE_BAR_X_POS 240
#define SCORE_BAR_Y_POS 50
#define EXPLOSION_HEIGHT 32
#define EXPLOSION_WIDTH 32
#define MAX_TIMES_TO_DRAW_GROUND 2



#endif
