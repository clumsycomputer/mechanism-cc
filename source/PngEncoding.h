#include "PngPixels.h"
#include "general.h"

#ifndef PNG_ENCODING_H
#define PNG_ENCODING_H

typedef U64 PngSignature;
#define pngSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define pngSignature__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define pngSignature__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define pngSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET 0
#define pngSignature__Rgb8bitPngEncoding__VALUE_SIZE sizeof(PngSignature)
typedef U32 IhdrDataSize;
#define ihdrDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataSize__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataSize__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define ihdrDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (pngSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + pngSignature__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataSize__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataSize)
typedef U32 IhdrSignature;
#define ihdrSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrSignature__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrSignature__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define ihdrSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataSize__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrSignature__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrSignature)
typedef U32 IhdrDataPngPixelWidth;
#define ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrSignature__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngPixelWidth)
typedef U32 IhdrDataPngPixelHeight;
#define ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngPixelHeight)
typedef U8 IhdrDataPngChannelBitDepth;
#define ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngChannelBitDepth)
typedef U8 IhdrDataPngChannelKind;
#define ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngChannelKind)
typedef U8 IhdrDataPngCompressionMethod;
#define ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngCompressionMethod)
typedef U8 IhdrDataPngFilterMethod;
#define ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngFilterMethod)
#define ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_DEFAULT 0x00 // none
typedef U8 IhdrDataPngInterlaceMethod;
#define ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__STATIC
#define ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrDataPngInterlaceMethod)
typedef U32 IhdrSignatureDataCrc;
#define ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_SIZE)
#define ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IhdrSignatureDataCrc)
typedef U32 IdatCompressedPixelsSize;
#define idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__VARIABLE
#define idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_SIZE)
#define idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IdatCompressedPixelsSize)
typedef U32 IdatSignature;
#define idatSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define idatSignature__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define idatSignature__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define idatSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_SIZE)
#define idatSignature__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IdatSignature)
typedef U8* IdatCompressedPixels;
#define idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueAddressKind__CONSTANT
#define idatCompressedPixels__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__VARIABLE
#define idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET (idatSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + idatSignature__Rgb8bitPngEncoding__VALUE_SIZE)
#define idatCompressedPixels__Rgb8bitPngEncoding__VARIABLE_MEMBER_SIZE(idatCompressedPixelsSize) (idatCompressedPixelsSize)
typedef U32 IdatSignatureCompressedPixelsCrc;
#define idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueMutabilityKind__VARIABLE
#define idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__VARIABLE
#define idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) (idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET + idatCompressedPixelsSize)
#define idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IdatSignatureCompressedPixelsCrc)
typedef U32 IendDataSize;
#define iendDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueMutabilityKind__VARIABLE
#define iendDataSize__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define iendDataSize__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define iendDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) (idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) + idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_SIZE)
#define iendDataSize__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IendDataSize)
typedef U32 IendSignature;
#define iendSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueMutabilityKind__VARIABLE
#define iendSignature__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define iendSignature__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define iendSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) (iendDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) + iendDataSize__Rgb8bitPngEncoding__VALUE_SIZE)
#define iendSignature__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IendSignature)
typedef U32 IendSignatureCrc;
#define iendSignatureCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_KIND __ValueMutabilityKind__VARIABLE
#define iendSignatureCrc__Rgb8bitPngEncoding__VALUE_MUTABILITY_KIND __ValueMutabilityKind__CONSTANT
#define iendSignatureCrc__Rgb8bitPngEncoding__VALUE_ENDIANESS __ValueEndianessKind__BIG
#define iendSignatureCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) (iendSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize) + iendSignature__Rgb8bitPngEncoding__VALUE_SIZE)
#define iendSignatureCrc__Rgb8bitPngEncoding__VALUE_SIZE sizeof(IendSignatureCrc)

#define IHDR_CHUNK_SIZE (ihdrSignature__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_SIZE + ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_SIZE)
#define Rgb8bitPngEncoding__SIZE(idatCompressedPixelsSize) (pngSignature__Rgb8bitPngEncoding__VALUE_SIZE + IHDR_CHUNK_SIZE + idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_SIZE + idatSignature__Rgb8bitPngEncoding__VALUE_SIZE + idatCompressedPixelsSize + idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_SIZE + iendDataSize__Rgb8bitPngEncoding__VALUE_SIZE + iendSignature__Rgb8bitPngEncoding__VALUE_SIZE + iendSignatureCrc__Rgb8bitPngEncoding__VALUE_SIZE)

U64 maxsizeofRgb8bitPngEncoding(U32 pixelsWidth, U32 pixelsHeight);
void initRgb8bitPngEncoding(U8* pngEncoding, Rgb8bitPngPixels* pngPixels);
void encodeRgb8bitPngPixels(U8* pngEncoding, Rgb8bitPngPixels* pngPixels);
IdatCompressedPixelsSize* atIdatCompressedPixelsSize(U8* pngEncoding);



// #define _pngSignature__Rgb8bitPngEncoding__MEMBER_SIZE 8
// #define _ihdrDataPngSize__Rgb8bitPngEncoding__MEMBER_SIZE 4
// #define _ihdrSignature__Rgb8bitPngEncoding__MEMBER_SIZE 4

// #define PNG_ENCODING_IHDR_DATA_SIZE 13
// #define PNG_ENCODING_IHDR_CRC_INPUT_SIZE (_ihdrSignature__Rgb8bitPngEncoding__MEMBER_SIZE + PNG_ENCODING_IHDR_DATA_SIZE)

// #define _ihdrSignature__Rgb8bitPngEncoding__PTR_OFFSET (_pngSignature__Rgb8bitPngEncoding__MEMBER_SIZE + _ihdrDataPngSize__Rgb8bitPngEncoding__MEMBER_SIZE)

// #define PNG_ENCODING_FILTER_METHOD_SIZE 1
// #define PNG_ENCODING_FILTER_METHOD_NONE 0x00
// #define PNG_ENCODING_FILTER_METHOD_DEFAULT PNG_ENCODING_FILTER_METHOD_NONE

#endif
