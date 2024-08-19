#include <stdio.h>
#include "types.h"

typedef HeapAllocation __ImagePixels;
typedef __ImagePixels Rgb8bitImagePixels;
typedef __ImagePixels Rgb16bitImagePixels;

#define PIXELS_KIND_SIZE sizeof(U8)
#define PIXELS_CHANNEL_COUNT_SIZE sizeof(U8)
#define PIXELS_CHANNEL_BIT_DEPTH_SIZE sizeof(U8)
#define PIXELS_DIMENSION_SIZE sizeof(U16)
#define PIXELS_FIELDS_SIZE (PIXELS_KIND_SIZE + PIXELS_CHANNEL_COUNT_SIZE + PIXELS_CHANNEL_BIT_DEPTH_SIZE + PIXELS_DIMENSION_SIZE + PIXELS_DIMENSION_SIZE)

#define PIXELS_KIND_PTR_OFFSET (PIXELS_KIND_SIZE)
#define PIXELS_CHANNEL_COUNT_PTR_OFFSET (PIXELS_KIND_PTR_OFFSET + PIXELS_CHANNEL_COUNT_SIZE)
#define PIXELS_CHANNEL_BIT_DEPTH_PTR_OFFSET (PIXELS_CHANNEL_COUNT_PTR_OFFSET + PIXELS_CHANNEL_BIT_DEPTH_SIZE)
#define PIXELS_WIDTH_PTR_OFFSET (PIXELS_CHANNEL_BIT_DEPTH_PTR_OFFSET + PIXELS_DIMENSION_SIZE)
#define PIXELS_HEIGHT_PTR_OFFSET (PIXELS_WIDTH_PTR_OFFSET + PIXELS_DIMENSION_SIZE)

#define BITS_PER_BYTE 8

typedef enum {
  __PixelsKind_RGB_8bit = 0,
  __PixelsKind_RGB_16bit = 1
} __PixelsKindOptions;

typedef enum {
  __PixelsChannelCount_RGB = 3,
  // __PixelsChannelCount_RGBA = 4,
} __PixelsChannelCountOptions;

typedef enum {
  __PixelsChannelBitDepth_8 = 8,
  __PixelsChannelBitDepth_16 = 16
} __PixelsChannelBitDepthOptions;

Rgb8bitImagePixels createRgb8bitImagePixels(U16 pixelsWidth, U16 pixelsHeight);
// Rgb16bitImagePixels createRgb16bitImagePixels(U16 pixelsWidth, U16 pixelsHeight);
void freeImagePixels(__ImagePixels imagePixels);

U8 getPixelsKind(__ImagePixels imagePixels);
U8 getPixelsChannelCount(__ImagePixels imagePixels);
U8 getPixelsChannelBitDepth(__ImagePixels imagePixels);
U8 getPixelsChannelByteDepth(__ImagePixels imagePixels);
U8 getPixelsPixelByteCount(__ImagePixels imagePixels);
U16 getPixelsWidth(__ImagePixels imagePixels);
U16 getPixelsHeight(__ImagePixels imagePixels);

void writeRgbImagePixels(__ImagePixels imagePixels, FILE* outputFilePtr);
