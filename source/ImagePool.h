#include "ImagePixels.h"
#include "ImagePng.h"
#include "general.h"

#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

typedef HeapAllocation ImagePool;

typedef struct
{
  ImagePool __pool;
  __ImagePixels poolPixels;
  __ImagePng poolPng;
} ImagePoolView;

ImagePoolView createRgb8bitImagePool(U16 pixelsWidth, U16 pixelsHeight);
// ImagePoolView createRgb16bitImagePool(U16 pixelsWidth, U16 pixelsHeight);

void freeImagePool(ImagePoolView imagePoolView);

#endif
