#include "ImagePixels.h"
#include "general.h"

U64 calcPixelsChannelByteDepth(U8 pixelsChannelBitDepth__)
{
  return pixelsChannelBitDepth__ / BITS_PER_BYTE;
}

U64 calcPixelsPixelByteCount(
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__)
{
  return pixelsChannelCount__ * calcPixelsChannelByteDepth(pixelsChannelBitDepth__);
}

U64 calcPixelsDataByteCount(
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__,
  U16 pixelsWidth,
  U16 pixelsHeight)
{
  return (calcPixelsPixelByteCount(pixelsChannelCount__, pixelsChannelBitDepth__) * pixelsWidth + 1) * pixelsHeight;
}

U64 calcPixelsByteCount(
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__,
  U16 pixelsWidth,
  U16 pixelsHeight)
{
  return PIXELS_HEADER_SIZE_PLUS_PIXELS_DATA_PADDING_SIZE + calcPixelsDataByteCount(pixelsChannelCount__, pixelsChannelBitDepth__, pixelsWidth, pixelsHeight);
}

U8* atPixelsKind(__ImagePixels imagePixels)
{
  return imagePixels - pixelsKind__PTR_OFFSET;
}

U8* atPixelsChannelCount(__ImagePixels imagePixels)
{
  return imagePixels - pixelsChannelCount__PTR_OFFSET;
}

U8* atPixelsChannelBitDepth(__ImagePixels imagePixels)
{
  return imagePixels - pixelsChannelBitDepth__PTR_OFFSET;
}

U16* atPixelsWidth(__ImagePixels imagePixels)
{
  return (U16*)(imagePixels - pixelsWidth__PTR_OFFSET);
}

U16* atPixelsHeight(__ImagePixels imagePixels)
{
  return (U16*)(imagePixels - pixelsHeight__PTR_OFFSET);
}

void __initPixelsConfig(
  U8 pixelsKind__,
  U8 pixelsChannelCount__,
  U8 pixelsChannelBitDepth__,
  __ImagePixels uninitializedPixels)
{
  *atPixelsKind(uninitializedPixels) = pixelsKind__;
  *atPixelsChannelCount(uninitializedPixels) = pixelsChannelCount__;
  *atPixelsChannelBitDepth(uninitializedPixels) = pixelsChannelBitDepth__;
}

void __initPixelsConstants(
  U16 pixelsWidth,
  U16 pixelsHeight,
  __ImagePixels uninitializedPixels)
{
  *atPixelsWidth(uninitializedPixels) = pixelsWidth;
  *atPixelsHeight(uninitializedPixels) = pixelsHeight;
}

U8 getPixelsKind(__ImagePixels imagePixels)
{
  return *atPixelsKind(imagePixels);
}

U8 getPixelsChannelCount(__ImagePixels imagePixels)
{
  return *atPixelsChannelCount(imagePixels);
}

U8 getPixelsChannelBitDepth(__ImagePixels imagePixels)
{
  return *atPixelsChannelBitDepth(imagePixels);
}

U8 getPixelsChannelByteDepth(__ImagePixels imagePixels)
{
  return calcPixelsChannelByteDepth(
    getPixelsChannelBitDepth(imagePixels));
}

U8 getPixelsPixelByteCount(__ImagePixels imagePixels)
{
  return calcPixelsPixelByteCount(
    getPixelsChannelCount(imagePixels),
    getPixelsChannelBitDepth(imagePixels));
}

U16 getPixelsWidth(__ImagePixels imagePixels)
{
  return *atPixelsWidth(imagePixels);
}

U16 getPixelsHeight(__ImagePixels imagePixels)
{
  return *atPixelsHeight(imagePixels);
}

U64 getPixelsDataByteCount(__ImagePixels imagePixels)
{
  return calcPixelsDataByteCount(
    getPixelsChannelCount(imagePixels),
    getPixelsChannelBitDepth(imagePixels),
    getPixelsWidth(imagePixels),
    getPixelsHeight(imagePixels));
}

U64 getPixelsByteCount(__ImagePixels imagePixels)
{
  return calcPixelsByteCount(
    getPixelsChannelCount(imagePixels),
    getPixelsChannelBitDepth(imagePixels),
    getPixelsWidth(imagePixels),
    getPixelsHeight(imagePixels));
}

// void __writeImagePixels(
//   U64 pngColorType__,
//   __ImagePixels imagePixels,
//   FILE* outputFilePtr)
// {
//   U16 pixelsHeight = getPixelsHeight(imagePixels);
//   U16 pixelsWidth = getPixelsWidth(imagePixels);
//   U8 pixelsPixelByteCount = getPixelsPixelByteCount(imagePixels);
//   png_structp pngWriteStruct =
//     png_create_write_struct(
//       PNG_LIBPNG_VER_STRING,
//       NULL,
//       NULL,
//       NULL);
//   png_infop pngInfoPtr = png_create_info_struct(pngWriteStruct);
//   png_init_io(
//     pngWriteStruct,
//     outputFilePtr);
//   png_set_IHDR(
//     pngWriteStruct,
//     pngInfoPtr,
//     (png_uint_32)getPixelsWidth(imagePixels),
//     (png_uint_32)getPixelsHeight(imagePixels),
//     (int)getPixelsChannelBitDepth(imagePixels),
//     (int)pngColorType__,
//     PNG_INTERLACE_NONE,
//     PNG_COMPRESSION_TYPE_DEFAULT,
//     PNG_FILTER_TYPE_DEFAULT);
//   png_write_info(
//     pngWriteStruct,
//     pngInfoPtr);
//   for (int rowIndex = 0; rowIndex < pixelsHeight; rowIndex++)
//   {
//     int pixelsRowPtrOffset = rowIndex * pixelsWidth * pixelsPixelByteCount;
//     png_write_row(
//       pngWriteStruct,
//       imagePixels + pixelsRowPtrOffset);
//   }
//   png_write_end(
//     pngWriteStruct,
//     pngInfoPtr);
//   png_destroy_write_struct(
//     &pngWriteStruct,
//     &pngInfoPtr);
// }

// void writeRgbImagePixels(
//   __ImagePixels imagePixels,
//   FILE* outputFilePtr)
// {
//   __writeImagePixels(
//     PNG_COLOR_TYPE_RGB,
//     imagePixels,
//     outputFilePtr);
// }
