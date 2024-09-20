#include "LinearAlgebra.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  U32 pixelsWidth = 129;
  U32 pixelsHeight = 129;
  U8 backgroundColorRed = 255;
  U8 backgroundColorGreen = 97;
  U8 backgroundColorBlue = 0;
  S32 sphereHorizontalVerticalPolarAngleCount = 7;
  S32 spherePolarOrthogonalDepthAngleCount = 7;
  IEEE64 sphereOriginDepth = 2;
  IEEE64 sphereRadius = 1;
  IEEE64 sphereCellMagnitude = 0.1;
  U8 sphereCellColorRed = 0;
  U8 sphereCellColorGreen = 0;
  U8 sphereCellColorBlue = 0;
  IEEE64 cameraPositionHorizontal = 0;
  IEEE64 cameraPositionVertical = 0;
  IEEE64 cameraPositionDepth = 0;
  IEEE64 cameraTargetHorizontal = 0;
  IEEE64 cameraTargetVertical = 0;
  IEEE64 cameraTargetDepth = 2;
  IEEE64 cameraUpOrientationHorizontal = 0;
  IEEE64 cameraUpOrientationVertical = 1;
  IEEE64 cameraUpOrientationDepth = 0;
  IEEE64 perspectiveFieldOfView = M_PI_2;
  IEEE64 perspectiveNearClippingPlaneDepth = 0.01;
  IEEE64 perspectiveFarClippingPlaneDepth = 4;
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
      currentPixelChannels_ptr->red = backgroundColorRed;
      currentPixelChannels_ptr->green = backgroundColorGreen;
      currentPixelChannels_ptr->blue = backgroundColorBlue;
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
  IEEE64 cameraForwardHorizontal =
    cameraTargetHorizontal - cameraPositionHorizontal;
  IEEE64 cameraForwardVertical =
    cameraTargetVertical - cameraPositionVertical;
  IEEE64 cameraForwardDepth =
    cameraTargetDepth - cameraPositionDepth;
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
      cameraNormalForwardVertical,
      cameraNormalForwardDepth,
      cameraUpOrientationVertical,
      cameraUpOrientationDepth);
  IEEE64 cameraRightVertical =
    calcVector3CrossProductVertical(
      cameraNormalForwardHorizontal,
      cameraNormalForwardDepth,
      cameraUpOrientationHorizontal,
      cameraUpOrientationDepth);
  IEEE64 cameraRightDepth =
    calcVector3CrossProductDepth(
      cameraNormalForwardHorizontal,
      cameraNormalForwardVertical,
      cameraUpOrientationHorizontal,
      cameraUpOrientationVertical);
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
      cameraNormalRightVertical,
      cameraNormalRightDepth,
      cameraNormalForwardVertical,
      cameraNormalForwardDepth);
  IEEE64 cameraAdjustedUpVertical =
    calcVector3CrossProductVertical(
      cameraNormalRightHorizontal,
      cameraNormalRightDepth,
      cameraNormalForwardHorizontal,
      cameraNormalForwardDepth);
  IEEE64 cameraAdjustedUpDepth =
    calcVector3CrossProductDepth(
      cameraNormalRightHorizontal,
      cameraNormalRightVertical,
      cameraNormalForwardHorizontal,
      cameraNormalForwardVertical);
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
  IEEE64 perspectiveHorizontalRowHorizontalColumnScalar =
    1 / (pixelsWidthOverHeightAspectRatio * tan(perspectiveFieldOfView / 2));
  IEEE64 perspectiveVerticalRowVerticalColumnScalar =
    1 / tan(perspectiveFieldOfView / 2);
  IEEE64 perspectiveDepthRowDepthColumnScalar =
    (perspectiveNearClippingPlaneDepth + perspectiveFarClippingPlaneDepth) / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  IEEE64 perspectiveDepthRowHomogeneousColumnScalar =
    2 * perspectiveNearClippingPlaneDepth * perspectiveFarClippingPlaneDepth / (perspectiveFarClippingPlaneDepth - perspectiveNearClippingPlaneDepth);
  // IEEE64 cameraRowHorizontalColumnHorizontalScalar = cameraNormalRightHorizontal;
  IEEE64 cameraRowHorizontalColumnHomogeneousScalar =
    -calcVector3DotProduct(
      cameraNormalRightHorizontal,
      cameraNormalRightVertical,
      cameraNormalRightDepth,
      cameraPositionHorizontal,
      cameraPositionVertical,
      cameraPositionDepth);
  IEEE64 cameraRowVerticalColumnHomogeneousScalar =
    -calcVector3DotProduct(
      cameraNormalAdjustedUpHorizontal,
      cameraNormalAdjustedUpVertical,
      cameraNormalAdjustedUpDepth,
      cameraPositionHorizontal,
      cameraPositionVertical,
      cameraPositionDepth);
  IEEE64 cameraRowDepthColumnHomogeneousScalar =
    calcVector3DotProduct(
      cameraNormalForwardHorizontal,
      cameraNormalForwardVertical,
      cameraNormalForwardDepth,
      cameraPositionHorizontal,
      cameraPositionVertical,
      cameraPositionDepth);
  IEEE64 transformRowHorizontalColumnHorizontalScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraNormalRightHorizontal,
      cameraUpOrientationHorizontal,
      -cameraNormalForwardHorizontal,
      0);
  IEEE64 transformRowHorizontalColumnVerticalScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraNormalRightVertical,
      cameraUpOrientationVertical,
      -cameraNormalForwardVertical,
      0);
  IEEE64 transformRowHorizontalColumnDepthScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraNormalRightDepth,
      cameraUpOrientationDepth,
      -cameraNormalForwardDepth,
      0);
  IEEE64 transformRowHorizontalColumnHomogeneousScalar =
    calcMatrix4Element(
      perspectiveHorizontalRowHorizontalColumnScalar,
      0,
      0,
      0,
      cameraRowHorizontalColumnHomogeneousScalar,
      cameraRowVerticalColumnHomogeneousScalar,
      cameraRowDepthColumnHomogeneousScalar,
      1);
  IEEE64 transformRowVerticalColumnHorizontalScalar =
    calcMatrix4Element(
      0,
      perspectiveVerticalRowVerticalColumnScalar,
      0,
      0,
      cameraNormalRightHorizontal,
      cameraUpOrientationHorizontal,
      -cameraNormalForwardHorizontal,
      0);
  IEEE64 transformRowVerticalColumnVerticalScalar =
    calcMatrix4Element(
      0,
      perspectiveVerticalRowVerticalColumnScalar,
      0,
      0,
      cameraNormalRightVertical,
      cameraUpOrientationVertical,
      -cameraNormalForwardVertical,
      0);
  IEEE64 transformRowVerticalColumnDepthScalar =
    calcMatrix4Element(
      0,
      perspectiveVerticalRowVerticalColumnScalar,
      0,
      0,
      cameraNormalRightDepth,
      cameraUpOrientationDepth,
      -cameraNormalForwardDepth,
      0);
  IEEE64 transformRowVerticalColumnHomogeneousScalar =
    calcMatrix4Element(
      0,
      perspectiveVerticalRowVerticalColumnScalar,
      0,
      0,
      cameraRowHorizontalColumnHomogeneousScalar,
      cameraRowVerticalColumnHomogeneousScalar,
      cameraRowDepthColumnHomogeneousScalar,
      1);
  IEEE64 transformRowDepthColumnHorizontalScalar =
    calcMatrix4Element(
      0,
      0,
      perspectiveDepthRowDepthColumnScalar,
      perspectiveDepthRowHomogeneousColumnScalar,
      cameraNormalRightHorizontal,
      cameraUpOrientationHorizontal,
      -cameraNormalForwardHorizontal,
      0);
  IEEE64 transformRowDepthColumnVerticalScalar =
    calcMatrix4Element(
      0,
      0,
      perspectiveDepthRowDepthColumnScalar,
      perspectiveDepthRowHomogeneousColumnScalar,
      cameraNormalRightVertical,
      cameraUpOrientationVertical,
      -cameraNormalForwardVertical,
      0);
  IEEE64 transformRowDepthColumnDepthScalar =
    calcMatrix4Element(
      0,
      0,
      perspectiveDepthRowDepthColumnScalar,
      perspectiveDepthRowHomogeneousColumnScalar,
      cameraNormalRightDepth,
      cameraUpOrientationDepth,
      -cameraNormalForwardDepth,
      0);
  IEEE64 transformRowDepthColumnHomogeneousScalar =
    calcMatrix4Element(
      0,
      0,
      perspectiveDepthRowDepthColumnScalar,
      perspectiveDepthRowHomogeneousColumnScalar,
      cameraRowHorizontalColumnHomogeneousScalar,
      cameraRowVerticalColumnHomogeneousScalar,
      cameraRowDepthColumnHomogeneousScalar,
      1);
  IEEE64 transformRowHomogeneousColumnHorizontalScalar =
    calcMatrix4Element(
      0,
      0,
      1,
      0,
      cameraNormalRightHorizontal,
      cameraUpOrientationHorizontal,
      -cameraNormalForwardHorizontal,
      0);
  IEEE64 transformRowHomogeneousColumnVerticalScalar =
    calcMatrix4Element(
      0,
      0,
      1,
      0,
      cameraNormalRightVertical,
      cameraUpOrientationVertical,
      -cameraNormalForwardVertical,
      0);
  IEEE64 transformRowHomogeneousColumnDepthScalar =
    calcMatrix4Element(
      0,
      0,
      1,
      0,
      cameraNormalRightDepth,
      cameraUpOrientationDepth,
      -cameraNormalForwardDepth,
      0);
  IEEE64 transformRowHomogeneousColumnHomogeneousScalar =
    calcMatrix4Element(
      0,
      0,
      1,
      0,
      cameraRowHorizontalColumnHomogeneousScalar,
      cameraRowVerticalColumnHomogeneousScalar,
      cameraRowDepthColumnHomogeneousScalar,
      1);
  // IEEE64 cameraHomogeneousRowHorizontalColumnScalar =
  //   -calcVector3DotProduct(
  //     cameraNormalRightHorizontal,
  //     cameraNormalRightVertical,
  //     cameraNormalRightDepth,
  //     cameraPositionHorizontal,
  //     cameraPositionVertical,
  //     cameraPositionDepth);
  // IEEE64 cameraHomogeneousRowVerticalColumnScalar =
  //   -calcVector3DotProduct(
  //     cameraNormalAdjustedUpHorizontal,
  //     cameraNormalAdjustedUpVertical,
  //     cameraNormalAdjustedUpDepth,
  //     cameraPositionHorizontal,
  //     cameraPositionVertical,
  //     cameraPositionDepth);
  // IEEE64 cameraHomogeneousRowDepthColumnScalar =
  //   calcVector3DotProduct(
  //     -cameraNormalForwardHorizontal,
  //     -cameraNormalForwardVertical,
  //     -cameraNormalForwardDepth,
  //     cameraPositionHorizontal,
  //     cameraPositionVertical,
  //     cameraPositionDepth);
  // IEEE64 transformHorizontalHorizontalColumnScalar =
  //   calcMatrix4Element(
  //     perspectiveHorizontalRowHorizontalColumnScalar,
  //     0,
  //     0,
  //     0,
  //     cameraNormalRightHorizontal,
  //     cameraNormalRightVertical,
  //     cameraNormalRightDepth,
  //     cameraHomogeneousRowHorizontalColumnScalar);
  // IEEE64 transformHorizontalVerticalColumnScalar =
  //   calcMatrix4Element(
  //     perspectiveHorizontalRowHorizontalColumnScalar,
  //     0,
  //     0,
  //     0,
  //     cameraNormalAdjustedUpHorizontal,
  //     cameraNormalAdjustedUpVertical,
  //     cameraNormalAdjustedUpDepth,
  //     cameraHomogeneousRowVerticalColumnScalar);
  // IEEE64 transformHorizontalDepthColumnScalar =
  //   calcMatrix4Element(
  //     perspectiveHorizontalRowHorizontalColumnScalar,
  //     0,
  //     0,
  //     0,
  //     -cameraNormalForwardHorizontal,
  //     -cameraNormalForwardVertical,
  //     -cameraNormalForwardDepth,
  //     cameraHomogeneousRowDepthColumnScalar);
  // IEEE64 transformHorizontalHomogeneousColumnScalar =
  //   calcMatrix4Element(
  //     perspectiveHorizontalRowHorizontalColumnScalar,
  //     0,
  //     0,
  //     0,
  //     0,
  //     0,
  //     0,
  //     1);
  // IEEE64 transformVerticalHorizontalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     perspectiveVerticalRowVerticalColumnScalar,
  //     0,
  //     0,
  //     cameraNormalRightHorizontal,
  //     cameraNormalRightVertical,
  //     cameraNormalRightDepth,
  //     cameraHomogeneousRowHorizontalColumnScalar);
  // IEEE64 transformVerticalVerticalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     perspectiveVerticalRowVerticalColumnScalar,
  //     0,
  //     0,
  //     cameraNormalAdjustedUpHorizontal,
  //     cameraNormalAdjustedUpVertical,
  //     cameraNormalAdjustedUpDepth,
  //     cameraHomogeneousRowVerticalColumnScalar);
  // IEEE64 transformVerticalDepthColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     perspectiveVerticalRowVerticalColumnScalar,
  //     0,
  //     0,
  //     -cameraNormalForwardHorizontal,
  //     -cameraNormalForwardVertical,
  //     -cameraNormalForwardDepth,
  //     cameraHomogeneousRowDepthColumnScalar);
  // IEEE64 transformVerticalHomogeneousColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     perspectiveVerticalRowVerticalColumnScalar,
  //     0,
  //     0,
  //     0,
  //     0,
  //     0,
  //     1);
  // IEEE64 transformDepthHorizontalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     perspectiveDepthRowDepthColumnScalar,
  //     perspectiveDepthRowHomogeneousColumnScalar,
  //     cameraNormalRightHorizontal,
  //     cameraNormalRightVertical,
  //     cameraNormalRightDepth,
  //     cameraHomogeneousRowHorizontalColumnScalar);
  // IEEE64 transformDepthVerticalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     perspectiveDepthRowDepthColumnScalar,
  //     perspectiveDepthRowHomogeneousColumnScalar,
  //     cameraNormalAdjustedUpHorizontal,
  //     cameraNormalAdjustedUpVertical,
  //     cameraNormalAdjustedUpDepth,
  //     cameraHomogeneousRowVerticalColumnScalar);
  // IEEE64 transformDepthDepthColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     perspectiveDepthRowDepthColumnScalar,
  //     perspectiveDepthRowHomogeneousColumnScalar,
  //     -cameraNormalForwardHorizontal,
  //     -cameraNormalForwardVertical,
  //     -cameraNormalForwardDepth,
  //     cameraHomogeneousRowDepthColumnScalar);
  // IEEE64 transformDepthHomogeneousColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     perspectiveDepthRowDepthColumnScalar,
  //     perspectiveDepthRowHomogeneousColumnScalar,
  //     0,
  //     0,
  //     0,
  //     1);
  // IEEE64 transformHomogeneousHorizontalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     1,
  //     0,
  //     cameraNormalRightHorizontal,
  //     cameraNormalRightVertical,
  //     cameraNormalRightDepth,
  //     cameraHomogeneousRowHorizontalColumnScalar);
  // IEEE64 transformHomogeneousVerticalColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     1,
  //     0,
  //     cameraNormalAdjustedUpHorizontal,
  //     cameraNormalAdjustedUpVertical,
  //     cameraNormalAdjustedUpDepth,
  //     cameraHomogeneousRowVerticalColumnScalar);
  // IEEE64 transformHomogeneousDepthColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     1,
  //     0,
  //     -cameraNormalForwardHorizontal,
  //     -cameraNormalForwardVertical,
  //     -cameraNormalForwardDepth,
  //     cameraHomogeneousRowDepthColumnScalar);
  // IEEE64 transformHomogeneousHomogeneousColumnScalar =
  //   calcMatrix4Element(
  //     0,
  //     0,
  //     1,
  //     0,
  //     0,
  //     0,
  //     0,
  //     1);

  IEEE64 sphereHorizontalVerticalPolarAngleStep =
    (2 * M_PI) / sphereHorizontalVerticalPolarAngleCount;
  IEEE64 spherePolarOrthogonalDepthAngleStep =
    M_PI / spherePolarOrthogonalDepthAngleCount;
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
      IEEE64 spherePointHomogeneous = 1;
      IEEE64 transformPointHorizontal =
        calcVector4DotProduct(
          transformRowHorizontalColumnHorizontalScalar,
          transformRowHorizontalColumnVerticalScalar,
          transformRowHorizontalColumnDepthScalar,
          transformRowHorizontalColumnHomogeneousScalar,
          spherePointHorizontal,
          spherePointVertical,
          spherePointDepth,
          spherePointHomogeneous);
      // spherePointHorizontal * transformHorizontalHorizontalColumnScalar + spherePointVertical;
      IEEE64 transformPointVertical =
        calcVector4DotProduct(
          transformRowVerticalColumnHorizontalScalar,
          transformRowVerticalColumnVerticalScalar,
          transformRowVerticalColumnDepthScalar,
          transformRowVerticalColumnHomogeneousScalar,
          spherePointHorizontal,
          spherePointVertical,
          spherePointDepth,
          spherePointHomogeneous);
      // spherePointVertical * perspectiveVerticalRowVerticalColumnScalar;
      IEEE64 transformPointDepth =
        calcVector4DotProduct(
          transformRowDepthColumnHorizontalScalar,
          transformRowDepthColumnVerticalScalar,
          transformRowDepthColumnDepthScalar,
          transformRowDepthColumnHomogeneousScalar,
          spherePointHorizontal,
          spherePointVertical,
          spherePointDepth,
          spherePointHomogeneous);
      // spherePointDepth * perspectiveDepthRowDepthColumnScalar + 1 * perspectiveDepthRowHomogeneousColumnScalar;
      IEEE64 transformPointHomogeneous =
        calcVector4DotProduct(
          transformRowHomogeneousColumnHorizontalScalar,
          transformRowHomogeneousColumnVerticalScalar,
          transformRowHomogeneousColumnDepthScalar,
          transformRowHomogeneousColumnHomogeneousScalar,
          spherePointHorizontal,
          spherePointVertical,
          spherePointDepth,
          spherePointHomogeneous);
      // spherePointDepth;
      IEEE64 cartesianPointHorizontal =
        transformPointHorizontal / transformPointHomogeneous;
      IEEE64 cartesianPointVertical =
        transformPointVertical / transformPointHomogeneous;
      IEEE64 cartesianPointDepth =
        transformPointDepth / transformPointHomogeneous;
      IEEE64 cartesianCellMagnitude =
        sphereCellMagnitude / transformPointHomogeneous;
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
          currentPixelChannels_ptr->red = sphereCellColorRed;
          currentPixelChannels_ptr->green = sphereCellColorGreen;
          currentPixelChannels_ptr->blue = sphereCellColorBlue;
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
