#include "general.h"

#ifndef IMAGE_PIXELS_H
#define IMAGE_PIXELS_H

typedef HeapAllocation __ImagePixels;
typedef __ImagePixels Rgb8bitImagePixels;
// typedef __ImagePixels Rgb16bitImagePixels;

#define pixelsHeight__CONSTANT_FIELD_SIZE sizeof(U32)
#define pixelsWidth__CONSTANT_FIELD_SIZE sizeof(U32)
#define pixelsChannelBitDepth__CONFIG_FIELD_SIZE sizeof(U8)
#define pixelsChannelCount__CONFIG_FIELD_SIZE sizeof(U8)
#define pixelsKind__CONFIG_FIELD_SIZE sizeof(U8)

#define PIXELS_HEADER_SIZE (pixelsHeight__CONSTANT_FIELD_SIZE + pixelsWidth__CONSTANT_FIELD_SIZE + pixelsChannelBitDepth__CONFIG_FIELD_SIZE + pixelsChannelCount__CONFIG_FIELD_SIZE + pixelsKind__CONFIG_FIELD_SIZE)
#define PIXELS_DATA_PADDING_SIZE (ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE - (PIXELS_HEADER_SIZE % ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE))
#define PIXELS_HEADER_SIZE_PLUS_PIXELS_DATA_PADDING_SIZE (PIXELS_HEADER_SIZE + PIXELS_DATA_PADDING_SIZE)

#define pixelsKind__PTR_OFFSET (PIXELS_DATA_PADDING_SIZE + pixelsKind__CONFIG_FIELD_SIZE)
#define pixelsChannelCount__PTR_OFFSET (pixelsKind__PTR_OFFSET + pixelsChannelCount__CONFIG_FIELD_SIZE)
#define pixelsChannelBitDepth__PTR_OFFSET (pixelsChannelCount__PTR_OFFSET + pixelsChannelBitDepth__CONFIG_FIELD_SIZE)
#define pixelsWidth__PTR_OFFSET (pixelsChannelBitDepth__PTR_OFFSET + pixelsWidth__CONSTANT_FIELD_SIZE)
#define pixelsHeight__PTR_OFFSET (pixelsWidth__PTR_OFFSET + pixelsHeight__CONSTANT_FIELD_SIZE)

typedef enum
{
  __PixelsKind_Rgb8bit = 0,
  // __PixelsKind_Rgb16bit = 1
} __PixelsKindOptions;

typedef enum
{
  __PixelsChannelCount_Rgb = 3,
  // __PixelsChannelCount_RGBA = 4,
} __PixelsChannelCountOptions;

typedef enum
{
  __PixelsChannelBitDepth_8 = 8,
  // __PixelsChannelBitDepth_16 = 16
} __PixelsChannelBitDepthOptions;

U64 calcPixelsDataByteCount(U8 pixelsChannelCount__, U8 pixelsChannelBitDepth__, U16 pixelsWidth, U16 pixelsHeight);
U64 calcPixelsByteCount(U8 pixelsChannelCount__, U8 pixelsChannelBitDepth__, U16 pixelsWidth, U16 pixelsHeight);

void __initPixelsConfig(U8 pixelsKind__, U8 pixelsChannelCount__, U8 pixelsChannelBitDepth__, __ImagePixels unintializedPixels);
void __initPixelsConstants(U16 pixelsWidth, U16 pixelsHeight, __ImagePixels unintializedPixels);

U8 getPixelsKind(__ImagePixels imagePixels);
U8 getPixelsChannelCount(__ImagePixels imagePixels);
U8 getPixelsChannelBitDepth(__ImagePixels imagePixels);
U8 getPixelsChannelByteDepth(__ImagePixels imagePixels);
U8 getPixelsPixelByteCount(__ImagePixels imagePixels);
U16 getPixelsWidth(__ImagePixels imagePixels);
U16 getPixelsHeight(__ImagePixels imagePixels);
U64 getPixelsDataByteCount(__ImagePixels imagePixels);
U64 getPixelsByteCount(__ImagePixels imagePixels);

#endif
