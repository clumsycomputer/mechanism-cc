#include "LinearAlgebra.h"
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
  IEEE64 cameraPositionHorizontal = 0;
  IEEE64 cameraPositionVertical = 0;
  IEEE64 cameraPositionDepth = -2;
  IEEE64 cameraTargetHorizontal = 0;
  IEEE64 cameraTargetVertical = 0;
  IEEE64 cameraTargetDepth = 0;
  IEEE64 cameraUpOrientationHorizontal = 0;
  IEEE64 cameraUpOrientationVertical = 1;
  IEEE64 cameraUpOrientationDepth = 0;
  IEEE64 cameraForwardHorizontal =
    cameraPositionHorizontal - cameraTargetHorizontal;
  IEEE64 cameraForwardVertical =
    cameraPositionVertical - cameraTargetVertical;
  IEEE64 cameraForwardDepth =
    cameraPositionDepth - cameraTargetDepth;
  IEEE64 cameraForwardMagnitude =
    calcVector3Magnitude(
      cameraForwardHorizontal,
      cameraForwardVertical,
      cameraForwardDepth);
  IEEE64 cameraNormalForwardHorizontal =
    cameraForwardHorizontal / cameraForwardMagnitude;
  IEEE64 cameraNormalForwardVertical =
    cameraForwardVertical / cameraForwardMagnitude;
  IEEE64 cameraNormalForwardDepth =
    cameraForwardDepth / cameraForwardMagnitude;
  IEEE64 cameraRightHorizontal =
    calcVector3CrossProductHorizontal(
      cameraUpOrientationVertical,
      cameraUpOrientationDepth,
      cameraNormalForwardVertical,
      cameraNormalForwardDepth);
  IEEE64 cameraRightVertical =
    calcVector3CrossProductVertical(
      cameraUpOrientationHorizontal,
      cameraUpOrientationDepth,
      cameraNormalForwardHorizontal,
      cameraNormalForwardDepth);
  IEEE64 cameraRightDepth =
    calcVector3CrossProductDepth(
      cameraUpOrientationHorizontal,
      cameraUpOrientationVertical,
      cameraNormalForwardHorizontal,
      cameraNormalForwardVertical);
  IEEE64 cameraRightMagnitude =
    calcVector3Magnitude(
      cameraRightHorizontal,
      cameraRightVertical,
      cameraRightDepth);
  IEEE64 cameraNormalRightHorizontal =
    cameraRightHorizontal / cameraRightMagnitude;
  IEEE64 cameraNormalRightVertical =
    cameraRightVertical / cameraRightMagnitude;
  IEEE64 cameraNormalRightDepth =
    cameraRightDepth / cameraRightMagnitude;
  IEEE64 cameraAdjustedUpHorizontal =
    calcVector3CrossProductHorizontal(
      cameraNormalForwardVertical,
      cameraNormalForwardDepth,
      cameraNormalRightVertical,
      cameraNormalRightDepth);
  IEEE64 cameraAdjustedUpVertical =
    calcVector3CrossProductVertical(
      cameraNormalForwardHorizontal,
      cameraNormalForwardDepth,
      cameraNormalRightHorizontal,
      cameraNormalRightDepth);
  IEEE64 cameraAdjustedUpDepth =
    calcVector3CrossProductDepth(
      cameraNormalForwardHorizontal,
      cameraNormalForwardVertical,
      cameraNormalRightHorizontal,
      cameraNormalRightVertical);
  IEEE64 cameraAdjustedUpMagnitude =
    calcVector3Magnitude(
      cameraAdjustedUpHorizontal,
      cameraAdjustedUpVertical,
      cameraAdjustedUpDepth);
  IEEE64 cameraNormalAdjustedUpHorizontal =
    cameraAdjustedUpHorizontal / cameraAdjustedUpMagnitude;
  IEEE64 cameraNormalAdjustedUpVertical =
    cameraAdjustedUpVertical / cameraAdjustedUpMagnitude;
  IEEE64 cameraNormalAdjustedUpDepth =
    cameraAdjustedUpDepth / cameraAdjustedUpMagnitude;
  IEEE64 perspectiveFieldOfView = M_PI_2;
  IEEE64 perspectiveNearClippingPlaneDepth = 0.01;
  IEEE64 perspectiveFarClippingPlaneDepth = 4;
  IEEE64 perspectiveHorizontalRowHorizontalColumnScalar =
    1 / (pixelsWidthOverHeightAspectRatio * tan(perspectiveFieldOfView / 2));
  IEEE64 perspectiveVerticalRowVerticalColumnScalar =
    1 / tan(perspectiveFieldOfView / 2);
  IEEE64 perspectiveDepthRowDepthColumnScalar =
    (perspectiveNearClippingPlaneDepth + perspectiveFarClippingPlaneDepth) / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 perspectiveDepthRowHomogeneousColumnScalar =
    2 * perspectiveNearClippingPlaneDepth * perspectiveFarClippingPlaneDepth / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 transformHorizontalHorizontalColumnScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraNormalRightHorizontal,
      cameraNormalRightVertical,
      cameraNormalRightDepth,
      -calcVector3DotProduct(
        cameraNormalRightHorizontal,
        cameraNormalRightVertical,
        cameraNormalRightDepth,
        cameraPositionHorizontal,
        cameraPositionVertical,
        cameraPositionDepth));
  IEEE64 transformHorizontalVerticalColumnScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraNormalRightHorizontal,
      cameraNormalRightVertical,
      cameraNormalRightDepth,
      -calcVector3DotProduct(
        cameraNormalRightHorizontal,
        cameraNormalRightVertical,
        cameraNormalRightDepth,
        cameraPositionHorizontal,
        cameraPositionVertical,
        cameraPositionDepth));
  S32 sphereHorizontalVerticalPolarAngleCount = 7;
  IEEE64 sphereHorizontalVerticalPolarAngleStep =
    (2 * M_PI) / sphereHorizontalVerticalPolarAngleCount;
  S32 spherePolarOrthogonalDepthAngleCount = 7;
  IEEE64 spherePolarOrthogonalDepthAngleStep =
    M_PI / spherePolarOrthogonalDepthAngleCount;
  IEEE64 sphereOriginDepth = 0;
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
        spherePointHorizontal * perspectiveHorizontalRowHorizontalColumnScalar;
      IEEE64 perspectivePointVertical =
        spherePointVertical * perspectiveVerticalRowVerticalColumnScalar;
      IEEE64 perspectivePointDepth =
        spherePointDepth * perspectiveDepthRowDepthColumnScalar + 1 * perspectiveDepthRowHomogeneousColumnScalar;
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
      for (S32 currentCellPixelRowIndex = cellPixelRowIndexMinimum; currentCellPixelRowIndex <= cellPixelRowIndexMaximum; currentCellPixelRowIndex++)
      {
        for (S32 currentCellPixelColumnIndex = cellPixelColumnIndexMinimum; currentCellPixelColumnIndex <= cellPixelColumnIndexMaximum; currentCellPixelColumnIndex++)
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
