#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  U32 pixelsWidth = 49;
  U32 pixelsHeight = 49;
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
  S32 pixelsMinimimumDimension =
    getPixelsMinimumDimension(pngPixels);
  IEEE64 pixelsNormalizedDimensionMagnitudeHorizontal =
    (IEEE64)pngPixels->width / pixelsMinimimumDimension;
  IEEE64 pixelsNormalizedDimensionMagnitudeVertical =
    (IEEE64)pngPixels->height / pixelsMinimimumDimension;
  IEEE64 pixelsNormalizedDimensionLengthHorizontal =
    2 * pixelsNormalizedDimensionMagnitudeHorizontal;
  IEEE64 pixelsNormalizedDimensionLengthVertical =
    2 * pixelsNormalizedDimensionMagnitudeVertical;
  // IEEE64 cameraPositionHorizontal = 0;
  // IEEE64 cameraPositionVertical = 0;
  // IEEE64 cameraPositionDepth = 0;
  // IEEE64 cameraTargetHorizontal = 0;
  // IEEE64 cameraTargetVertical = 0;
  // IEEE64 cameraTargetDepth = 0;
  // IEEE64 cameraUpOrientationHorizontal = -1todo;
  // IEEE64 cameraUpOrientationVertical = -1todo;
  // IEEE64 cameraUpOrientationDepth = -1todo;
  IEEE64 perspectiveFieldOfView = M_PI_2;
  IEEE64 perspectiveNearClippingPlaneDepth = 0.01;
  IEEE64 perspectiveFarClippingPlaneDepth = 4;
  IEEE64 perspectiveHorizontalHorizontalScalar =
    1 / (pixelsWidthOverHeightAspectRatio * tan(perspectiveFieldOfView / 2));
  IEEE64 perspectiveVerticalVerticalScalar =
    1 / tan(perspectiveFieldOfView / 2);
  IEEE64 perspectiveDepthDepthScalar =
    (perspectiveNearClippingPlaneDepth + perspectiveFarClippingPlaneDepth) / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 perspectiveDepthHomogeneousScalar =
    2 * perspectiveNearClippingPlaneDepth * perspectiveFarClippingPlaneDepth / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  S32 sphereHorizontalVerticalPolarAngleCount = 7;
  IEEE64 sphereHorizontalVerticalPolarAngleStep =
    (2 * M_PI) / sphereHorizontalVerticalPolarAngleCount;
  S32 spherePolarOrthogonalDepthAngleCount = 11;
  IEEE64 spherePolarOrthogonalDepthAngleStep =
    M_PI / spherePolarOrthogonalDepthAngleCount;
  IEEE64 sphereOriginDepth = 2;
  IEEE64 sphereRadius = 2;
  IEEE64 sphereCellMagnitude = 0.1;
  for (IEEE64 currentSphereHorizontalVerticalPolarAngle = M_PI_2; currentSphereHorizontalVerticalPolarAngle < (2 * M_PI + M_PI_2); currentSphereHorizontalVerticalPolarAngle += sphereHorizontalVerticalPolarAngleStep)
  {
    for (IEEE64 currentSpherePolarOrthogonalDepthAngle = 0; currentSpherePolarOrthogonalDepthAngle <= M_PI; currentSpherePolarOrthogonalDepthAngle += spherePolarOrthogonalDepthAngleStep)
    {
      IEEE64 spherePointHorizontal =
        sphereRadius * sin(currentSpherePolarOrthogonalDepthAngle) * cos(currentSphereHorizontalVerticalPolarAngle);
      IEEE64 spherePointVertical =
        sphereRadius * sin(currentSpherePolarOrthogonalDepthAngle) * sin(currentSphereHorizontalVerticalPolarAngle);
      IEEE64 spherePointDepth =
        sphereRadius * cos(currentSpherePolarOrthogonalDepthAngle) + sphereOriginDepth;
      IEEE64 perspectivePointHorizontal =
        spherePointHorizontal * perspectiveHorizontalHorizontalScalar;
      IEEE64 perspectivePointVertical =
        spherePointVertical * perspectiveVerticalVerticalScalar;
      IEEE64 perspectivePointDepth =
        spherePointDepth * perspectiveDepthDepthScalar + 1 * perspectiveDepthHomogeneousScalar;
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
      IEEE64 pixelsCellPointHorizontal =
        (cartesianPointHorizontal + pixelsNormalizedDimensionMagnitudeHorizontal) / pixelsNormalizedDimensionLengthHorizontal;
      IEEE64 pixelsCellPointVertical =
        (cartesianPointVertical + pixelsNormalizedDimensionMagnitudeVertical) / pixelsNormalizedDimensionLengthVertical;
      S32 cellCenterPixelColumnIndex =
        pixelsCellPointHorizontal * (S32)pngPixels->width;
      S32 cellCenterPixelRowIndex =
        pixelsCellPointVertical * (S32)pngPixels->height;
      if (cellCenterPixelColumnIndex < 0 || cellCenterPixelRowIndex >= (S32)pngPixels->width || cellCenterPixelColumnIndex < 0 || cellCenterPixelColumnIndex >= (S32)pngPixels->height)
      {
        continue;
      }
      S32 cellPixelMagnitude =
        ceil(cartesianCellMagnitude * pixelsMinimimumDimension);
      S32 cellPixelColumnIndexMinimum =
        cellCenterPixelColumnIndex - cellPixelMagnitude;
      cellPixelColumnIndexMinimum =
        cellPixelColumnIndexMinimum < 0 ? 0 : cellPixelColumnIndexMinimum;
      S32 cellPixelColumnIndexMaximum =
        cellCenterPixelColumnIndex + cellPixelMagnitude;
      cellPixelColumnIndexMaximum =
        cellPixelColumnIndexMaximum < (S32)pngPixels->width ? cellPixelColumnIndexMaximum : (S32)pngPixels->width - 1;
      S32 cellPixelRowIndexMinimum =
        cellCenterPixelRowIndex - cellPixelMagnitude;
      cellPixelRowIndexMinimum =
        cellPixelRowIndexMinimum < 0 ? 0 : cellPixelRowIndexMinimum;
      S32 cellPixelRowIndexMaximum =
        cellCenterPixelRowIndex + cellPixelMagnitude;
      cellPixelRowIndexMaximum =
        cellPixelRowIndexMaximum < (S32)pngPixels->height ? cellPixelRowIndexMaximum : (S32)pngPixels->height - 1;
      for (S32 currentCellPixelColumnIndex = cellPixelColumnIndexMinimum; currentCellPixelColumnIndex <= cellPixelColumnIndexMaximum; currentCellPixelColumnIndex++)
      {
        for (S32 currentCellPixelRowIndex = cellPixelRowIndexMinimum; currentCellPixelRowIndex <= cellPixelRowIndexMaximum; currentCellPixelRowIndex++)
        {
          currentPixelChannels_ptr =
            atPixelsDataPixelChannels(
              pngPixels,
              currentCellPixelColumnIndex,
              currentCellPixelRowIndex);
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
