/*=============================================================================
#     FileName: pngToolFuc.h
#         Desc: png handle function
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-08-31 22:44:14
=============================================================================*/



#ifndef _PNG_TOOLS_FUNC_H_

#define _PNG_TOOLS_FUNC_H_


extern "C"
{
    #include "png.h"
}
#include <cstdio>
#include <string>
#include <assert.h>
#include <iostream>
#include <vector>

//output debug info or not
#define DEBUG_OPEN 1
//ARGB judge A set or not
#define NOT_TRANSPARENT     0xFF000000


//area of big picture according 4 value (up, down, left, right)
typedef struct _areaOfBigImage
{
    //top border of image
    unsigned int minTop;
    //bottom border of image
    unsigned int maxBottom;
    //left border of image
    unsigned int minLeft;
    //right border of image
    unsigned int maxRight;

}AreaOfImage;


//Png image info struct
typedef struct _imageInfo
{
    //image name
    std::string imageName;
    //png piexel matrix
    png_bytep *pixelData;
    //Png source file width and height
    int width, height;
    //png color type (rgba or rgb etc..)
    png_byte colorType;
    //png bit depth (8 24 32 etc..)
    png_byte bitDepth;
}PngInfo;


/*
 * big merged image stuct cotain final image width, final height
 * png file list, fps, big image name, total frame, area of big image
 *
 */

typedef struct _bigMergedImageInfo
{
    //after merged image name
    std::string mergedImageName;
    //total frame (total png file number)
    unsigned int totalFrames;
    //fps
    unsigned int fps;
    //png file list
    std::vector<PngInfo*> pngFileVec;
    //area of big image
    AreaOfImage bigImageArea;
    //origin image width and height
    unsigned int bigImageWid;
    unsigned int bigImageHgt;

}MergedImageInfo;


//single png file handling
class PngTools
{
//public member funtion
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
    //according png file origion data to compute png file minial area
    AreaOfImage getPngBoundary(png_bytep imageData, int wid, int hgt);
//private member funtion
private:

//public member variable
public:

//private member variable
private:
    //will handle png file name
    std::string m_pngFileName;
    //PngInfo pointer
    PngInfo *m_pInfo;
    //is read png file to m_pInfo or not
    bool m_bIsReadPng;
};


#endif
