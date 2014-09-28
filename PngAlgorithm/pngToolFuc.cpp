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
        printf("[Debug]: " format " -- function[%s] -- line[%d] \n",##__VA_ARGS__, __func__, __LINE__)

//check bit of png file
#define OFFSET      8

PngTools::PngTools():
m_pInfo(NULL),
m_bIsReadPng(false)
{
    
}

PngTools::PngTools(const char *fileName)
{
    this->m_pngFileName = fileName;
}

PngTools::~PngTools()
{
    //free alloc heap memory
    if (m_pInfo)
    {
        for (int i = 0; i < m_pInfo->height; i++)
        {
            delete [] m_pInfo->pixelData[i];
        }
        delete [] m_pInfo->pixelData;
        delete m_pInfo;
        m_pInfo = NULL;//after delloc memory set value NULL to pointer
    }
    m_bIsReadPng = false;
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

PngInfo *PngTools::readPngInfo()
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
    if(this->isPngFile(header))
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
    m_pInfo = new PngInfo;

    //read wid and hgt
    m_pInfo->width = png_get_image_width(_pngPtr, _infoPtr);
    m_pInfo->height = png_get_image_height(_pngPtr, _infoPtr);
    //read colorType
    m_pInfo->colorType = png_get_color_type(_pngPtr, _infoPtr);
    //read bit depth
    m_pInfo->bitDepth = png_get_bit_depth(_pngPtr, _infoPtr);

#if (DEBUG_OPEN)
    _debug("wid[%d]--hgt[%d]--colorType[%d]--bitDepth[%d]", 
            m_pInfo->width, m_pInfo->height, m_pInfo->colorType, m_pInfo->bitDepth);
#endif

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
    
    //alloc PngInfo pixelData for rows
    m_pInfo->pixelData = new png_bytep[(unsigned int)sizeof(png_bytep) * m_pInfo->height];
    //alloc piexelData for cols
    for (int i = 0; i < m_pInfo->height; i++)
    {
        m_pInfo->pixelData[i] = new png_byte[(unsigned int)(png_get_rowbytes(_pngPtr, _infoPtr))];
    }
    
    //read data to pixelData
    png_read_image(_pngPtr, m_pInfo->pixelData);

    //read complete and clean resource
    png_destroy_read_struct(&_pngPtr, &_infoPtr, (png_infopp)NULL);
    //close file stream
    fclose(fp);
    
    //set flag 
    this->m_bIsReadPng = true;

    //return the Pnginfo pointer
    return m_pInfo;

}

bool PngTools::writePngData2File(const char *fileName)
{
#if (DEBUG_OPEN)
    assert(fileName);
#endif

    //open file
    FILE *wfp = fopen(fileName, "wb");
    if (!wfp)
    {
        fprintf(stderr, "%s\n", "open file [%s] error!");
        return false;
    }

    //create write_strcut of png
    png_structp _pngPtr;
    png_infop _infoPtr;
    
    _pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _infoPtr = png_create_info_struct(_pngPtr);

    //error handle while struct create failed
    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "failed during write png file");
        fclose(wfp);
        png_destroy_write_struct(&_pngPtr, &_infoPtr);
        return false;
    }
    //init io
    png_init_io(_pngPtr, wfp);
    //error
    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "during write png header error");
        fclose(wfp);
        png_destroy_write_struct(&_pngPtr, &_infoPtr);
        return false;
    }
    //write png header data
    png_set_IHDR(_pngPtr, _infoPtr, 
                m_pInfo->width, m_pInfo->height, 
                m_pInfo->bitDepth, m_pInfo->colorType,
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                PNG_FILTER_TYPE_BASE);

    //write png
    png_write_info(_pngPtr, _infoPtr);

    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "during file writing error");
        fclose(wfp);
        png_destroy_write_struct(&_pngPtr, &_infoPtr);
        return false;
    }

    //start to write info
    png_write_image(_pngPtr, m_pInfo->pixelData);
    
    //write end error handle
    if (setjmp(png_jmpbuf(_pngPtr)))
    {
        fprintf(stderr, "%s\n", "failed during write png end data");
        fclose(wfp);
        png_destroy_write_struct(&_pngPtr, &_infoPtr);
        return false;
    }
    
    //clean resource
    fclose(wfp);
    png_destroy_write_struct(&_pngPtr, &_infoPtr);

#if (DEBUG_OPEN)
    _debug("Write png to file[%s] completed!", fileName);
#endif
    return true;
}

std::string PngTools::getFileName()
{
#if (DEBUG_OPEN)
    _debug("m_pngFileName >> [%s]", m_pngFileName.c_str());
#endif

    return this->m_pngFileName;
}

bool PngTools::handlePng()
{
    //check color type and promise has read png file to m_pInfo
    int bits = 3;
    if (this->m_bIsReadPng)
    {
        if (m_pInfo->colorType == PNG_COLOR_TYPE_RGB)
        {
            bits = 3;
        }
        else if (m_pInfo->colorType == PNG_COLOR_TYPE_RGBA)
        {
            bits = 4;
        }
        else //reserve to extend
        {

        }
    }
#if (DEBUG_OPEN)    
    _debug("Png [%s] colorBits [%d]", m_pngFileName.c_str(), bits);
#endif

    //png data handing
    //traverse pixelData as array
    for (int h = 0; h < m_pInfo->height; h++)
    {
        //get row of matrix
        png_byte *rowTmp = m_pInfo->pixelData[h];
        for (int w = 0; w < m_pInfo->width; w++)
        {
            //get col of matrix
            png_byte *colTmp = &(rowTmp[bits * w]);
            //pixel handing 

            //output each pixel value
            if (bits == 3)
            {
#if (DEBUG_OPEN)
            printf("Pixel Pos{%-3d, %-3d} >>> RGB [%-3d # %-3d # %-3d]\n", 
                            w, h, colTmp[0], colTmp[1], colTmp[2]);
#endif
            }
            else
            {
#if (DEBUG_OPEN)
            printf("Pixel Pos{%-3d, %-3d} >>> RGB [%-3d # %-3d # %-3d # %-3d]\n", 
                            w, h, colTmp[0], colTmp[1], colTmp[2], colTmp[3]);
#endif
            }
            
            //@Note Test change png to gray
            int midColor = (colTmp[0] + colTmp[1] + colTmp[2]) / 3.0;
            //assignment
            colTmp[0] = colTmp[1] = colTmp[2] = midColor;
        }
    }
    return true;
}
