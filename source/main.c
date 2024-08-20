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
#include "ImagePixels.h"
#include <stdio.h>

int main(void)
{
  Rgb16bitImagePixels imagePixels =
    createRgb16bitImagePixels(
      512,
      512);
  printf("%d\n", getPixelsKind(imagePixels));
  printf("%d\n", getPixelsChannelCount(imagePixels));
  printf("%d\n", getPixelsChannelBitDepth(imagePixels));
  printf("%d\n", getPixelsChannelByteDepth(imagePixels));
  printf("%d\n", getPixelsPixelByteCount(imagePixels));
  printf("%d\n", getPixelsWidth(imagePixels));
  printf("%d\n", getPixelsHeight(imagePixels));
  for (int rowIndex = 0; rowIndex < getPixelsHeight(imagePixels); rowIndex++)
  {
    int rowInitialPixelOffset = rowIndex * getPixelsWidth(imagePixels) * getPixelsPixelByteCount(imagePixels);
    for (int columnIndex = 0; columnIndex < getPixelsWidth(imagePixels); columnIndex++)
    {
      int pixelIndexOffset = rowInitialPixelOffset + columnIndex * getPixelsPixelByteCount(imagePixels);
      int pixelRedChannelIndex = pixelIndexOffset;
      int pixelGreenChannelIndex = pixelIndexOffset + getPixelsChannelByteDepth(imagePixels);
      int pixelBlueChannelIndex = pixelIndexOffset + 2 * getPixelsChannelByteDepth(imagePixels);
      *(U16*)(imagePixels + pixelRedChannelIndex) = 65535;
      *(U16*)(imagePixels + pixelGreenChannelIndex) = 32767;
      *(U16*)(imagePixels + pixelBlueChannelIndex) = 0;
    }
  }
  FILE* imagePixelsOutputFile =
    fopen(
      "foo.png",
      "wb");
  writeRgbImagePixels(
    imagePixels,
    imagePixelsOutputFile);
  fclose(imagePixelsOutputFile);
  freeImagePixels(imagePixels);
  return 0;
}
