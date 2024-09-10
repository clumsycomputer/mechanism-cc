#include "PngPixels.h"
#include "PngEncoding.h"

U64 calcPixelsDataRowSize(U32 pixelsWidth)
{
  return ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_SIZE + pixelsWidth * __Rgb8bitPixelChannels_PNG_PIXELS_SIZE;
}

U64 calcPixelsDataSize(U32 pixelsWidth, U32 pixelsHeight)
{
  U64 pixelsDataRowSize =
    calcPixelsDataRowSize(pixelsWidth);
  return pixelsHeight * pixelsDataRowSize;
}

U64 sizeofRgb8bitPngPixels(U32 pixelsWidth, U32 pixelsHeight)
{
  return sizeof(Rgb8bitPngPixels) + calcPixelsDataSize(pixelsWidth, pixelsHeight); // + padding
}

void initRgb8bitPngPixels(Rgb8bitPngPixels* pngPixels, U32 pixelsWidth, U32 pixelsHeight)
{
  pngPixels->channelCount = __PixelsChannelCountOption_Rgb;
  pngPixels->channelBitDepth = __PixelsChannelBitDepthOption_8bit;
  pngPixels->width =
    pixelsWidth;
  pngPixels->height =
    pixelsHeight;
  pngPixels->data_ptr =
    (U8*)pngPixels + sizeof(Rgb8bitPngPixels);
  pngPixels->__cache.dataRowSize =
    calcPixelsDataRowSize(pixelsWidth);
  U8* pixelsData =
    pngPixels->data_ptr;
  for (U32 pixelsRowIndex = 0; pixelsRowIndex < pixelsHeight; pixelsRowIndex++)
  {
    U64 pixelsDataPngEncodingRowFilterMethodOffset =
      pixelsRowIndex * pngPixels->__cache.dataRowSize;
    *(pixelsData + pixelsDataPngEncodingRowFilterMethodOffset) =
      ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE;
  }
}

Rgb8bitPixelChannels* atPixelsDataPixelChannels(Rgb8bitPngPixels* pngPixels, U32 pixelRowIndex, U32 pixelColumnIndex)
{
  U64 pixelsPixelChannelsOffset =
    pixelRowIndex * pngPixels->__cache.dataRowSize + ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_SIZE + pixelColumnIndex * __Rgb8bitPixelChannels_PNG_PIXELS_SIZE;
  return (Rgb8bitPixelChannels*)(pngPixels->data_ptr + pixelsPixelChannelsOffset);
}
