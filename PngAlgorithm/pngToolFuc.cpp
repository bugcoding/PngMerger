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

bool PngTools::isPngFile()
{
    //check bits of file
    const int OFFSET = 8;
    FILE *fp = fopen(m_pngFileName.c_str(), "rb");
    if (!fp)
    {
        fprintf(stderr, "%s\n", "open png file error!");
        return false;
    }
    //alloc buffer of 8 bits data
    char *header = new char[OFFSET];
    fread(header, 1, OFFSET, fp);
    //call libpng func to judge file type
    bool isPng = png_sig_cmp((png_const_bytep)header, 0, OFFSET);
    delete [] header;
    //close file stream
    fclose(fp);

    //debug info
#if (DEBUG_OPEN)
_debug("isPng == [%d] >> m_pngFileName == [%s]", isPng, m_pngFileName.c_str());
#endif

    return isPng;
}
