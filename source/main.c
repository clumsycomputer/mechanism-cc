#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  U32 pixelsWidth = 64 + 1;
  U32 pixelsHeight = 64 + 1;
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(pixelsWidth, pixelsHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(pixelsWidth, pixelsHeight);
  U64 poolSize =
    pixelsSize + maxEncodingSize;
  U8* pngPool =
    (U8*)malloc(poolSize);
  Rgb8bitPngPixels* pngPixels =
    (Rgb8bitPngPixels*)pngPool;
  U8* pngEncoding =
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
          pixelRowIndex,
          pixelColumnIndex);
      currentPixelChannels_ptr->red = 255;
      currentPixelChannels_ptr->green = 79;
      currentPixelChannels_ptr->blue = 0;
    }
  }
  U32 circlePointCount = 512;
  IEEE64 circlePointRadius = 0.9;
  U32 originPointColumnIndex = pngPixels->width / 2;
  U32 originPointRowIndex = pngPixels->height / 2;
  U32 columnViewDimensionMagnitude = pngPixels->width - originPointColumnIndex - 1;
  U32 rowViewDimensionMagnitude = pngPixels->height - originPointRowIndex - 1;
  for (U32 pointIndex = 0; pointIndex < circlePointCount; pointIndex++)
  {
    IEEE64 pointAngle =
      2 * M_PI / circlePointCount * pointIndex;
    IEEE64 pointCos =
      cos(pointAngle);
    IEEE64 pointSin =
      sin(pointAngle);
    U32 pointColumnIndex =
      (U32)(circlePointRadius * columnViewDimensionMagnitude * pointCos) + originPointColumnIndex;
    U32 pointRowIndex =
      (U32)(circlePointRadius * rowViewDimensionMagnitude * pointSin) + originPointRowIndex;
    currentPixelChannels_ptr =
      atPixelsDataPixelChannels(
        pngPixels,
        pointRowIndex,
        pointColumnIndex);
    currentPixelChannels_ptr->red = 0;
    currentPixelChannels_ptr->green = 0;
    currentPixelChannels_ptr->blue = 0;
  // }
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
