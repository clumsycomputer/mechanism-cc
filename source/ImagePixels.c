#include "ImagePixels.h"
#include <stdlib.h>

U8* atPixelsKind(__ImagePixels imagePixels)
{
  return imagePixels - PIXELS_KIND_PTR_OFFSET;
}

U8* atPixelsChannelCount(__ImagePixels imagePixels)
{
  return imagePixels - PIXELS_CHANNEL_COUNT_PTR_OFFSET;
}

U8* atPixelsChannelBitDepth(__ImagePixels imagePixels)
{
  return imagePixels - PIXELS_CHANNEL_BIT_DEPTH_PTR_OFFSET;
}

U16* atPixelsWidth(__ImagePixels imagePixels)
{
  return (U16*)(imagePixels - PIXELS_WIDTH_PTR_OFFSET);
}

U16* atPixelsHeight(__ImagePixels imagePixels)
{
  return (U16*)(imagePixels - PIXELS_HEIGHT_PTR_OFFSET);
}

__ImagePixels __createImagePixels(
  U8 pixelsKind,
  U8 pixelsChannelCount,
  U8 pixelsChannelBitDepth,
  U16 pixelsWidth,
  U16 pixelsHeight)
{
  U64 pixelsByteCount = pixelsChannelCount * (pixelsChannelBitDepth / BITS_PER_BYTE) * pixelsWidth * pixelsHeight;
  __ImagePixels imagePixelsResult = (__ImagePixels)malloc(pixelsByteCount + PIXELS_FIELDS_SIZE);
  imagePixelsResult += PIXELS_FIELDS_SIZE;
  *atPixelsKind(imagePixelsResult) = pixelsKind;
  *atPixelsChannelCount(imagePixelsResult) = pixelsChannelCount;
  *atPixelsChannelBitDepth(imagePixelsResult) = pixelsChannelBitDepth;
  *atPixelsWidth(imagePixelsResult) = pixelsWidth;
  *atPixelsHeight(imagePixelsResult) = pixelsHeight;
  return imagePixelsResult;
}

Rgb8bitImagePixels createRgb8bitImagePixels(U16 pixelsWidth, U16 pixelsHeight)
{
  return __createImagePixels(
    PixelsKind_RGB_8bit,
    PixelsChannelCount_RGB,
    PixelsChannelBitDepth_8,
    pixelsWidth,
    pixelsHeight);
}

U8 getPixelsKind(__ImagePixels imagePixels)
{
  return *atPixelsKind(imagePixels);
}

U8 getPixelsChannelCount(__ImagePixels imagePixels)
{
  return *atPixelsChannelCount(imagePixels);
}

U8 getPixelsChannelBitDepth(__ImagePixels imagePixels)
{
  return *atPixelsChannelBitDepth(imagePixels);
}

U16 getPixelsWidth(__ImagePixels imagePixels)
{
  return *atPixelsWidth(imagePixels);
}

U16 getPixelsHeight(__ImagePixels imagePixels)
{
  return *atPixelsHeight(imagePixels);
}
