/*=============================================================================
#     FileName: PngUtils.cpp
#         Desc: PngUtils implement
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-11-27 23:01:02
=============================================================================*/

#include "Pngutils.h"

//defalut ctor
PngUtils::PngUtils()
{
 #if DEBUG_MODE
    _debug_print("default constructor be called");
 #endif
}

//ctor with png file name
PngUtils::PngUtils(std::string pngfileName)
{
#if (DEBUG_MODE)
    _debug_print("File name [%s]", pngfileName.c_str());
#endif
    //current handling png file name
    this->m_pngfileName = pngfileName;
}

//dtor some resource clean operating
PngUtils::~PngUtils()
{
}

//get file name from outer with PngUtils instance
std::string PngUtils::getPngfileName()
{
#if (DEBUG_MODE)
    _debug_print("File name [%s]", this->m_pngfileName.c_str());
#endif
    return m_pngfileName;
}
//
//error handler while load image
void PngUtils::FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *msg)
{
     fprintf(stderr, "\n ======================= \n");
     fprintf(stderr, "%s_Format >> %s\n", FreeImage_GetFormatFromFIF(fif), msg);
     fprintf(stderr, "\n ======================= \n");
}

//get data assign to m_pBitmapHandler member var
BasePngPropt *PngUtils::getPnginfo()
{
    //if m_pngfileName not be set, false will be returned
    if (m_pngfileName.empty())
    {
#if (DEBUG_MODE)
        _debug_print("m_pngfileName must be set");
#endif
        fprintf(stderr, "%s\n", "Png file name is empty, please check!");
        return NULL;
    }
    //start to fill base info
    BasePngPropt *pngBaseinfo = new BasePngPropt();
    //allocate memory error
    if (!pngBaseinfo)
    {
        fprintf(stderr, "%s\n", "**** ALLOCATE MEMORY FAILED! ****");
        return NULL;
    }
    
    //set output msg funtion
    FreeImage_SetOutputMessage(FreeImageErrorHandler);

    //set png name
    pngBaseinfo->pngfileName = m_pngfileName;

    //special file format is 'png'
    pngBaseinfo->bitmapHandler = FreeImage_Load(FIF_PNG, m_pngfileName.c_str(), 0);
    //error handle
    if (!pngBaseinfo->bitmapHandler)
    {
        fprintf(stderr, "Load png [%s] failed!", m_pngfileName.c_str());
        return NULL;
    }

    //fill 4 property to struct
    pngBaseinfo->wid = FreeImage_GetWidth(pngBaseinfo->bitmapHandler);
    pngBaseinfo->hgt = FreeImage_GetHeight(pngBaseinfo->bitmapHandler);
    pngBaseinfo->bpp = FreeImage_GetBPP(pngBaseinfo->bitmapHandler);
    pngBaseinfo->clrType = FreeImage_GetColorType(pngBaseinfo->bitmapHandler);

    //debug
#if (DEBUG_MODE)
    _debug_print("Load png [%s] completed", m_pngfileName.c_str());
    _debug_print("pngBaseinfo [%s >> %p >> %u >> %u >> %u]", 
                    pngBaseinfo->pngfileName.c_str(), pngBaseinfo->bitmapHandler,
                    pngBaseinfo->wid, pngBaseinfo->hgt, pngBaseinfo->bpp);
#endif

    return pngBaseinfo;
}

