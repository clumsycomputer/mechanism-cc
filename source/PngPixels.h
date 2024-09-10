#include "general.h"

#ifndef PNG_PIXELS_H
#define PNG_PIXELS_H

typedef enum
{
  __PixelsChannelCountOption_Rgb = (U8)3
} PixelsChannelCountOption;

typedef enum
{
  __PixelsChannelBitDepthOption_8bit = (U8)8
} PixelsChannelBitDepthOption;

typedef struct {
  U64 dataRowSize;
} Rgb8bitPngPixelsCache;

typedef struct {
  Rgb8bitPngPixelsCache __cache;
  U8* data_ptr;
  U8 channelCount;
  U8 channelBitDepth;
  U32 width;
  U32 height;  
} Rgb8bitPngPixels;

typedef struct {
  U8 red;
  U8 green;
  U8 blue;
} Rgb8bitPixelChannels;

U64 calcPixelsDataSize(U32 pixelsWidth, U32 pixelsHeight);
U64 sizeofRgb8bitPngPixels(U32 pixelsWidth, U32 pixelsHeight);
void initRgb8bitPngPixels(Rgb8bitPngPixels* pngPixels, U32 pixelsWidth, U32 pixelsHeight);
Rgb8bitPixelChannels* atPixelsDataPixelChannels(Rgb8bitPngPixels* pngPixels, U32 pixelRowIndex, U32 pixelColumnIndex);

#define __Rgb8bitPixelChannels_PNG_PIXELS_SIZE sizeof(Rgb8bitPixelChannels)

#endif
