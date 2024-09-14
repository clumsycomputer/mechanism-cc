#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  U32 pixelsWidth = 512;
  U32 pixelsHeight = 512;
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
  IEEE64 pixelsWidthOverHeightAspectRatio =
    getPixelsWidthOverHeightAspectRatio(pngPixels);
  IEEE64 pixelsMinimimumDimension =
    getPixelsMinimumDimension(pngPixels);
  IEEE64 cartesianHorizontalNormalizedDimensionMagnitude =
    (IEEE64)pngPixels->width / pixelsMinimimumDimension;
  IEEE64 cartesianVerticalNormalizedDimensionMagnitude =
    (IEEE64)pngPixels->height / pixelsMinimimumDimension;
  IEEE64 sphereOriginDepth = 2;
  IEEE64 sphereRadius = 0.9;
  IEEE64 sphereHorizontalVerticalPolarAngle = M_PI;
  IEEE64 spherePolarOrthogonalDepthAngle = M_PI;
  IEEE64 sphereCellMagnitude = 0.01;
  IEEE64 spherePointHorizontal = sphereRadius * sin(spherePolarOrthogonalDepthAngle - M_PI_2) * cos(sphereHorizontalVerticalPolarAngle + M_PI_2);
  IEEE64 spherePointVertical = sphereRadius * sin(spherePolarOrthogonalDepthAngle - M_PI_2) * sin(sphereHorizontalVerticalPolarAngle + M_PI_2);
  IEEE64 spherePointDepth = sphereRadius * cos(spherePolarOrthogonalDepthAngle - M_PI_2) + sphereOriginDepth;
  IEEE64 perspectiveFieldOfView = M_PI_2;
  IEEE64 perspectiveNearClippingPlaneDepth = 0.001;
  IEEE64 perspectiveFarClippingPlaneDepth = 4;
  IEEE64 perspectivePointHorizontal =
    spherePointHorizontal * (1 / (pixelsWidthOverHeightAspectRatio * tan(perspectiveFieldOfView / 2)));
  IEEE64 perspectivePointVertical =
    spherePointVertical * (1 / tan(perspectiveFieldOfView / 2));
  IEEE64 perspectivePointDepth =
    spherePointDepth * ((perspectiveNearClippingPlaneDepth + perspectiveFarClippingPlaneDepth) / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth)) + 2 * perspectiveNearClippingPlaneDepth * perspectiveFarClippingPlaneDepth / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 perspectivePointHomogeneous =
    spherePointDepth;
  IEEE64 cartesianPointHorizontal =
    perspectivePointHorizontal / perspectivePointHomogeneous;
  IEEE64 cartesianPointVertical =
    perspectivePointVertical / perspectivePointHomogeneous;
  IEEE64 cartesianPointDepth =
    perspectivePointDepth / perspectivePointHomogeneous;
  IEEE64 cartesianCellMagnitude =
    sphereCellMagnitude / perspectivePointHomogeneous;

  IEEE64 cellLeftPoint =
    cartesianPointHorizontal - cartesianCellMagnitude;
  IEEE64 cellRightPoint =
    cartesianPointHorizontal + cartesianCellMagnitude;
  IEEE64 cellTopPoint =
    cartesianPointVertical - cartesianCellMagnitude;
  IEEE64 cellBottomPoint =
    cartesianPointVertical + cartesianCellMagnitude;
  if (cellLeftPoint > cartesianHorizontalNormalizedDimensionMagnitude || cellRightPoint < -cartesianHorizontalNormalizedDimensionMagnitude || cellTopPoint > cartesianVerticalNormalizedDimensionMagnitude || cellBottomPoint < -cartesianVerticalNormalizedDimensionMagnitude)
  {
    return 1;
  }
  IEEE64 cellLeftViewPoint = cellLeftPoint < -cartesianHorizontalNormalizedDimensionMagnitude ? -cartesianHorizontalNormalizedDimensionMagnitude : cellLeftPoint;
  IEEE64 cellRightViewPoint = cellRightPoint > cartesianHorizontalNormalizedDimensionMagnitude ? cartesianHorizontalNormalizedDimensionMagnitude : cellRightPoint;
  IEEE64 cellTopViewPoint = cellTopPoint < -cartesianVerticalNormalizedDimensionMagnitude ? -cartesianVerticalNormalizedDimensionMagnitude : cellTopPoint;
  IEEE64 cellBottomViewPoint = cellBottomPoint > cartesianVerticalNormalizedDimensionMagnitude ? cartesianVerticalNormalizedDimensionMagnitude : cellBottomPoint;
  // IEEE64 cellLeftViewPixel
  U32 cellLeftColumnIndex = (cellLeftViewPoint - -cartesianHorizontalNormalizedDimensionMagnitude) / (2 * cartesianHorizontalNormalizedDimensionMagnitude) * pngPixels->width;
  U32 cellRightColumnIndex = (cellRightViewPoint - -cartesianHorizontalNormalizedDimensionMagnitude) / (2 * cartesianHorizontalNormalizedDimensionMagnitude) * pngPixels->width;
  U32 cellTopRowIndex = (cellTopViewPoint - -cartesianVerticalNormalizedDimensionMagnitude) / (2 * cartesianVerticalNormalizedDimensionMagnitude) * pngPixels->height;
  U32 cellBottomRowIndex = (cellBottomViewPoint - -cartesianVerticalNormalizedDimensionMagnitude) / (2 * cartesianVerticalNormalizedDimensionMagnitude) * pngPixels->height;
  for (U32 cellCurrentColumnIndex = cellLeftColumnIndex; cellCurrentColumnIndex <= cellRightColumnIndex; cellCurrentColumnIndex++)
  {
    for (U32 cellCurrentRowIndex = cellTopRowIndex; cellCurrentRowIndex < cellBottomRowIndex; cellCurrentRowIndex++)
    {
      currentPixelChannels_ptr =
        atPixelsDataPixelChannels(
          pngPixels,
          cellCurrentColumnIndex,
          cellCurrentRowIndex);
      currentPixelChannels_ptr->red = 0;
      currentPixelChannels_ptr->green = 0;
      currentPixelChannels_ptr->blue = 0;
    }
  }

  // U32 sphereCellCount = 512;

  // IEEE64 circleRadius = 0.9;
  // IEEE64 circleCenterHorizontal = 0;
  // IEEE64 circleCenterVertical= 0;
  // U32 circleCellCount = 1024;
  // IEEE64 circleCellMagnitude = 0.005;
  // for (U32 cellIndex = 0; cellIndex < circleCellCount; cellIndex++)
  // {
  //   IEEE64 circleCellAngle =
  //     2 * M_PI / circleCellCount * cellIndex;
  //   IEEE64 circleCellCos =
  //     cos(circleCellAngle);
  //   IEEE64 circleCellSin =
  //     sin(circleCellAngle);
  //   IEEE64 circleCellOriginX =
  //     circleRadius * circleCellCos + circleCenterHorizontal;
  //   IEEE64 circleCellOriginY =
  //     circleRadius * circleCellSin + circleCenterVertical;
  //   IEEE64 circleCellLeft =
  //     circleCellOriginX - circleCellMagnitude;
  //   IEEE64 circleCellRight =
  //     circleCellOriginX + circleCellMagnitude;
  //   IEEE64 circleCellTop =
  //     circleCellOriginY - circleCellMagnitude;
  //   IEEE64 circleCellBottom =
  //     circleCellOriginY + circleCellMagnitude;
  //   IEEE64 clipViewCellLeft = circleCellLeft;
  //   IEEE64 clipViewCellRight = circleCellRight;
  //   IEEE64 clipViewCellTop = circleCellTop;
  //   IEEE64 clipViewCellBottom = circleCellBottom;
  //   if (false__Bool__STATIC_VALUE ==
  //       isPixelsViewportCellVisible(
  //         clipViewCellLeft,
  //         clipViewCellRight,
  //         clipViewCellTop,
  //         clipViewCellBottom))
  //   {
  //     continue;
  //   }
  //   IEEE64 trimmedPixelsViewportCellLeft =
  //     clipViewCellLeft < boundLeft__PixelsViewport__STATIC_FIELD ? boundLeft__PixelsViewport__STATIC_FIELD : clipViewCellLeft;
  //   IEEE64 trimmedPixelsViewportCellRight =
  //     clipViewCellRight > boundRight__PixelsViewport__STATIC_FIELD ? boundRight__PixelsViewport__STATIC_FIELD : clipViewCellRight;
  //   IEEE64 trimmedPixelsViewportCellTop =
  //     clipViewCellTop < boundTop__PixelsViewport__STATIC_FIELD ? boundTop__PixelsViewport__STATIC_FIELD : clipViewCellTop;
  //   IEEE64 trimmedPixelsViewportCellBottom =
  //     clipViewCellBottom > boundBottom__PixelsViewport__STATIC_FIELD ? boundBottom__PixelsViewport__STATIC_FIELD : clipViewCellBottom;
  //   U32 clipViewCellPixelIndexLeft =
  //     (trimmedPixelsViewportCellLeft - boundLeft__PixelsViewport__STATIC_FIELD) / dimensionLength__PixelsViewport__STATIC_FIELD * pngPixels->width;
  //   U32 clipViewCellPixelIndexRight =
  //     (trimmedPixelsViewportCellRight - boundLeft__PixelsViewport__STATIC_FIELD) / dimensionLength__PixelsViewport__STATIC_FIELD * pngPixels->width;
  //   U32 clipViewCellPixelIndexTop =
  //     (trimmedPixelsViewportCellTop - boundTop__PixelsViewport__STATIC_FIELD) / dimensionLength__PixelsViewport__STATIC_FIELD * pngPixels->height;
  //   U32 clipViewCellPixelIndexBottom =
  //     (trimmedPixelsViewportCellBottom - boundTop__PixelsViewport__STATIC_FIELD) / dimensionLength__PixelsViewport__STATIC_FIELD * pngPixels->height;
  //   for (U32 pixelColumnIndex = clipViewCellPixelIndexLeft; pixelColumnIndex <= clipViewCellPixelIndexRight; pixelColumnIndex++)
  //   {
  //     for (U32 pixelRowIndex = clipViewCellPixelIndexTop; pixelRowIndex <= clipViewCellPixelIndexBottom; pixelRowIndex++)
  //     {
  //       currentPixelChannels_ptr =
  //         atPixelsDataPixelChannels(
  //           pngPixels,
  //           pixelColumnIndex,
  //           pixelRowIndex);
  //       currentPixelChannels_ptr->red = 0;
  //       currentPixelChannels_ptr->green = 0;
  //       currentPixelChannels_ptr->blue = 0;
  //     }
  //   }
  // }
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
