#include "general.h"
#include <stdio.h>

void printBytes(U8* startAddress, U64 byteCount) 
{
  U8* currentAddress;
  for (U64 byteIndex = 0; byteIndex < byteCount; byteIndex++) {
    currentAddress = startAddress + byteIndex;
    printf("%02x ", *currentAddress);
  }
  printf("\n");
}

U32 swapEndianU32(U32 value)
{
  return ((value >> 24) & 0x000000FF) |
         ((value >> 8) & 0x0000FF00) |
         ((value << 8) & 0x00FF0000) |
         ((value << 24) & 0xFF000000);
}
