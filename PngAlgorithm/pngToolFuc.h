/*=============================================================================
#     FileName: pngToolFuc.h
#         Desc: png handle function
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-08-31 22:44:14
=============================================================================*/
#include "png.h"
#include <cstdio>
#include <string>


#ifndef _PNG_TOOLS_FUNC_H_

#define _PNG_TOOLS_FUNC_H_

#define DEBUG_OPEN 1

class PngTools
{
public:
    //ctor default
    PngTools();
    //constructor with png file name
    PngTools(const char *fileName);
    //dtor
    ~PngTools();
    //appoint fileName
    void setWillHandingPng(const char *pngFileName);
    //judge the file of m_pngFileName designating
    bool isPngFile();


private:
    //will handle png file name
    std::string m_pngFileName;
};


#endif
