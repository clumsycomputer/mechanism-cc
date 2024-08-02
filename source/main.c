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

int main()
{
    int width = 256;
    int height = 256;
    png_bytep image_data = (png_byte *)malloc(width * height * 3);
    png_bytep row_pointers[height];
    for (int y = 0; y < height; y++)
    {
        row_pointers[y] = image_data + y * width * 3;
        for (int x = 0; x < width; x++)
        {
            row_pointers[y][x * 3] = (png_byte)(x % 255);           // Red
            row_pointers[y][x * 3 + 1] = (png_byte)(y % 255);       // Green
            row_pointers[y][x * 3 + 2] = (png_byte)((x + y) % 255); // Blue
        }
    }
    FILE *fp = fopen("image.png", "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    free(image_data);
    return 0;
}
