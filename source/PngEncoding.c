#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"
#include <zlib.h>

U64 calcMaxIdatCompressedPixelsSize(U32 pixelsWidth, U32 pixelsHeight)
{
  return compressBound(
    calcPixelsDataSize(pixelsWidth, pixelsHeight));
}

U64 maxsizeofRgb8bitPngEncoding(U32 pixelsWidth, U32 pixelsHeight)
{
  U64 maxIdatCompressedPixelsSize =
    calcMaxIdatCompressedPixelsSize(pixelsWidth, pixelsHeight);
  return Rgb8bitPngEncoding__SIZE(maxIdatCompressedPixelsSize);
}

PngSignature* atPngSignature(U8* pngEncoding)
{
  return (PngSignature*)(pngEncoding + pngSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataSize* atIhdrDataSize(U8* pngEncoding)
{
  return (IhdrDataSize*)(pngEncoding + ihdrDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrSignature* atIhdrSignature(U8* pngEncoding)
{
  return (IhdrSignature*)(pngEncoding + ihdrSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngPixelWidth* atIhdrDataPngPixelWidth(U8* pngEncoding)
{
  return (IhdrDataPngPixelWidth*)(pngEncoding + ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngPixelHeight* atIhdrDataPngPixelHeight(U8* pngEncoding)
{
  return (IhdrDataPngPixelHeight*)(pngEncoding + ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngChannelBitDepth* atIhdrDataPngChannelBitDepth(U8* pngEncoding)
{
  return (IhdrDataPngChannelBitDepth*)(pngEncoding + ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngChannelKind* atIhdrDataPngChannelKind(U8* pngEncoding)
{
  return (IhdrDataPngChannelKind*)(pngEncoding + ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngCompressionMethod* atIhdrDataPngCompressionMethod(U8* pngEncoding)
{
  return (IhdrDataPngCompressionMethod*)(pngEncoding + ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngFilterMethod* atIhdrDataPngFilterMethod(U8* pngEncoding)
{
  return (IhdrDataPngFilterMethod*)(pngEncoding + ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngInterlaceMethod* atIhdrDataPngInterlaceMethod(U8* pngEncoding)
{
  return (IhdrDataPngInterlaceMethod*)(pngEncoding + ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrSignatureDataCrc* atIhdrSignatureDataCrc(U8* pngEncoding)
{
  return (IhdrSignatureDataCrc*)(pngEncoding + ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatCompressedPixelsSize* atIdatCompressedPixelsSize(U8* pngEncoding)
{
  return (IdatCompressedPixelsSize*)(pngEncoding + idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatSignature* atIdatSignature(U8* pngEncoding)
{
  return (IdatSignature*)(pngEncoding + idatSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatCompressedPixels atIdatCompressedPixels(U8* pngEncoding)
{
  return (IdatCompressedPixels)(pngEncoding + idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatSignatureCompressedPixelsCrc* atIdatSignatureCompressedPixelsCrc(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IdatSignatureCompressedPixelsCrc*)(pngEncoding + idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendDataSize* atIendDataSize(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendDataSize*)(pngEncoding + iendDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendSignature* atIendSignature(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendSignature*)(pngEncoding + iendSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendSignature* atIendSignatureCrc(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendSignatureCrc*)(pngEncoding + iendSignatureCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

void initRgb8bitPngEncoding(U8* pngEncoding, Rgb8bitPngPixels* pngPixels)
{
  *atPngSignature(pngEncoding) = 0x0A1A0A0D474E5089;                                                    // 8-byte little-endian architecture
  *atIhdrDataSize(pngEncoding) = 0x0D000000;                                                            // 4-byte little-endian architecture (13, signature + data)
  *atIhdrSignature(pngEncoding) = 0x52444849;                                                           // 4-byte little-endian architecture ('IHDR', ASCII)
  *atIhdrDataPngChannelBitDepth(pngEncoding) = 0x08;                                                    // 1-byte (8)
  *atIhdrDataPngChannelKind(pngEncoding) = 0x02;                                                        // 1-byte (truecolor, rgb)
  *atIhdrDataPngCompressionMethod(pngEncoding) = 0x00;                                                  // 1-byte (zlib deflate)
  *atIhdrDataPngFilterMethod(pngEncoding) = ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_DEFAULT; // 1-byte (none)
  *atIhdrDataPngInterlaceMethod(pngEncoding) = 0x00;                                                    // 1-byte (none)
  *atIdatSignature(pngEncoding) = 0x54414449;                                                           // 4-byte little-endian architecture ('IDAT', ASCII)
  *atIhdrDataPngPixelWidth(pngEncoding) =
    swapEndianU32(pngPixels->width);
  *atIhdrDataPngPixelHeight(pngEncoding) =
    swapEndianU32(pngPixels->height);
  *atIhdrSignatureDataCrc(pngEncoding) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atIhdrSignature(pngEncoding),
        IHDR_CHUNK_SIZE));
}

void encodeRgb8bitPngPixels(U8* pngEncoding, Rgb8bitPngPixels* pngPixels)
{
  z_stream pixelStream;
  pixelStream.zalloc = Z_NULL;
  pixelStream.zfree = Z_NULL;
  pixelStream.opaque = Z_NULL;
  pixelStream.avail_in =
    (uInt)calcPixelsDataSize(
      pngPixels->width,
      pngPixels->height);
  pixelStream.next_in =
    (Bytef*)pngPixels->data_ptr;
  pixelStream.avail_out =
    calcMaxIdatCompressedPixelsSize(
      pngPixels->width,
      pngPixels->height);
  pixelStream.next_out =
    (Bytef*)atIdatCompressedPixels(pngEncoding);
  deflateInit(
    &pixelStream,
    Z_DEFAULT_COMPRESSION);
  deflate(
    &pixelStream,
    Z_FINISH);
  deflateEnd(
    &pixelStream);
  IdatCompressedPixelsSize idatCompressedPixelsSize =
    (U32)pixelStream.total_out;
  *atIdatCompressedPixelsSize(pngEncoding) =
    swapEndianU32(idatCompressedPixelsSize);
  *atIdatSignatureCompressedPixelsCrc(pngEncoding, idatCompressedPixelsSize) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atIdatSignature(pngEncoding),
        idatSignature__Rgb8bitPngEncoding__VALUE_SIZE + idatCompressedPixelsSize));
  *atIendDataSize(pngEncoding, idatCompressedPixelsSize) =
    0x00000000;
  *atIendSignature(pngEncoding, idatCompressedPixelsSize) =
    0x444E4549;
  *atIendSignatureCrc(pngEncoding, idatCompressedPixelsSize) =
    0x82426082;
}
