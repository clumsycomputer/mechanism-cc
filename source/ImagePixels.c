#include <stdlib.h>
#include "ImagePixels.h"

U8* getPixelsKindPtr(__ImagePixels imagePixels) {
  return imagePixels - PIXELS_KIND_PTR_OFFSET;
}

U8* getPixelsChannelCountPtr(__ImagePixels imagePixels) {
  return imagePixels - PIXELS_CHANNEL_COUNT_PTR_OFFSET;
}

U8* getPixelsChannelBitDepthPtr(__ImagePixels imagePixels) {
  return imagePixels - PIXELS_CHANNEL_BIT_DEPTH_PTR_OFFSET;
}

U16* getPixelsWidthPtr(__ImagePixels imagePixels) {
  return (U16*)(imagePixels - PIXELS_WIDTH_PTR_OFFSET);
}

U16* getPixelsHeightPtr(__ImagePixels imagePixels) {
  return (U16*)(imagePixels - PIXELS_HEIGHT_PTR_OFFSET);
}

__ImagePixels __createImagePixels(
    U8 pixelsKind,
    U8 pixelsChannelCount,
    U8 pixelsChannelBitDepth,
    U16 pixelsWidth,
    U16 pixelsHeight) {
  U64 pixelsByteCount = pixelsChannelCount * (pixelsChannelBitDepth / BITS_PER_BYTE) * pixelsWidth * pixelsHeight;
  __ImagePixels imagePixelsResult = (__ImagePixels)malloc(pixelsByteCount + PIXELS_FIELDS_SIZE);
  imagePixelsResult += PIXELS_FIELDS_SIZE;
  *getPixelsKindPtr(imagePixelsResult) = pixelsKind;
  *getPixelsChannelCountPtr(imagePixelsResult) = pixelsChannelCount;
  *getPixelsChannelBitDepthPtr(imagePixelsResult) = pixelsChannelBitDepth;
  *getPixelsWidthPtr(imagePixelsResult) = pixelsWidth;
  *getPixelsHeightPtr(imagePixelsResult) = pixelsHeight;
  return imagePixelsResult;
}

Rgb8bitImagePixels createRgb8bitImagePixels(U16 pixelsWidth, U16 pixelsHeight) {
  return __createImagePixels(
      PixelsKind_RGB_8bit,
      PixelsChannelCount_RGB,
      PixelsChannelBitDepth_8,
      pixelsWidth,
      pixelsHeight);
}

U8 getPixelsChannelCount(__ImagePixels imagePixels) {
  return *getPixelsChannelCountPtr(imagePixels);
}
