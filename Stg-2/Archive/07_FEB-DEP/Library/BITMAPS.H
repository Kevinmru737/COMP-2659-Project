#ifndef TEST_DATA
#define TEST_DATA

#include "types.h"

extern char TEST_CASES_FOR_32_BIT_DRAWER[][];
extern char TEST_CASES_FOR_16_BIT_DRAWER[][];
extern char TEST_CASES_FOR_8_BIT_DRAWER[][];

extern  UINT32 cube_32_x_32[];
extern UINT32 ground_640_x_128[];
extern UINT32 unaligned_cube_32_x_7[];
extern UINT32 unaligned_expected_cube[];

extern UINT16 invader_16_x_16[];
extern UINT16 ground_16_bit_640_x_2[];
extern UINT16 unaligned_input_16_x_5[];
extern UINT16 unaligned_expected_16_x_5[];

extern UINT8 char_8_x_8[];
extern UINT8 ground_640_x_2_8_bit_test[];
extern UINT8 unaligned_expected_char[];
extern UINT8 unaligned_input_char[];


extern UINT32* test_32_bit_drawer_expected_buffers[];
extern UINT32 *test_32_bit_drawer_input_buffers[];

extern UINT16 *test_16_bit_drawer_input_buffers[];
extern UINT16 *test_16_bit_drawer_expected_buffers[];

extern UINT8 *test_8_bit_drawer_input_buffers[];
extern UINT8 *test_8_bit_drawer_expected_buffers[];

extern char TEST_CASES_FOR_32_BIT_DRAWER[][];
extern char TEST_CASES_FOR_16_BIT_DRAWER[][];
extern char TEST_CASES_FOR_8_BIT_DRAWER[][];



#endif
