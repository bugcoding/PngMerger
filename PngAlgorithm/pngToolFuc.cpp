/*=============================================================================
#     FileName: pngToolFuc.cpp
#         Desc: tool function implement
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-08-31 22:52:22
=============================================================================*/
#include "pngToolFuc.h"

#define _debug(format,...) \
        printf("[Debug]: " format " -- %s -- %d \n",##__VA_ARGS__, __func__, __LINE__)

//check bit of png file
#define OFFSET      8

PngTools::PngTools()
{
    
}

PngTools::PngTools(const char *fileName)
{
    this->m_pngFileName = fileName;
}

PngTools::~PngTools()
{

}

void PngTools::setWillHandingPng(const char *pngFileName)
{
    this->m_pngFileName = pngFileName;
}

bool PngTools::isPngFile(const char *headerInfo)
{
    //call libpng func to judge file type
    bool isPng = png_sig_cmp((png_const_bytep)headerInfo, 0, OFFSET);

    //debug info
#if (DEBUG_OPEN)
_debug("isPng == [%d] >> m_pngFileName == [%s]", isPng, m_pngFileName.c_str());
#endif

    return isPng;
}

PngInfo *PngTools::getPngInfo()
{
    //open png file and ready to read the pixel data
    FILE *fp = fopen(m_pngFileName.c_str(), "rb");
    //error handle
    if (!fp)
    {
        fprintf(stderr, "%s\n", "open png file error!");
        return NULL;
    }
    //alloc buffer of 8 bits data
    char *header = new char[OFFSET];
    fread(header, 1, OFFSET, fp);
    if(!this->isPngFile(header))
    {
        fprintf(stderr, "%s\n", "Not a png file!");
        delete [] header;
        fclose(fp);
        return NULL;
    }
    delete [] header;

    //ready to read png
    png_structp _pngPtr;
    png_infop _infoPtr;
    png_byte _colorType;
    png_byte _bitDepth;

    //init _pngPtr
    _pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    //init _infoPtr
    _infoPtr = png_create_info_struct(_pngPtr);

    //error handle
    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "failed to read png file");
        //clean resource after error come out 
        png_destroy_read_struct(&_pngPtr, &_infoPtr, (png_infopp)NULL);
        fclose(fp);
    }
    //png io init
    png_init_io(_pngPtr, fp);
    //skip previous OFFSET bits data
    png_set_sig_bytes(_pngPtr, OFFSET);
    //start call read function
    png_read_info(_pngPtr, _infoPtr);

    //init PngInfo struct 
    PngInfo *_pngInfo = new PngInfo;

    //read wid and hgt
    _pngInfo->width = png_get_image_width(_pngPtr, _infoPtr);
    _pngInfo->height = png_get_image_height(_pngPtr, _infoPtr);
    //read colorType
    _pngInfo->colorType = png_get_color_type(_pngPtr, _infoPtr);
    //read bit depth
    _pngInfo->bitDepth = png_get_bit_depth(_pngPtr, _infoPtr);

    //update png info
    png_read_update_info(_pngPtr, _infoPtr);
    //error handle
    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "failed to During read png info");
        png_destroy_read_struct(&_pngPtr, &_infoPtr, (png_infopp)NULL);
        fclose(fp);
        return NULL;
    }
    //read pixel data
    //only support RGBA and RGB now
    int bits = (_pngInfo->colorType == PNG_COLOR_TYPE_RGB) ? 3 : 4;
    //alloc PngInfo pixelData 
    _pngInfo->pixelData = new unsigned char[_pngInfo->width * _pngInfo->height * bits];
    //get png every rows info
    png_bytep *rowPointers = png_get_rows(_pngPtr, _infoPtr);
    //according bits to fill pixel data array
    int pos = 0;
    //read each pixel data
    for (int i = 0; i < _pngInfo->height; i++) 
    {
        for (int j = 0; j < _pngInfo->width * bits; j += bits)
        {
            _pngInfo->pixelData[pos++] = rowPointers[i][j];//r
            _pngInfo->pixelData[pos++] = rowPointers[i][j + 1];//g
            _pngInfo->pixelData[pos++] = rowPointers[i][j + 2];//b
            if (bits == 4)// has alpha
            {
                _pngInfo->pixelData[pos++] = rowPointers[i][j + 3];//alpha
            }
        }
    }
    //read complete and clean resource
    png_destroy_read_struct(&_pngPtr, &_infoPtr, (png_infopp)NULL);
    //close file stream
    fclose(fp);

    //return the Pnginfo pointer
    return _pngInfo;

}
