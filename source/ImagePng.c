#include "ImagePng.h"
#include <zlib.h>

U64 calcPngMaxCompressedPixelsByteCount(
  U64 pixelsDataByteCount)
{
  return compressBound(pixelsDataByteCount);
}

U64 calcPngMaxDataByteCount(
  U64 pixelsDataByteCount)
{
  return PNG_DATA_METADATA_SIZE + calcPngMaxCompressedPixelsByteCount(pixelsDataByteCount);
}

U64 calcPngMaxByteCount(
  U64 pixelsDataByteCount)
{
  return PNG_HEADER_SIZE_PLUS_PNG_DATA_PADDING_SIZE + calcPngMaxDataByteCount(pixelsDataByteCount);
}

U8* atPngKind(__ImagePng imagePng)
{
  return imagePng - pngKind__PTR_OFFSET;
}

U64* atPngPixelsDataByteCount(__ImagePng imagePng)
{
  return (U64*)(imagePng - pngPixelsDataByteCount__PTR_OFFSET);
}

U64* atPngDataSignature(__ImagePng imagePng)
{
  return (U64*)(imagePng + pngDataSignature__PTR_OFFSET);
}

U32* atPngDataIhdrChunkLength(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIhdrChunkLength__PTR_OFFSET);
}

U32* atPngDataIhdrChunkType(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIhdrChunkType__PTR_OFFSET);
}

U32* atPngDataIhdrPixelWidth(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIhdrPixelWidth__PTR_OFFSET);
}

U32* atPngDataIhdrPixelHeight(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIhdrPixelHeight__PTR_OFFSET);
}

U8* atPngDataIhdrChannelBitDepth(__ImagePng imagePng)
{
  return imagePng + pngDataIhdrChannelBitDepth__PTR_OFFSET;
}

U8* atPngDataIhdrChannelType(__ImagePng imagePng)
{
  return imagePng + pngDataIhdrChannelType__PTR_OFFSET;
}

U8* atPngDataIhdrCompressionMethod(__ImagePng imagePng)
{
  return imagePng + pngDataIhdrCompressionMethod__PTR_OFFSET;
}

U8* atPngDataIhdrFilterMethod(__ImagePng imagePng)
{
  return imagePng + pngDataIhdrFilterMethod__PTR_OFFSET;
}

U8* atPngDataIhdrInterlaceMethod(__ImagePng imagePng)
{
  return imagePng + pngDataIhdrInterlaceMethod__PTR_OFFSET;
}

U32* atPngDataIhdrCrc(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIhdrCrc__PTR_OFFSET);
}

U32* atPngDataIdatChunkLength(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIdatChunkLength__PTR_OFFSET);
}

U32* atPngDataIdatChunkType(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIdatChunkType__PTR_OFFSET);
}

U32* atPngDataIdatCompressedPixels(__ImagePng imagePng)
{
  return (U32*)(imagePng + pngDataIdatCompressedPixels__PTR_OFFSET);
}

U32* atPngDataIdatCrc(__ImagePng imagePng)
{
  return (U32*)((U8*)atPngDataIdatCompressedPixels(imagePng) + getPngDataCompressedPixelsByteCount(imagePng));
}

U32* atPngDataIendChunkLength(__ImagePng imagePng)
{
  return (U32*)((U8*)atPngDataIdatCrc(imagePng) + PNG_DATA_IDAT_CRC_SIZE);
}

U32* atPngDataIendChunkType(__ImagePng imagePng)
{
  return (U32*)((U8*)atPngDataIendChunkLength(imagePng) + PNG_DATA_IDAT_CHUNK_LENGTH_SIZE);
}

U32* atPngDataIendCrc(__ImagePng imagePng)
{
  return (U32*)((U8*)atPngDataIendChunkType(imagePng) + PNG_DATA_IDAT_CHUNK_TYPE_SIZE);
}

U8 getPngKind(__ImagePng imagePng)
{
  return *atPngKind(imagePng);
}

U64 getPngPixelsDataByteCount(__ImagePng imagePng)
{
  return *atPngPixelsDataByteCount(imagePng);
}

U64 getPngMaxCompressedPixelsByteCount(__ImagePng imagePng)
{
  return calcPngMaxCompressedPixelsByteCount(
    getPngPixelsDataByteCount(imagePng));
}

U64 getPngMaxDataByteCount(__ImagePng imagePng)
{
  return calcPngMaxDataByteCount(
    getPngPixelsDataByteCount(imagePng));
}

U64 getPngMaxByteCount(__ImagePng imagePng)
{
  return calcPngMaxByteCount(
    getPngPixelsDataByteCount(imagePng));
}

U32 getPngDataCompressedPixelsByteCount(__ImagePng imagePng)
{
  return swapEndianU32(*atPngDataIdatChunkLength(imagePng));
}

U64 getPngDataByteCount(__ImagePng imagePng)
{
  return PNG_DATA_METADATA_SIZE + getPngDataCompressedPixelsByteCount(imagePng);
}

