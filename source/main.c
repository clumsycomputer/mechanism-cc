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

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

void write_png_image(int pixel_width, int pixel_height, png_bytep pixel_row_ptrs, FILE* output_file_ptr) {
    png_structp png_struct_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop png_info_ptr = png_create_info_struct(png_struct_ptr);
    png_init_io(png_struct_ptr, output_file_ptr);
    png_set_IHDR(png_struct_ptr, png_info_ptr, pixel_width, pixel_height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_struct_ptr, png_info_ptr);
    png_write_image(png_struct_ptr, pixel_row_ptrs);
    png_write_end(png_struct_ptr, NULL);
    png_destroy_write_struct(&png_struct_ptr, &png_info_ptr);
}

void rasterize_points() {}

int main()
{
    int max_pixel_channel_size = 255;
    int pixel_byte_count = 3;
    int pixel_width = 256;
    int pixel_height = 256;
    png_bytep pixel_data_ptr = (png_byte *)malloc(pixel_width * pixel_height * pixel_byte_count);
    png_bytep pixel_row_ptrs[pixel_height];
    for (int pixel_row_index = 0; pixel_row_index < pixel_height; pixel_row_index++)
    {
        int row_initial_pixel_offset = pixel_row_index * pixel_width * pixel_byte_count;
        pixel_row_ptrs[pixel_row_index] = pixel_data_ptr + row_initial_pixel_offset;
        for (int pixel_column_index = 0; pixel_column_index < pixel_width; pixel_column_index++)
        {
            int pixel_index_offset = row_initial_pixel_offset + pixel_column_index * pixel_byte_count;
            int pixel_red_byte_index = pixel_index_offset;
            int pixel_green_byte_index = pixel_index_offset + 1;
            int pixel_blue_byte_index = pixel_index_offset + 2;
            pixel_data_ptr[pixel_red_byte_index] = (png_byte)(pixel_column_index % max_pixel_channel_size);
            pixel_data_ptr[pixel_green_byte_index] = (png_byte)(pixel_row_index % max_pixel_channel_size);
            pixel_data_ptr[pixel_blue_byte_index] = (png_byte)((pixel_column_index + pixel_row_index) % max_pixel_channel_size);
        }
    }
    FILE *image_file_ptr = fopen("foo.png", "wb");
    write_png_image(pixel_width, pixel_height, pixel_row_ptrs, image_file_ptr);
    fclose(image_file_ptr);
    free(pixel_data_ptr);
    return 0;
}
