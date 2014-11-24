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
    #include <windows.h>
#elif defined(_LINUX)
    #include <sys/types.h>
#endif
//
#define DOT_FLAG    '.'
//extName
#define EXT_NAME    "png"

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
    uint totalFrames;
    //fps
    uint fps;
    //png file list
    std::vector<PngInfo*> pngFileVec;
    //area of big image
    AreaOfImage bigImageArea;
    //origin image width and height
    uint bigImageWid;
    uint bigImageHgt;

}MergedImageInfo;


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
void getFileExtName(const char *fileName, char *ext);
    

private:
    //big merged image pointer
    MergedImageInfo *m_pMergeImage;
    //directory name contain png file
    std::string m_pngFileDir;
};











#endif
