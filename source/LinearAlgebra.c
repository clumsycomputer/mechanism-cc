#include "LinearAlgebra.h"
#include "general.h"
#include <math.h>

IEEE64 calcVector3Magnitude(IEEE64 vectorHorizontal, IEEE64 vectorVertical, IEEE64 vectorDepth)
{
  return sqrt(vectorHorizontal * vectorHorizontal + vectorVertical * vectorVertical + vectorDepth * vectorDepth);
}

IEEE64 calcVector3CrossProductHorizontal(IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth)
{
  return lhsVectorVertical * rhsVectorDepth - lhsVectorDepth * rhsVectorVertical;
}

IEEE64 calcVector3CrossProductVertical(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorDepth, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorDepth)
{
  return lhsVectorHorizontal * rhsVectorDepth - lhsVectorDepth * rhsVectorHorizontal;
}

IEEE64 calcVector3CrossProductDepth(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical)
{
  return lhsVectorHorizontal * rhsVectorVertical - lhsVectorVertical * rhsVectorHorizontal;
}

IEEE64 calcVector3DotProduct(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth)
{
  return lhsVectorHorizontal * rhsVectorHorizontal + lhsVectorVertical * rhsVectorVertical + lhsVectorDepth * rhsVectorDepth;
}

IEEE64 calcVector4DotProduct(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 lhsVectorHomogeneous, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth, IEEE64 rhsVectorHomogeneous)
{
  return lhsVectorHorizontal * rhsVectorHorizontal + lhsVectorVertical * rhsVectorVertical + lhsVectorDepth * rhsVectorDepth + lhsVectorHomogeneous * rhsVectorHomogeneous;
}

IEEE64 calcMatrix4Element(IEEE64 lhsRowHorizontalColumn, IEEE64 lhsRowVerticalColumn, IEEE64 lhsRowDepthColumn, IEEE64 lhsRowHomogeneousColumn, IEEE64 rhsColumnRowZero, IEEE64 rhsColumnRowOne, IEEE64 rhsColumnRowTwo, IEEE64 rhsColumnRowThree)
{
  return lhsRowHorizontalColumn * rhsColumnRowZero + lhsRowVerticalColumn * rhsColumnRowOne + lhsRowDepthColumn * rhsColumnRowTwo + lhsRowHomogeneousColumn * rhsColumnRowThree;
}
