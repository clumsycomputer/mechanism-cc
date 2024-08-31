#include "general.h"
#include "ImagePixels.h"

#ifndef IMAGE_PNG_H
#define IMAGE_PNG_H

typedef HeapAllocation __ImagePng;
typedef __ImagePng Rgb8bitImagePng;
// typedef __ImagePng Rgb16bitImagePng;

#define pngPixelsDataByteCount__CONSTANT_FIELD_SIZE sizeof(U64)
#define pngKind__CONFIG_FIELD_SIZE sizeof(U8)

#define PNG_HEADER_SIZE (pngPixelsDataByteCount__CONSTANT_FIELD_SIZE + pngKind__CONFIG_FIELD_SIZE)
#define PNG_DATA_PADDING_SIZE (ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE - (PNG_HEADER_SIZE % ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE))
#define PNG_HEADER_SIZE_PLUS_PNG_DATA_PADDING_SIZE (PNG_HEADER_SIZE + PNG_DATA_PADDING_SIZE)

#define PNG_DATA_SIGNATURE_SIZE 8
#define PNG_DATA_IHDR_CHUNK_LENGTH_SIZE 4
#define PNG_DATA_IHDR_CHUNK_TYPE_SIZE 4
#define PNG_DATA_IHDR_PIXEL_WIDTH_SIZE 4
#define PNG_DATA_IHDR_PIXEL_HEIGHT_SIZE 4
#define PNG_DATA_IHDR_CHANNEL_BIT_DEPTH_SIZE 1
#define PNG_DATA_IHDR_CHANNEL_TYPE_SIZE 1
#define PNG_DATA_IHDR_COMPRESSION_METHOD_SIZE 1
#define PNG_DATA_IHDR_FILTER_METHOD_SIZE 1
#define PNG_DATA_IHDR_INTERLACE_METHOD_SIZE 1
#define PNG_DATA_IHDR_CRC_SIZE 4
#define PNG_DATA_IHDR_CHUNK_SIZE (PNG_DATA_IHDR_CHUNK_LENGTH_SIZE + PNG_DATA_IHDR_CHUNK_TYPE_SIZE + PNG_DATA_IHDR_PIXEL_WIDTH_SIZE + PNG_DATA_IHDR_PIXEL_HEIGHT_SIZE + PNG_DATA_IHDR_CHANNEL_BIT_DEPTH_SIZE + PNG_DATA_IHDR_CHANNEL_TYPE_SIZE + PNG_DATA_IHDR_COMPRESSION_METHOD_SIZE + PNG_DATA_IHDR_FILTER_METHOD_SIZE + PNG_DATA_IHDR_INTERLACE_METHOD_SIZE + PNG_DATA_IHDR_CRC_SIZE)
#define PNG_DATA_IDAT_CHUNK_LENGTH_SIZE 4
#define PNG_DATA_IDAT_CHUNK_TYPE_SIZE 4
#define PNG_DATA_IDAT_CRC_SIZE 4
#define PNG_DATA_IDAT_CHUNK_METADATA_SIZE (PNG_DATA_IDAT_CHUNK_LENGTH_SIZE + PNG_DATA_IDAT_CHUNK_TYPE_SIZE + PNG_DATA_IDAT_CRC_SIZE)
#define PNG_DATA_IEND_CHUNK_LENGTH_SIZE 4
#define PNG_DATA_IEND_CHUNK_TYPE_SIZE 4
#define PNG_DATA_IEND_CRC_SIZE 4
#define PNG_DATA_IEND_CHUNK_SIZE (PNG_DATA_IEND_CHUNK_LENGTH_SIZE + PNG_DATA_IEND_CHUNK_TYPE_SIZE + PNG_DATA_IEND_CRC_SIZE)
#define PNG_DATA_METADATA_SIZE (PNG_DATA_SIGNATURE_SIZE + PNG_DATA_IHDR_CHUNK_SIZE + PNG_DATA_IDAT_CHUNK_METADATA_SIZE + PNG_DATA_IEND_CHUNK_SIZE)

#define pngKind__PTR_OFFSET (PNG_DATA_PADDING_SIZE + pngKind__CONFIG_FIELD_SIZE)
#define pngPixelsDataByteCount__PTR_OFFSET (pngKind__PTR_OFFSET + pngPixelsDataByteCount__CONSTANT_FIELD_SIZE)
#define pngCompressedPixelsByteCount__PTR_OFFSET (pngPixelsDataByteCount__PTR_OFFSET)

