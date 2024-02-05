#ifndef TYPES_H
#define TYPES_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

#define UINT32_SIZE_BITS 32
#define UINT16_SIZE_BITS 16
#define UINT8_SIZE_BITS 8


#define UINT32_PER_SCANLINE 20
#define UINT16_PER_SCANLINE 40
#define UINT8_PER_SCANLINE 80

#define OFFSET_TO_UINT32(X,Y) (X >> 5) + (Y << 4) + (Y << 2)
#define OFFSET_TO_UINT16(X,Y) (X >> 4) + (Y << 5) + (Y << 3)

#endif
