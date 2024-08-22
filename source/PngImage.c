// #include <stdlib.h>
// #include <zlib.h>
// #include "ImagePixels.h"
// #include "PngImage.h"

// void applyPngSignatureBytes(__PngImage pngImageResult) {}

// void applyIhdrBytes(__PngImage pngImageResult) {}

// void applyIdatCompressedPixelBytes(__PngImage pngImageResult, __ImagePixels imagePixels)
// {
//   z_stream pixelStream;
//   pixelStream.zalloc = Z_NULL;
//   pixelStream.zfree = Z_NULL;
//   pixelStream.opaque = Z_NULL;
//   deflateInit(&pixelStream, Z_DEFAULT_COMPRESSION);
//   pixelStream.avail_in = (uInt)getPixelsByteCount(imagePixels);
//   pixelStream.next_in = (Bytef*)imagePixels;
//   pixelStream.avail_out = (uInt)getImageMaxCompressedByteCount(pngImageResult);
//   pixelStream.next_out = (Bytef*)(pngImageResult + 41);
//   deflate(
//     &pixelStream,
//     Z_FINISH);
//   deflateEnd(&pixelStream);
// }

// __PngImage __createPngImage(IEEE32 maxCompressedPixelsByteCountScalar, __ImagePixels imagePixels) {
//     U64 maxCompressedImagePixelsByteCount = maxCompressedPixelsByteCountScalar * getPixelsByteCount(imagePixels);
//     __PngImage pngImageResult = (__PngImage)malloc(MAX_COMPRESSED_PIXELS_BYTE_COUNT_SCALAR_FIELD_SIZE + COMPRESSED_PIXEL_BYTE_COUNT_FIELD_SIZE + PNG_SIGNATURE_CHUNK_BYTE_SIZE + PNG_IHDR_CHUNK_BYTE_SIZE + PNG_IDAT_CHUNK_METADATA_BYTE_SIZE + PNG_IEND_CHUNK_BYTE_SIZE + maxCompressedImagePixelsByteCount);
//     applyPngSignatureBytes(pngImageResult);
//     applyIhdrBytes(pngImageResult);
//     applyIdatCompressedPixelBytes(pngImageResult, imagePixels);
//     applyIdatMetadataBytes(pngImageResult);
//     applyIendBytes(pngImageResult);
//     return pngImageResult;
// }
