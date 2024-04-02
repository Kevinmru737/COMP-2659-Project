

#ifndef CONSTS_H
#define CONSTS_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

#define PLAYER_INDEX 0              /*RENDER, EVENTS AND MODELS*/
#define GROUND_POS 271              /*EVENTS AND MODELS*/
#define DEFAULT_OBJECT_VELOCITY 4   /*EVENTS AND MODELS*/
#define DEFAULT_OBJECT_HEIGHT 31    /*RASTER, EVENTS AND MODELS*/

/****************Exclusively for MODELS module**************************/
#define TRIANGLE_BASE_WIDTH 15
#define DEFAULT_OBJECT_WIDTH 31
#define SHORT_OBJECT_HEIGHT 15

/****************Exclusively for events module**************************/
#define PLAYER_INITIAL_JUMP_VELOCITY 25
#define PLAYER_LEFT_EDGE_X_POS 160
#define PLAYER_RIGHT_EDGE_X_POS 191
#define PLAYER_TERMINAL_VELOCITY -24

/****************Exclusively for raster module **************************/
                                /* (x % 32) + (y *20) */
#define OFFSET_TO_UINT32(X,Y) (X >> 5) + (Y << 4) + (Y << 2)
#define OFFSET_TO_UINT16(X,Y) (X >> 4) + (Y << 5) + (Y << 3)
#define OFFSET_TO_UINT8(X,Y)  (X >> 3) + (Y << 6) + (Y << 4)
#define UINT32_SIZE_BITS 32
#define UINT16_SIZE_BITS 16
#define UINT8_SIZE_BITS 8
#define UINT32_PER_SCANLINE 20
#define UINT16_PER_SCANLINE 40
#define UINT8_PER_SCANLINE 80
#define PLATFORM_HEIGHT_SHORT 16
/*******************Exclusively for geo dash module ****************************/
#define MAX_GAME_STATE 11
#define EXPLOSION_ANIMATION_TOTAL_FRAMES 8
#define FINAL_VICTORY_FRAME_COUNT   10
#define MAX_VICTORY_ANIMATION_LOOP_COUNT 10

/*******************Exclusively for levels module ******************************/
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

/*******************Exclusively for renderer module ****************************/
#define SCORE_BAR_WIDTH 160
#define SCORE_BAR_HEIGHT 32
#define SCORE_BAR_X_POS 240
#define SCORE_BAR_Y_POS 50
#define EXPLOSION_HEIGHT 32
#define EXPLOSION_WIDTH 32
#define MAX_TIMES_TO_DRAW_GROUND 2
#define RIGHT_EDGE_DRAW 608

/*******************Exclusively for KBD module ****************************/
#define KBD_BUFFER_SIZE             256
#define NULL_CHAR                   '\0'
#define NO_MOUSE_STATE               0
#define MOUSE_2nd_PACKET_STATE       1
#define MOUSE_3rd_PACKET_STATE       2
#define DEFAULT_MOUSE_X             320
#define DEFAULT_MOUSE_Y             200
#define KBD_VEC_NUM                  70
#define BUFFER_EMPTY_VALUE           -1
#define BREAK_CODE                   0x80
#define CAPS_ON_MAKE_CODE            0x3A
#define LEFT_SHIFT_MAKE_CODE         0x2A
#define Right_SHIFT_MAKE_CODE        0x36
#define LEFT_SHIFT_BREAK_CODE        0xAA
#define Right_SHIFT_BREAK_CODE       0xB6
#define IS_A_SHIFT_BREAK_CODES(X) ((X == Right_SHIFT_BREAK_CODE) || (X == LEFT_SHIFT_BREAK_CODE))
#define MOUSE_MAX_X                 624
#define MOUSE_MAX_Y                 384
/*******************Exclusively for input module ****************************/
#define MOUSE_LEFT_CLICK_VALUE      0xFA
#define MOUSE_RIGHT_CLICK_VALUE     0xF9
#define ALL_BUTTONS_MAX_Y           380
#define ALL_BUTTONS_MIN_Y           355
#define ONE_PLAYER_BUTTON_MIN_X     115
#define ONE_PLAYER_BUTTON_MAX_X     180
#define PAUL_MODE_BUTTON_MIN_X      340
#define PAUL_MODE_BUTTON_MAX_X      405
#define EXIT_BUTTON_MIN_X           450
#define EXIT_BUTTON_MAX_X           515




#endif