U64 getPngByteCount(__ImagePng imagePng)
{
  return PNG_HEADER_SIZE_PLUS_PNG_DATA_PADDING_SIZE + getPngDataByteCount(imagePng);
}

void __initPngConfig(U8 pngKind__, __ImagePng uninitializedPng)
{
  *atPngKind(uninitializedPng) = pngKind__;
}

void __initPngConstants(U64 pngPixelsDataByteCount, __ImagePng uninitializedPng)
{
  *atPngPixelsDataByteCount(uninitializedPng) = pngPixelsDataByteCount;
}

void __applyPngDataSignature(__ImagePng uninitializedPng)
{
  U64 pngDataSignatureBytes = 0x0A1A0A0D474E5089; // png signature in hexadecimal for little-endian architecture
  *atPngDataSignature(uninitializedPng) = pngDataSignatureBytes;
}

void __applyPngDataIhdrChunk(U32 pngPixelWidth, U32 pngPixelHeight, U8 pngChannelBitDepth, __ImagePng uninitializedPng)
{
  U32 pngDataIhdrChunkLengthBytes = 0x0D000000; // 13 formatted in hexadecimal for little-endian architecture
  U32 pngDataIhdrChunkTypeBytes = 0x52444849;   // 'IHDR' ASCII formatted in hexadecimal for little-endian architecture
  *atPngDataIhdrChunkLength(uninitializedPng) = pngDataIhdrChunkLengthBytes;
  *atPngDataIhdrChunkType(uninitializedPng) = pngDataIhdrChunkTypeBytes;
  *atPngDataIhdrPixelWidth(uninitializedPng) = swapEndianU32(pngPixelWidth);
  *atPngDataIhdrPixelHeight(uninitializedPng) = swapEndianU32(pngPixelHeight);
  *atPngDataIhdrChannelBitDepth(uninitializedPng) = pngChannelBitDepth;
  *atPngDataIhdrChannelType(uninitializedPng) = 0x02;       // truecolor
  *atPngDataIhdrCompressionMethod(uninitializedPng) = 0x00; // deflate zlib compression
  *atPngDataIhdrFilterMethod(uninitializedPng) = 0x00;      // none
  *atPngDataIhdrInterlaceMethod(uninitializedPng) = 0x00;   // none
  *atPngDataIhdrCrc(uninitializedPng) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atPngDataIhdrChunkType(uninitializedPng),
        PNG_DATA_IHDR_CHUNK_TYPE_SIZE + PNG_DATA_IHDR_PIXEL_WIDTH_SIZE + PNG_DATA_IHDR_PIXEL_HEIGHT_SIZE + PNG_DATA_IHDR_CHANNEL_BIT_DEPTH_SIZE + PNG_DATA_IHDR_CHANNEL_TYPE_SIZE + PNG_DATA_IHDR_COMPRESSION_METHOD_SIZE + PNG_DATA_IHDR_FILTER_METHOD_SIZE + PNG_DATA_IHDR_INTERLACE_METHOD_SIZE));
}

void __applyPngDataIdatChunk(__ImagePixels imagePixels, __ImagePng imagePng)
{
  z_stream pixelStream;
  pixelStream.zalloc =
    Z_NULL;
  pixelStream.zfree =
    Z_NULL;
  pixelStream.opaque =
    Z_NULL;
  pixelStream.avail_in =
    (uInt)getPixelsDataByteCount(imagePixels);
  pixelStream.next_in =
    (Bytef*)imagePixels;
  pixelStream.avail_out =
    (uInt)getPngMaxCompressedPixelsByteCount(imagePng);
  pixelStream.next_out =
    (Bytef*)atPngDataIdatCompressedPixels(imagePng);
  deflateInit(
    &pixelStream,
    Z_DEFAULT_COMPRESSION);
  deflate(
    &pixelStream,
    Z_FINISH);
  deflateEnd(
    &pixelStream);
  *atPngDataIdatChunkLength(imagePng) =
    swapEndianU32(
      (U32)pixelStream.total_out);
  *atPngDataIdatChunkType(imagePng) =
    0x54414449;
  *atPngDataIdatCrc(imagePng) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atPngDataIhdrChunkType(imagePng),
        PNG_DATA_IDAT_CHUNK_TYPE_SIZE + getPngDataCompressedPixelsByteCount(imagePng)));
}

void __applyPngDataIendChunk(__ImagePng imagePng)
{
  *atPngDataIendChunkLength(imagePng) = 0x00000000;
  *atPngDataIendChunkType(imagePng) = 0x444E4549;
  *atPngDataIendCrc(imagePng) = 0x82426082;
}

void updatePngDataPixels(__ImagePixels imagePixels, __ImagePng imagePng)
{
  __applyPngDataIdatChunk(imagePixels, imagePng);
  __applyPngDataIendChunk(imagePng);
}
