#include "ClipView.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  U32 pixelsWidth = 2048;
  U32 pixelsHeight = 2048;
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(pixelsWidth, pixelsHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(pixelsWidth, pixelsHeight);
  U64 poolSize =
    pixelsSize + maxEncodingSize;
  HeapAllocation pngPool =
    (HeapAllocation)malloc(poolSize);
  Rgb8bitPngPixels* pngPixels =
    (Rgb8bitPngPixels*)pngPool;
  HeapAllocation pngEncoding =
    pngPool + pixelsSize;
  initRgb8bitPngPixels(
    pngPixels,
    pixelsWidth,
    pixelsHeight);
  initRgb8bitPngEncoding(
    pngEncoding,
    pngPixels);
  Rgb8bitPixelChannels* currentPixelChannels_ptr;
  for (U32 pixelRowIndex = 0; pixelRowIndex < pngPixels->height; pixelRowIndex++)
  {
    for (U32 pixelColumnIndex = 0; pixelColumnIndex < pngPixels->width; pixelColumnIndex++)
    {
      currentPixelChannels_ptr =
        atPixelsDataPixelChannels(
          pngPixels,
          pixelColumnIndex,
          pixelRowIndex);
      currentPixelChannels_ptr->red = 255;
      currentPixelChannels_ptr->green = 97;
      currentPixelChannels_ptr->blue = 0;
    }
  }
  U32 circleCellCount = 1024;
  IEEE64 circleRadius = 0.9;
  IEEE64 circleOriginX = 0;
  IEEE64 circleOriginY = 0;
  IEEE64 circleCellMagnitude = 0.005;
  for (U32 cellIndex = 0; cellIndex < circleCellCount; cellIndex++)
  {
    IEEE64 circleCellAngle =
      2 * M_PI / circleCellCount * cellIndex;
    IEEE64 circleCellCos =
      cos(circleCellAngle);
    IEEE64 circleCellSin =
      sin(circleCellAngle);
    IEEE64 circleCellOriginX =
      circleRadius * circleCellCos + circleOriginX;
    IEEE64 circleCellOriginY =
      circleRadius * circleCellSin + circleOriginY;
    IEEE64 circleCellLeft =
      circleCellOriginX - circleCellMagnitude;
    IEEE64 circleCellRight =
      circleCellOriginX + circleCellMagnitude;
    IEEE64 circleCellTop =
      circleCellOriginY - circleCellMagnitude;
    IEEE64 circleCellBottom =
      circleCellOriginY + circleCellMagnitude;
    IEEE64 clipViewCellLeft = circleCellLeft;
    IEEE64 clipViewCellRight = circleCellRight;
    IEEE64 clipViewCellTop = circleCellTop;
    IEEE64 clipViewCellBottom = circleCellBottom;
    if (false__Bool__STATIC_VALUE ==
        isClipViewCellVisible(
          clipViewCellLeft,
          clipViewCellRight,
          clipViewCellTop,
          clipViewCellBottom))
    {
      continue;
    }
    IEEE64 trimmedClipViewCellLeft =
      clipViewCellLeft < boundLeft__ClipView__STATIC_FIELD ? boundLeft__ClipView__STATIC_FIELD : clipViewCellLeft;
    IEEE64 trimmedClipViewCellRight =
      clipViewCellRight > boundRight__ClipView__STATIC_FIELD ? boundRight__ClipView__STATIC_FIELD : clipViewCellRight;
    IEEE64 trimmedClipViewCellTop =
      clipViewCellTop < boundTop__ClipView__STATIC_FIELD ? boundTop__ClipView__STATIC_FIELD : clipViewCellTop;
    IEEE64 trimmedClipViewCellBottom =
      clipViewCellBottom > boundBottom__ClipView__STATIC_FIELD ? boundBottom__ClipView__STATIC_FIELD : clipViewCellBottom;
    U32 clipViewCellPixelIndexLeft =
      (trimmedClipViewCellLeft - boundLeft__ClipView__STATIC_FIELD) / dimensionLength__ClipView__STATIC_FIELD * pngPixels->width;
    U32 clipViewCellPixelIndexRight =
      (trimmedClipViewCellRight - boundLeft__ClipView__STATIC_FIELD) / dimensionLength__ClipView__STATIC_FIELD * pngPixels->width;
    U32 clipViewCellPixelIndexTop =
      (trimmedClipViewCellTop - boundTop__ClipView__STATIC_FIELD) / dimensionLength__ClipView__STATIC_FIELD * pngPixels->height;
    U32 clipViewCellPixelIndexBottom =
      (trimmedClipViewCellBottom - boundTop__ClipView__STATIC_FIELD) / dimensionLength__ClipView__STATIC_FIELD * pngPixels->height;
    for (U32 pixelColumnIndex = clipViewCellPixelIndexLeft; pixelColumnIndex <= clipViewCellPixelIndexRight; pixelColumnIndex++)
    {
      for (U32 pixelRowIndex = clipViewCellPixelIndexTop; pixelRowIndex <= clipViewCellPixelIndexBottom; pixelRowIndex++)
      {
        currentPixelChannels_ptr =
          atPixelsDataPixelChannels(
            pngPixels,
            pixelColumnIndex,
            pixelRowIndex);
        currentPixelChannels_ptr->red = 0;
        currentPixelChannels_ptr->green = 0;
        currentPixelChannels_ptr->blue = 0;
      }
    }
  }
  encodeRgb8bitPngPixels(
    pngEncoding,
    pngPixels);
  FILE* pngFile_ptr =
    fopen(
      "foo.png",
      "wb");
  fwrite(
    pngEncoding,
    1,
    getRgb8bitPngEncodingSize(pngEncoding),
    pngFile_ptr);
  fclose(pngFile_ptr);
  free(pngPool);
  return 0;
}
