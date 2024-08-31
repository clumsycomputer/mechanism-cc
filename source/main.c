// #include <libtcc.h>

// char hello_tcc_script[] =
//     "#include <tcclib.h>\n"
//     "\n"
//     "void get_frame_points(int frame_count, int frame_index, double frame_stamp) {\n"
//     "printf(\"frame_count: %d, frame_index: %d, frame_stamp: %.4f\\n\", frame_count, frame_index, frame_stamp);\n"
//     "}\n"
//     "\n";

// int main(int argc, char **argv)
// {
//     TCCState *tcc_state = tcc_new();
//     tcc_set_output_type(tcc_state, TCC_OUTPUT_MEMORY);
//     tcc_compile_string(tcc_state, hello_tcc_script);
//     tcc_relocate(tcc_state);
//     void (*get_frame_points)() = tcc_get_symbol(tcc_state, "get_frame_points");
//     get_frame_points();
//     int frame_count = 128;
//     for (int frame_index = 0; frame_index < frame_count; frame_index++)
//     {
//         double frame_stamp = (double)frame_index / frame_count;
//         get_frame_points(frame_count, frame_index, frame_stamp);
//     }
//     tcc_delete(tcc_state);
//     return 0;
// }
#include "ImagePool.h"
#include <stdio.h>
#include <zlib.h>

int main(void)
{
  ImagePoolView imagePoolView =
    createRgb8bitImagePool(
      3,
      3);
  int ROW_DEFLATE_FILTER_OPTION_SIZE = 1;
  U8 ROW_DEFLATE_FILTER_OPTION = 0;
  for (int rowIndex = 0; rowIndex < getPixelsHeight(imagePoolView.poolPixels); rowIndex++)
  {
    int rowSize =
      getPixelsWidth(imagePoolView.poolPixels) * getPixelsPixelByteCount(imagePoolView.poolPixels) + ROW_DEFLATE_FILTER_OPTION_SIZE;
    int rowInitialOffset =
      rowIndex * rowSize;
    *(U8*)(imagePoolView.poolPixels + rowInitialOffset) =
      ROW_DEFLATE_FILTER_OPTION;
    int rowInitialPixelOffset =
      rowInitialOffset + ROW_DEFLATE_FILTER_OPTION_SIZE;
    for (int columnIndex = 0; columnIndex < getPixelsWidth(imagePoolView.poolPixels); columnIndex++)
    {
      int pixelIndexOffset = rowInitialPixelOffset + columnIndex * getPixelsPixelByteCount(imagePoolView.poolPixels);
      int pixelRedChannelIndex = pixelIndexOffset;
      int pixelGreenChannelIndex = pixelIndexOffset + getPixelsChannelByteDepth(imagePoolView.poolPixels);
      int pixelBlueChannelIndex = pixelIndexOffset + 2 * getPixelsChannelByteDepth(imagePoolView.poolPixels);
      *(U8*)(imagePoolView.poolPixels + pixelRedChannelIndex) = 255;
      *(U8*)(imagePoolView.poolPixels + pixelGreenChannelIndex) = 0;
      *(U8*)(imagePoolView.poolPixels + pixelBlueChannelIndex) = 0;
    }
  }
  updatePngDataPixels(
    imagePoolView.poolPixels,
    imagePoolView.poolPng);
  FILE* imageFile =
    fopen(
      "foo.png",
      "wb");
  fwrite(
    imagePoolView.poolPng,
    1,
    getPngDataByteCount(imagePoolView.poolPng),
    imageFile);
  fclose(imageFile);
  freeImagePool(imagePoolView);
  return 0;
}
