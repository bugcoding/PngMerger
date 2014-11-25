/*=============================================================================
#     FileName: MergePngTool.h
#         Desc: header
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-11-24 22:07:45
=============================================================================*/

#ifndef _MERGE_PNG_TOOL_H_

#define _MERGE_PNG_TOOL_H_

#include "pngToolFuc.h"
#if (defined(_WIN32) || defined(WIN32) || defined(_win32))

    //file handling on win32 system
    #include <windows.h>

#elif (defined(_LINUX) || defined(__APPLE__) || defined(__MACOSX__)) 

    //file handing api on like UNIX system
    #include <sys/types.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    //compatiable win32 BYTE define
    typedef unsigned char   BYTE;

#endif

//reset vector size
#define RESET_VEC_SIZE(curVec, setSize)  \
        do\
        {\
            if (curVec.size() < (uint)setSize)\
            {\
                curVec.resize(setSize);\
            }\
        }while(false)

//extension name spliter
#define DOT_FLAG    '.'
//extName
#define EXT_NAME    "png"

/*
 * big merged image stuct cotain final image width, final height
 * png file list, fps, big image name, total frame, area of big image
 */
typedef struct _bigMergedImageInfo
{
    //after merged image name
    std::string mergedImageName;
    //total frame (total png file number)
    uint totalFrames;
    //fps
    uint fps;
    //png file list
    std::vector<PngInfo*> pngFileVec;
    //area of big image
    AreaOfImage bigImageArea;
    //origin image width and height
    uint bigImageWid, bigImageHgt;

}MergedImageInfo;


//final merge png class
class MergePngTool
{
public:
    //default ctor
    MergePngTool();
    //ctor with diretory name
    MergePngTool(std::string dirName);
    //dtor
    ~MergePngTool();
    /*
     * list dir specification m_pngFileDir 
     * read single png file with [PngTools]
     * write origin png data to MergedImageInfo
     */
    bool getPngFromDir();

private:
    //get file extension name (xxx.png) png is extName
    void getFileExtName(const char *fileName, char *ext);
    /*
     * fill each single png file data 
     * from [m_pMergeImage] to
     * big image buf[m_mergedImageBuf]
     */
    bool copyAllPngData2Buf();

    /*
     * write data from buffer to file
     * file name with m_pMergeImage->mergedImageName
     * @param 
     *      dstWid, destination file width
     *      dstHgt, destination file height
     */
    bool writeData2File(uint dstWid, uint dstHgt);

private:
    //big merged image pointer
    MergedImageInfo *m_pMergeImage;
    //directory name contain png file
    std::string m_pngFileDir;
    //buffer for big merged image data
    std::vector<BYTE> m_mergedImageBuf;
};




#endif
