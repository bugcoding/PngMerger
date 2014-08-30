#include <png.h>
#include <iostream>
#include <fstream>
#include <cstdio>

png_bytep *row_pointer;
png_structp png_ptr;
png_infop info_ptr;
png_byte color_type;
png_byte bit_depth;
int wid, hgt;

void read_png_file(std::string file_name)
{
    const int OFFSET = 8;
    FILE *instream = fopen(file_name.c_str(), "rb");
    if (!instream)
    {
        std::cout << "read data failed!" << std::endl;
        return ;
    }
    char *header = new char[OFFSET];
    fread(header, 1, OFFSET, instream);
    bool is_png = png_sig_cmp((png_const_bytep)header, 0, OFFSET);
    delete [] header;

    std::cout << "is_png: " << is_png << std::endl;
    //fclose(instream);

    //Init png struct
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr)
    {
        std::cout << "create_read_struct error" << std::endl;
        return ;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        std::cout << "create_info_struct error" << std::endl;
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);

        return ;
    }

    png_init_io(png_ptr, instream);
    png_set_sig_bytes(png_ptr, OFFSET);

    png_read_info(png_ptr, info_ptr);

    wid = png_get_image_width(png_ptr, info_ptr);
    hgt = png_get_image_height(png_ptr, info_ptr);

    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    int pass_num = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "%s\n", "read image info error!");
        return ;
    }

    row_pointer = new png_bytep[(int)(sizeof(png_bytep) * hgt)];
    for (int h = 0; h < hgt; h++)
    {
        row_pointer[h] = new png_byte[(int)(png_get_rowbytes(png_ptr, info_ptr))];
    }

    //read data to array from image
    png_read_image(png_ptr, row_pointer);

    fclose(instream);
}

void write_png_to_file(std::string file_name)
{
    FILE *fp = fopen(file_name.c_str(), "wb");
    if (!fp)
    {
        fprintf(stderr, "%s\n", "file could not open to write");
        return ;
    }
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "%s\n", "create_write_struct error");
        return ;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "%s\n", "create_info_struct errror!");
        return ;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "%s\n", "init_io error");
        return ;
    }

    png_init_io(png_ptr, fp);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "%s\n", "during writing header error");
        return ;
    }

    png_set_IHDR(png_ptr, info_ptr, wid, hgt, bit_depth, color_type, PNG_INTERLACE_NONE,
                        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "%s\n", "during file writing error");
        return ;
    }
    png_write_image(png_ptr, row_pointer);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "%s\n", "during writing file of end error");
        return ;
    }

    png_write_end(png_ptr, NULL);


    //destruct for above allocating memory
    for (int i = 0; i < hgt; i++)
    {
        delete [] row_pointer[i];
    }
    delete [] row_pointer;
    //close file stream
    fclose(fp);

}

void handle_png_file()
{
    int color = 3;
    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
    {
        color = 3;
    }
    else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA)
    {
        color = 4;
    }

    for (int h = 0; h < hgt; h++)
    {
        png_byte *row_tmp = row_pointer[h];
        for (int w = 0; w < wid; w++)
        {
            png_byte *col_tmp = &(row_tmp[w * color]);
            printf("pixel pos {%d-%d} -- RGB value [%d-%d-%d]\n",
                    w, h, col_tmp[0], col_tmp[1], col_tmp[2]);

            int mid = (int)((col_tmp[0] + col_tmp[1] + col_tmp[1]) / 3.0);
            col_tmp[0] = col_tmp[1] = col_tmp[2] = mid;
        }
    }
}


//int main(int argc, char *argv[])
//{
//    std::string from_file("test.png");
//    std::string to_file("test_handle.png");
//    read_png_file(from_file);
//    handle_png_file();
//    write_png_to_file(to_file);
//    return 0;
//}
