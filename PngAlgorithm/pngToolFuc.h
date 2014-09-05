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
#include <assert.h>
#include <iostream>


#ifndef _PNG_TOOLS_FUNC_H_

#define _PNG_TOOLS_FUNC_H_

#define DEBUG_OPEN 1


//Png image info struct
typedef struct _imageInfo
{
    //png piexel matrix
    png_bytep *pixelData;
    //Png source file width and height
    int width, height;
    //png color type (rgba or rgb etc..)
    png_byte colorType;
    //png bit depth (8 24 32 etc..)
    png_byte bitDepth;
}PngInfo;


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
    //judge png file
    bool isPngFile(const char *headerInfo);
    //get info from png file 
    PngInfo *readPngInfo();
    //wwite png data to file
    bool writePngData2File(const char *fileName);
    //get file name
    std::string getFileName();
    //handle png file with PngInfo
    bool handlePng();

private:
    //will handle png file name
    std::string m_pngFileName;
    //PngInfo pointer
    PngInfo *m_pInfo;
    //is read png file to m_pInfo or not
    bool m_bIsReadPng;
};


#endif
