#include "general.h"

#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

IEEE64 calcVector3Magnitude(IEEE64 vectorHorizontal, IEEE64 vectorVertical, IEEE64 vectorDepth);

IEEE64 calcVector3CrossProductHorizontal(IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth);

IEEE64 calcVector3CrossProductVertical(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorDepth, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorDepth);

IEEE64 calcVector3CrossProductDepth(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical);

IEEE64 calcVector3DotProduct(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth);

IEEE64 calcVector4DotProduct(IEEE64 lhsVectorHorizontal, IEEE64 lhsVectorVertical, IEEE64 lhsVectorDepth, IEEE64 lhsVectorHomogeneous, IEEE64 rhsVectorHorizontal, IEEE64 rhsVectorVertical, IEEE64 rhsVectorDepth, IEEE64 rhsVectorHomogeneous);

IEEE64 calcMatrix4Element(IEEE64 lhsRowHorizontalColumn, IEEE64 lhsRowVerticalColumn, IEEE64 lhsRowDepthColumn, IEEE64 lhsRowHomogeneousColumn, IEEE64 rhsColumnRowZero, IEEE64 rhsColumnRowOne, IEEE64 rhsColumnRowTwo, IEEE64 rhsColumnRowThree);

#endif
