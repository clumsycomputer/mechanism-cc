#include "ImageArena.h"
#include "ImagePixels.h"
#include <stdlib.h>

ImageArena __createImageArena(
  U8 pixelsKind__,
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__,
  U16 pixelsWidth,
  U16 pixelsHeight)
{
  HeapAllocation arenaAllocation =
    (HeapAllocation)malloc(
      calcPixelsByteCount(
        pixelsChannelCount__,
        pixelsChannelBitDepth__,
        pixelsWidth,
        pixelsHeight));
  ImageArena imageArena = {
    .arenaAllocation = arenaAllocation,
    .arenaPixels = (__ImagePixels)(arenaAllocation + PIXELS_METADATA_BYTE_SIZE),
  };
  __initPixelsMetadata(
    pixelsKind__,
    pixelsChannelCount__,
    pixelsChannelBitDepth__,
    pixelsWidth,
    pixelsHeight,
    imageArena.arenaPixels);
  return imageArena;
}

ImageArena createRgb8bitImageArena(U16 pixelsWidth, U16 pixelsHeight)
{
  return __createImageArena(
    __PixelsKind_RGB_8bit,
    __PixelsChannelCount_RGB,
    __PixelsKind_RGB_8bit,
    pixelsWidth,
    pixelsHeight);
}
