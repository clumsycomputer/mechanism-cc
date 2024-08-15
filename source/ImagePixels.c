#include "types.h"

typedef enum {
  PixelsChannelCount_RGB = 3,
  PixelsChannelCount_RGBA = 4,
} PixelsChannelCount;

typedef enum {
  PixelsBitDepth_8 = 8,
  PixelsBitDepth_16 = 16
} PixelsBitDepth;

HeapAllocation __createImagePixels(
    U8 pixelsChannelCount,
    U8 pixelsBitDepth,
    U16 pixelsWidth,
    U16 pixelsHeight) {
  int foo = 2 * 3;
}

void foo() {
  __createImagePixels(
      -1,
      -1,
      18,
      18);
}