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
PngUtils::PngUtils():
m_pBitmapHandler(NULL)
{
    
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
    //do not delloced  memory
    if (m_pBitmapHandler)
    {
        FreeImage_Unload(m_pBitmapHandler);
        m_pBitmapHandler = NULL;
    }
}

//get file name from outer with PngUtils instance
std::string PngUtils::getPngfileName()
{
#if (DEBUG_MODE)
    _debug_print("File name [%s]", this->m_pngfileName.c_str());
#endif
    return m_pngfileName;
}

//get data assign to m_pBitmapHandler member var
bool PngUtils::getPnginfo()
{
    //if m_pngfileName not be set, false will be returned
    if (m_pngfileName.empty())
    {
#if (DEBUG_MODE)
        _debug_print("m_pngfileName must be set");
#endif
        fprintf(stderr, "%s\n", "Png file name is empty, please check!");
        return false;
    }
    //special file format is 'png'
    m_pBitmapHandler = FreeImage_Load(FIF_PNG, m_pngfileName.c_str(), 0);
    //error handle
    if (!m_pBitmapHandler)
    {
        fprintf(stderr, "%s\n", "Load png [%s] failed!", m_pngfileName.c_str());
        return false;
    }
    return true;
}

