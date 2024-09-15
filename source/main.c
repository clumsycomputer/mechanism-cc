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
  IEEE64 pixelsWidthOverHeightAspectRatio =
    getPixelsWidthOverHeightAspectRatio(pngPixels);
  IEEE64 pixelsMinimimumDimension =
    getPixelsMinimumDimension(pngPixels);
  IEEE64 cartesianHorizontalNormalizedDimensionMagnitude =
    (IEEE64)pngPixels->width / pixelsMinimimumDimension;
  IEEE64 cartesianVerticalNormalizedDimensionMagnitude =
    (IEEE64)pngPixels->height / pixelsMinimimumDimension;
  IEEE64 cartesianHorizontalNormalizedDimensionLength =
    2 * cartesianHorizontalNormalizedDimensionMagnitude;
  IEEE64 cartesianVerticalNormalizedDimensionLength =
    2 * cartesianVerticalNormalizedDimensionMagnitude;
  IEEE64 perspectiveFieldOfView = M_PI_2;
  IEEE64 perspectiveNearClippingPlaneDepth = 0.001;
  IEEE64 perspectiveFarClippingPlaneDepth = 4;
  IEEE64 perspectiveHorizontalHorizontalScalar =
    1 / (pixelsWidthOverHeightAspectRatio * tan(perspectiveFieldOfView / 2));
  IEEE64 perspectiveVerticalVerticalScalar =
    1 / tan(perspectiveFieldOfView / 2);
  IEEE64 perspectiveDepthDepthScalar =
    (perspectiveNearClippingPlaneDepth + perspectiveFarClippingPlaneDepth) / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 perspectiveDepthHomogeneousScalar =
    2 * perspectiveNearClippingPlaneDepth * perspectiveFarClippingPlaneDepth / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  U32 sphereHorizontalVerticalPolarAngleCount = 5;
  IEEE64 sphereHorizontalVerticalPolarAngleStep =
    (2 * M_PI) / sphereHorizontalVerticalPolarAngleCount;
  U32 spherePolarOrthogonalDepthAngleCount = 11;
  IEEE64 spherePolarOrthogonalDepthAngleStep =
    M_PI / spherePolarOrthogonalDepthAngleCount;
  IEEE64 sphereOriginDepth = 2;
  IEEE64 sphereRadius = 0.9;
  IEEE64 sphereCellMagnitude = 0.01;
  for (IEEE64 currentSphereHorizontalVerticalPolarAngle = 0; currentSphereHorizontalVerticalPolarAngle < (M_PI * 2); currentSphereHorizontalVerticalPolarAngle += sphereHorizontalVerticalPolarAngleStep)
  {
    for (IEEE64 currentSpherePolarOrthogonalDepthAngle = -M_PI_2; currentSpherePolarOrthogonalDepthAngle <= M_PI_2; currentSpherePolarOrthogonalDepthAngle += spherePolarOrthogonalDepthAngleStep)
    {
      IEEE64 spherePointHorizontal =
        sphereRadius * sin(currentSpherePolarOrthogonalDepthAngle - M_PI_2) * cos(currentSphereHorizontalVerticalPolarAngle + M_PI_2);
      IEEE64 spherePointVertical =
        sphereRadius * sin(currentSpherePolarOrthogonalDepthAngle - M_PI_2) * sin(currentSphereHorizontalVerticalPolarAngle + M_PI_2);
      IEEE64 spherePointDepth =
        sphereRadius * cos(currentSpherePolarOrthogonalDepthAngle - M_PI_2) + sphereOriginDepth;
      IEEE64 perspectivePointHorizontal =
        spherePointHorizontal * perspectiveHorizontalHorizontalScalar;
      IEEE64 perspectivePointVertical =
        spherePointVertical * perspectiveVerticalVerticalScalar;
      IEEE64 perspectivePointDepth =
        spherePointDepth * perspectiveDepthDepthScalar + 0 * perspectiveDepthHomogeneousScalar;
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
        continue;
      }
      IEEE64 cellLeftViewPoint =
        cellLeftPoint < -cartesianHorizontalNormalizedDimensionMagnitude ? -cartesianHorizontalNormalizedDimensionMagnitude : cellLeftPoint;
      IEEE64 cellRightViewPoint =
        cellRightPoint > cartesianHorizontalNormalizedDimensionMagnitude ? cartesianHorizontalNormalizedDimensionMagnitude : cellRightPoint;
      IEEE64 cellTopViewPoint =
        cellTopPoint < -cartesianVerticalNormalizedDimensionMagnitude ? -cartesianVerticalNormalizedDimensionMagnitude : cellTopPoint;
      IEEE64 cellBottomViewPoint =
        cellBottomPoint > cartesianVerticalNormalizedDimensionMagnitude ? cartesianVerticalNormalizedDimensionMagnitude : cellBottomPoint;
      IEEE64 normalizedCellLeftViewPoint =
        (cellLeftViewPoint + cartesianHorizontalNormalizedDimensionMagnitude) / cartesianHorizontalNormalizedDimensionLength;
      IEEE64 normalizedCellRightViewPoint =
        (cellRightViewPoint + cartesianHorizontalNormalizedDimensionMagnitude) / cartesianHorizontalNormalizedDimensionLength;
      IEEE64 normalizedCellTopViewPoint =
        (cellTopViewPoint + cartesianVerticalNormalizedDimensionMagnitude) / cartesianVerticalNormalizedDimensionLength;
      IEEE64 normalizedCellBottomViewPoint =
        (cellBottomViewPoint + cartesianVerticalNormalizedDimensionMagnitude) / cartesianVerticalNormalizedDimensionLength;
      U32 cellLeftColumnIndex =
        normalizedCellLeftViewPoint * pngPixels->width;
      U32 cellRightColumnIndex =
        normalizedCellRightViewPoint * pngPixels->width;
      U32 cellTopRowIndex =
        normalizedCellTopViewPoint * pngPixels->height;
      U32 cellBottomRowIndex =
        normalizedCellBottomViewPoint * pngPixels->height;
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
