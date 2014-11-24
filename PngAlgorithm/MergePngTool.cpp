/*=============================================================================
#     FileName: MergePngTool.cpp
#         Desc: merge tool functio
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-11-24 22:07:07
=============================================================================*/

#include "MergePngTool.h"


MergePngTool::MergePngTool():
m_pMergeImage(NULL)
{
}

MergePngTool::MergePngTool(std::string pngDir)
{
#if (DEBUG_OPEN)
    _debug("Directory name: [%s]", pngDir.c_str());
#endif
    this->m_pngFileDir = pngDir;
}

MergePngTool::~MergePngTool()
{
    if (m_pMergeImage)
    {
        for (uint i = 0; i < m_pMergeImage->pngFileVec.size(); i++)
        {
            delete m_pMergeImage->pngFileVec[i];
        }
        delete m_pMergeImage;
    }
}
bool MergePngTool::getPngFromDir()
{
    //not specifical dir name
    if (m_pngFileDir.empty())
    {
        return false;
    }
//list directory file under win32
#if (defined(_WIN32) || defined(WIN32) || defined(_win32))
    //file info struct
    WIN32_FIND_DATA fileData;
    //handle find file 
    HANDLE fileFound = INVALID_HANDLE_VALUE;//default value
    //extName var
    char extName[128] = "\0";

    //png file border value
    uint minTop = 0, maxBottom = 0, minLeft = 0, maxRight = 0;

    //start traversing
    fileFound = FindFirstFile(m_pngFileDir.c_str(), &fileData);
    //file not found
    if (INVALID_HANDLE_VALUE == fileFound)
    {
        _debug("file [%s] not found!", m_pngFileDir.c_str());
        return false;
    }

    //start to fill data to MergedImageInfo
    this->m_pMergeImage = new MergedImageInfo();

    //list file
    do
    {
        //check is file or not
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            //is not a dir and get file ext name
            this->getFileExtName(fileData.cFileName, extName);
            //judge ext name
            if (!strcmp(extName, EXT_NAME))
            {
                //construct file real path 
                std::string filePath = m_pngFileDir + fileData.cFileName;

                //read png file data to PngInfo
                PngTools *pt = new PngTools(filePath.c_str());
                PngInfo *pInfo = new PngInfo();
                //read png[fileData.cFileName] to PngInfo
                pInfo = pt->readPngInfo();
                //fill info with data
                this->m_pMergeImage->pngFileVec.push_back(pInfo);
                //compute area of big image
                AreaOfImage aoi = pt->getPngBoundary(*(pInfo->pixelData), pInfo->width, pInfo->height);

                //confirm area of boder value
                if (minTop == 0 || aoi.minTop < minTop)
                {
                    minTop = aoi.minTop;
                }
                if (minLeft == 0 || aoi.minLeft < minLeft)
                {
                    minLeft = aoi.minLeft;
                }
                if (maxBottom < aoi.maxBottom)
                {
                    maxBottom = aoi.maxBottom;
                }
                if (maxRight < aoi.maxRight)
                {
                    maxRight = aoi.maxRight;
                }

                //final delete PngTools
                delete pt;
            }
        }


    }while(FindNextFile(fileFound, &fileData));
    //read all png file in diretory [m_pngDir]
    //according border value to confirm big image width and height
    this->m_pMergeImage->bigImageWid = maxRight - minLeft;
    this->m_pMergeImage->bigImageHgt = maxBottom - minTop;
    //total frame equals file number
    this->m_pMergeImage->totalFrames = m_pMergeImage->pngFileVec.size();
    //area of big merged image
    this->m_pMergeImage->bigImageArea.minTop = minTop;
    this->m_pMergeImage->bigImageArea.minLeft = minLeft;
    this->m_pMergeImage->bigImageArea.maxBottom = maxBottom;
    this->m_pMergeImage->bigImageArea.maxRight = maxRight;
    //set mergedImage name to directory name
    this->m_pMergeImage->mergedImageName = this->m_pngFileDir;
    
    return true;
    
#endif
    

}

//获取文件名的后续
void MergePngTool::getFileExtName(const char *fileName, char *ext)
{
    assert(fileName);

    char temp[256] = "\0";
    //get copy of fileName
    strcpy(temp, fileName);
    char *loc = strrchr(temp, DOT_FLAG);

    //find dot location
    if (loc)
    {
        //for exp: get "file.ext" put "ext" to ext
        strcpy(ext, loc + 1);
    }
    else
    {
        //如果没有找到后缀,将entention置空
        strcpy(ext, "\0");
    }
}