#define pngDataSignature__PTR_OFFSET 0
#define pngDataIhdrChunkLength__PTR_OFFSET (pngDataSignature__PTR_OFFSET + PNG_DATA_SIGNATURE_SIZE)
#define pngDataIhdrChunkType__PTR_OFFSET (pngDataIhdrChunkLength__PTR_OFFSET + PNG_DATA_IHDR_CHUNK_LENGTH_SIZE)
#define pngDataIhdrPixelWidth__PTR_OFFSET (pngDataIhdrChunkType__PTR_OFFSET + PNG_DATA_IHDR_CHUNK_TYPE_SIZE)
#define pngDataIhdrPixelHeight__PTR_OFFSET (pngDataIhdrPixelWidth__PTR_OFFSET + PNG_DATA_IHDR_PIXEL_WIDTH_SIZE)
#define pngDataIhdrChannelBitDepth__PTR_OFFSET (pngDataIhdrPixelHeight__PTR_OFFSET + PNG_DATA_IHDR_PIXEL_HEIGHT_SIZE)
#define pngDataIhdrChannelType__PTR_OFFSET (pngDataIhdrChannelBitDepth__PTR_OFFSET + PNG_DATA_IHDR_CHANNEL_BIT_DEPTH_SIZE)
#define pngDataIhdrCompressionMethod__PTR_OFFSET (pngDataIhdrChannelType__PTR_OFFSET + PNG_DATA_IHDR_CHANNEL_TYPE_SIZE)
#define pngDataIhdrFilterMethod__PTR_OFFSET (pngDataIhdrCompressionMethod__PTR_OFFSET + PNG_DATA_IHDR_COMPRESSION_METHOD_SIZE)
#define pngDataIhdrInterlaceMethod__PTR_OFFSET (pngDataIhdrFilterMethod__PTR_OFFSET + PNG_DATA_IHDR_FILTER_METHOD_SIZE)
#define pngDataIhdrCrc__PTR_OFFSET (pngDataIhdrInterlaceMethod__PTR_OFFSET + PNG_DATA_IHDR_INTERLACE_METHOD_SIZE)
#define pngDataIdatChunkLength__PTR_OFFSET (pngDataIhdrCrc__PTR_OFFSET + PNG_DATA_IHDR_CRC_SIZE)
#define pngDataIdatChunkType__PTR_OFFSET (pngDataIdatChunkLength__PTR_OFFSET + PNG_DATA_IDAT_CHUNK_LENGTH_SIZE)
#define pngDataIdatCompressedPixels__PTR_OFFSET (pngDataIdatChunkType__PTR_OFFSET + PNG_DATA_IDAT_CHUNK_TYPE_SIZE)

typedef enum
{
  __PngKind_Rgb8bit = 0,
  // __PngKind_Rgb16bit = 1
} __PngKindOptions;

U64 calcPngMaxCompressedPixelsByteCount(U64 pngPixelsDataByteCount);
U64 calcPngDataMaxByteCount(U64 pngPixelsDataByteCount);
U64 calcPngMaxByteCount(U64 pngPixelsDataByteCount);

void __initPngConfig(U8 pngKind__, __ImagePng uninitializedPng);
void __initPngConstants(U64 pngPixelsDataByteCount, __ImagePng uninitializedPng);

void __applyPngDataSignature(__ImagePng uninitializedPng);
void __applyPngDataIhdrChunk(U32 pngPixelWidth, U32 pngPixelHeight, U8 pngChannelBitDepth, __ImagePng uninitializedPng);
void __applyPngDataIdatChunk(__ImagePixels imagePixels, __ImagePng imagePng);
void __applyPngDataIendChunk(__ImagePng imagePng);

void updatePngDataPixels(__ImagePixels imagePixels, __ImagePng imagePng);

U8 getPngKind(__ImagePng imagePng);
U64 getPngPixelsDataByteCount(__ImagePng imagePng);
U64 getPngMaxCompressedPixelsByteCount(__ImagePng imagePng);
U64 getPngMaxDataByteCount(__ImagePng imagePng);
U64 getPngMaxByteCount(__ImagePng imagePng);
U32 getPngDataCompressedPixelsByteCount(__ImagePng imagePng);
U64 getPngDataByteCount(__ImagePng imagePng);
U64 getPngByteCount(__ImagePng imagePng);

#endif
