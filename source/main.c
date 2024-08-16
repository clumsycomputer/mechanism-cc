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

// #include <png.h>
// #include <stdio.h>
// #include <stdlib.h>

// typedef int Rgb8bitPixelWidth;
// typedef int Rgb8bitPixelHeight;
// typedef png_bytep Rgb8bitPixelData;
// typedef struct {
//     png_byte red;
//     png_byte green;
//     png_byte blue;
// } Rgb8bitPixelColor;

// #define RGB_8BIT_PIXEL_BYTE_COUNT 3
// #define RGB_8BIT_PIXEL_WIDTH_SIZE sizeof(Rgb8bitPixelWidth)
// #define RGB_8BIT_PIXEL_HEIGHT_SIZE sizeof(Rgb8bitPixelHeight)
// #define RGB_8BIT_PIXEL_WIDTH_INDEX (RGB_8BIT_PIXEL_HEIGHT_SIZE + RGB_8BIT_PIXEL_WIDTH_SIZE)
// #define RGB_8BIT_PIXEL_HEIGHT_INDEX (RGB_8BIT_PIXEL_HEIGHT_SIZE)

// int *rgb_8bit_pixel_data_pixel_width_ptr__(png_bytep rgb_8bit_pixel_data) {
//     return rgb_8bit_pixel_data - RGB_8BIT_PIXEL_WIDTH_INDEX;
// }

// int *rgb_8bit_pixel_data_pixel_height_ptr__(png_bytep rgb_8bit_pixel_data) {
//     return rgb_8bit_pixel_data - RGB_8BIT_PIXEL_HEIGHT_INDEX;
// }

// int rgb_8bit_pixel_width__(png_bytep rgb_8bit_pixel_data) {
//     return *rgb_8bit_pixel_data_pixel_width_ptr__(rgb_8bit_pixel_data);
// }

// int rgb_8bit_pixel_height__(png_bytep rgb_8bit_pixel_data) {
//     return *rgb_8bit_pixel_data_pixel_height_ptr__(rgb_8bit_pixel_data);
// }

// png_bytep create_rgb_8bit_pixel_data(int pixel_width, int pixel_height)
// {
//     char *rgb_8bit_pixel_data_result = (char *)malloc(pixel_width * pixel_height * RGB_8BIT_PIXEL_BYTE_COUNT + RGB_8BIT_PIXEL_WIDTH_SIZE + RGB_8BIT_PIXEL_HEIGHT_SIZE);
//     rgb_8bit_pixel_data_result = rgb_8bit_pixel_data_result + RGB_8BIT_PIXEL_WIDTH_SIZE + RGB_8BIT_PIXEL_HEIGHT_SIZE;
//     *rgb_8bit_pixel_data_pixel_width_ptr__(rgb_8bit_pixel_data_result) = pixel_width;
//     *rgb_8bit_pixel_data_pixel_height_ptr__(rgb_8bit_pixel_data_result) = pixel_height;
//     return (png_byte *)rgb_8bit_pixel_data_result;
// }

// void fill_rgb_8bit_pixel_data(png_bytep rgb_8bit_pixel_data, Rgb8bitPixelColor fill_color) {
//     for (int pixel_row_index = 0; pixel_row_index < rgb_8bit_pixel_height__(rgb_8bit_pixel_data); pixel_row_index++)
//     {
//         int row_initial_pixel_offset = pixel_row_index * rgb_8bit_pixel_width__(rgb_8bit_pixel_data) * RGB_8BIT_PIXEL_BYTE_COUNT;
//         for (int pixel_column_index = 0; pixel_column_index < rgb_8bit_pixel_width__(rgb_8bit_pixel_data); pixel_column_index++)
//         {
//             int pixel_index_offset = row_initial_pixel_offset + pixel_column_index * RGB_8BIT_PIXEL_BYTE_COUNT;
//             int pixel_red_byte_index = pixel_index_offset;
//             int pixel_green_byte_index = pixel_index_offset + 1;
//             int pixel_blue_byte_index = pixel_index_offset + 2;
//             rgb_8bit_pixel_data[pixel_red_byte_index] = fill_color.red;
//             rgb_8bit_pixel_data[pixel_green_byte_index] = fill_color.green;
//             rgb_8bit_pixel_data[pixel_blue_byte_index] = fill_color.blue;
//         }
//     }
// }

// void write_rgb_8bit_png_image(png_bytep rgb_8bit_pixel_data, FILE *output_file_ptr)
// {
//     int png_bit_depth = 8;
//     png_structp png_struct_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//     png_infop png_info_ptr = png_create_info_struct(png_struct_ptr);
//     png_bytep pixel_rows_ptr[rgb_8bit_pixel_height__(rgb_8bit_pixel_data)];
//     for (int row_index = 0; row_index < rgb_8bit_pixel_height__(rgb_8bit_pixel_data); row_index++)
//     {
//         pixel_rows_ptr[row_index] = &(rgb_8bit_pixel_data[row_index * rgb_8bit_pixel_width__(rgb_8bit_pixel_data) * RGB_8BIT_PIXEL_BYTE_COUNT]);
//     }
//     png_init_io(png_struct_ptr, output_file_ptr);
//     png_set_IHDR(png_struct_ptr, png_info_ptr, rgb_8bit_pixel_width__(rgb_8bit_pixel_data), rgb_8bit_pixel_height__(rgb_8bit_pixel_data), png_bit_depth, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
//     png_write_info(png_struct_ptr, png_info_ptr);
//     png_write_image(png_struct_ptr, pixel_rows_ptr);
//     png_write_end(png_struct_ptr, NULL);
//     png_destroy_write_struct(&png_struct_ptr, &png_info_ptr);
// }

// void free_rgb_8bit_pixel_data(png_bytep rgb_8bit_pixel_data)
// {
//     free(rgb_8bit_pixel_data_pixel_width_ptr__(rgb_8bit_pixel_data));
// }

// int main()
// {
//     char *output_file_name = "foo.png";
//     int max_pixel_channel_value = (int)sizeof(png_byte) * 255;
//     int pixel_width = 256;
//     int pixel_height = 256;
//     Rgb8bitPixelColor fill_color = {.red = 255, .green = 128, .blue = 0};

//     FILE *image_file_ptr = fopen(output_file_name, "wb");
//     png_bytep rgb_8bit_pixel_data = create_rgb_8bit_pixel_data(pixel_width, pixel_height);
//     fill_rgb_8bit_pixel_data(rgb_8bit_pixel_data, fill_color);
//     write_rgb_8bit_png_image(rgb_8bit_pixel_data, image_file_ptr);
//     free_rgb_8bit_pixel_data(rgb_8bit_pixel_data);
//     fclose(image_file_ptr);
//     return 0;
// }

#include "ImagePixels.h"
#include <stdio.h>

int main() {
  Rgb8bitImagePixels imagePixels =
      createRgb8bitImagePixels(
          512,
          512);
  printf("%d\n", getPixelsChannelCount(imagePixels));
  return 0;
}
