#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  IEEE32 originX;
  IEEE32 originY;
  IEEE32 magnitude;
  Rgb8bitPixelChannels color;
} Cell;

int main(void)
{
  U32 pixelsWidth = 64;
  U32 pixelsHeight = 64;
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
          pixelColumnIndex,
          pixelRowIndex);
      currentPixelChannels_ptr->red = 255;
      currentPixelChannels_ptr->green = 178;
      currentPixelChannels_ptr->blue = 0;
    }
  }
  IEEE64 viewCenterX = 0;
  IEEE64 viewCenterY = 0;
  IEEE64 viewMagnitude = 1;
  IEEE64 viewLength = 2 * viewMagnitude;
  IEEE64 viewLeftBoundsX = viewCenterX - viewMagnitude;
  IEEE64 viewRightBoundsX = viewCenterX + viewMagnitude; // viewLeftBoundsX + viewLength
  IEEE64 viewTopBoundsY = viewCenterY + viewMagnitude;
  IEEE64 viewBottomBoundsY = viewCenterY - viewMagnitude; // viewTopBoundsY - viewLength
  U32 circleCellCount = 12;
  IEEE64 circleRadius = 0.9;
  IEEE64 circleOriginX = 0;
  IEEE64 circleOriginY = 0;
  IEEE64 circleCellMagnitude = 0.05;
  // U32 pixelsCenterColumnIndex = pngPixels->width / 2;
  // U32 pixelsCenterRowIndex = pngPixels->height / 2;
  // U32 viewColumnDimensionMagnitude = pngPixels->width - viewCenterColumnIndex - 1;
  // U32 viewRowDimensionMagnitude = pngPixels->height - viewCenterRowIndex - 1;
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
    IEEE64 circleCellLeftX =
      circleCellOriginX - circleCellMagnitude;
    IEEE64 circleCellRightX =
      circleCellOriginX + circleCellMagnitude;
    IEEE64 circleCellTopY =
      circleCellOriginY + circleCellMagnitude;
    IEEE64 circleCellBottomY =
      circleCellOriginY - circleCellMagnitude;
    if (circleCellRightX < viewLeftBoundsX || circleCellLeftX > viewRightBoundsX || circleCellBottomY > viewTopBoundsY || circleCellTopY < viewBottomBoundsY)
    {
      continue;
    }
    IEEE64 viewCellLeftX =
      circleCellLeftX < viewLeftBoundsX ? viewLeftBoundsX : circleCellLeftX;
    IEEE64 viewCellRightX =
      circleCellRightX > viewRightBoundsX ? viewRightBoundsX : circleCellRightX;
    IEEE64 viewCellTopY =
      circleCellTopY < viewTopBoundsY ? viewTopBoundsY : circleCellTopY;
    IEEE64 viewCellBottomY =
      circleCellBottomY > viewTopBoundsY ? viewTopBoundsY : circleCellBottomY;
    U32 viewCellLeftColumnIndex = 
      (viewCellLeftX - viewLeftBoundsX) / viewLength * pixelsWidth;
    U32 viewCellRightColumnIndex = 
      (viewCellRightX - viewLeftBoundsX) / viewLength * pixelsWidth;
    // U32 viewCellTopRowIndex = 
    //   (viewCellTop - view) / viewLength * pixelsWidth;
    // U32 viewCellBottomRowIndex = 
    //   (viewCellRightX - viewLeftBoundsX) / viewLength * pixelsWidth;
    printf("%d %d\n", viewCellLeftColumnIndex, viewCellRightColumnIndex);
    // U32 viewCellTopRowIndex = -1todo;
    // U32 viewCellBottomRowIndex = -1todo;
    //   (U32)(circlePointRadius * viewColumnDimensionMagnitude * pointCos) + viewCenterColumnIndex;
    // U32 pointRowIndex =
    //   (U32)(circlePointRadius * viewRowDimensionMagnitude * pointSin) + viewCenterRowIndex;
    // currentPixelChannels_ptr =
    //   atPixelsDataPixelChannels(
    //     pngPixels,
    //     pointColumnIndex,
    //     pointRowIndex);
    // currentPixelChannels_ptr->red = 0;
    // currentPixelChannels_ptr->green = 0;
    // currentPixelChannels_ptr->blue = 0;
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
