#include "ImagePool.h"
#include "ImagePixels.h"
#include "ImagePng.h"
#include <stdlib.h>

ImagePoolView __createImagePool(
  U8 pixelsKind__,
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__,
  U16 pixelsWidth,
  U16 pixelsHeight,
  U8 pngKind__)
{
  U64 pixelsDataByteCount =
    calcPixelsDataByteCount(
      pixelsChannelCount__,
      pixelsChannelBitDepth__,
      pixelsWidth,
      pixelsHeight);
  U64 pixelsByteCount =
    calcPixelsByteCount(
      pixelsChannelCount__,
      pixelsChannelBitDepth__,
      pixelsWidth,
      pixelsHeight);
  U64 pngPaddingByteCount = ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE - (pixelsByteCount % ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE);
  U64 pngMaxByteCount =
    calcPngMaxByteCount(
      pixelsDataByteCount);
  U64 poolByteCount = pixelsByteCount + pngPaddingByteCount + pngMaxByteCount;
  ImagePool imagePool =
    (ImagePool)malloc(poolByteCount);
  ImagePoolView imagePoolView = {
    .__pool = imagePool,
    .poolPixels = (__ImagePixels)(imagePool + PIXELS_HEADER_SIZE_PLUS_PIXELS_DATA_PADDING_SIZE),
    .poolPng = (__ImagePng)(imagePool + pixelsByteCount + pngPaddingByteCount + PNG_HEADER_SIZE_PLUS_PNG_DATA_PADDING_SIZE)};
  __initPixelsConfig(
    pixelsKind__,
    pixelsChannelCount__,
    pixelsChannelBitDepth__,
    imagePoolView.poolPixels);
  __initPixelsConstants(
    pixelsWidth,
    pixelsHeight,
    imagePoolView.poolPixels);
  __initPngConfig(
    pngKind__,
    imagePoolView.poolPng);
  __initPngConstants(
    pixelsDataByteCount,
    imagePoolView.poolPng);
  __applyPngDataSignature(imagePoolView.poolPng);
  __applyPngDataIhdrChunk(
    pixelsWidth,
    pixelsHeight,
    pixelsChannelBitDepth__,
    imagePoolView.poolPng);
  return imagePoolView;
}

ImagePoolView createRgb8bitImagePool(U16 pixelsWidth, U16 pixelsHeight)
{
  return __createImagePool(
    __PixelsKind_Rgb8bit,
    __PixelsChannelCount_Rgb,
    __PixelsChannelBitDepth_8,
    pixelsWidth,
    pixelsHeight,
    __PngKind_Rgb8bit);
}

// ImagePoolView createRgb16bitImagePool(U16 pixelsWidth, U16 pixelsHeight, IEEE32 pngMaxCompressedPixelsByteCountScalar)
// {
//   return __createImagePool(
//     __PixelsKind_Rgb16bit,
//     __PixelsChannelCount_Rgb,
//     __PixelsChannelBitDepth_16,
//     pixelsWidth,
//     pixelsHeight,
//     __PngKind_Rgb16bit);
// }

void freeImagePool(ImagePoolView imagePoolView)
{
  free(imagePoolView.__pool);
}
