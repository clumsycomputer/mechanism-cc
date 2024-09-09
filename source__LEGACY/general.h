#include <stdint.h>

#ifndef MECHANISM_CC_GENERAL_H
#define MECHANISM_CC_GENERAL_H

typedef uint8_t U8;
typedef int8_t S8;
typedef uint16_t U16;
typedef int16_t S16;
typedef uint32_t U32;
typedef int32_t S32;
typedef uint64_t U64;
typedef int64_t S64;
typedef float IEEE32;
typedef double IEEE64;

typedef char* String;
typedef U8 Byte;
typedef Byte* HeapAllocation;

#define BITS_PER_BYTE 8
#define ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE 8

void printBytes(U8* startAddress, U64 byteCount);
U32 swapEndianU32(U32 value);

#endif
