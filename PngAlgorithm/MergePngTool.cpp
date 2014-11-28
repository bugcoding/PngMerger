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
    //match new alloc
    if (m_pMergeImage)
    {
        for (uint i = 0; i < m_pMergeImage->pngFileVec.size(); i++)
        {
            delete m_pMergeImage->pngFileVec[i];
            m_pMergeImage->pngFileVec[i] = NULL;
        }
        delete m_pMergeImage;
        m_pMergeImage = NULL;
    }
}
bool MergePngTool::getPngFromDir()
{
    //not specifical dir name
    if (m_pngFileDir.empty())
    {
        fprintf(stderr, "%s\n", "Member variable [m_pngFileDir] must be set!");
        return false;
    }
    
    //common variable for linux and win32

    //extName var
    char extName[128] = "\0";
    //png file border value
    uint minTop = 0, maxBottom = 0, minLeft = 0, maxRight = 0;


//list directory file under win32
#if (defined(_WIN32) || defined(WIN32) || defined(_win32))
    //file info struct
    WIN32_FIND_DATA fileData;
    //handle find file 
    HANDLE fileFound = INVALID_HANDLE_VALUE;//default value

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

#elif (defined(_LINUX) || defined(__APPLE__) || defined(__MACOSX__)) 
    //unix api for file handling
    DIR *tmpDir = NULL;
    //all file info under the dir
    struct dirent *files = NULL;
    //file state for checking file is directory or not
    struct stat fileState = {0};
    
    //open the dir
    if (!(tmpDir = opendir(m_pngFileDir.c_str())))
    {
#if (DEBUG_OPEN)
        _debug("Open directory[%s] error!", m_pngFileDir.c_str());
#endif
        return false;
    }

    //start to fill data to MergedImageInfo
    this->m_pMergeImage = new MergedImageInfo();

    //traversing all file under the dir
    while ((files = readdir(tmpDir)))
    {
        //get file real path for absolutly
        std::string filePath = m_pngFileDir + files->d_name;

        //check file state if error out , continue
        if (lstat(filePath.c_str(), &fileState) < 0)
        {
#if (DEBUG_OPEN)
            _debug("File [%s] state error!", filePath.c_str());
#endif
            return false;
        }
        //confirm *not* a directory
        if (!S_ISDIR(fileState.st_mode))
        {
           this->getFileExtName(filePath.c_str(), extName);
           //must be png endwith
           if (!strcmp(extName, EXT_NAME))
           {
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
    }

    
#endif
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

#if (DEBUG_OPEN)
    //image info debug output
    for (int i = 0; i < this->m_pMergeImage->pngFileVec.size(); i++)
    {
        //all file name
        fprintf(stdout, "file[%d]->%s\n", i, 
                        m_pMergeImage->pngFileVec.at(i)->imageName.c_str());
        //each file min area
        fprintf(stdout, "AreaOfBigImage[%u, %u, %u, %u]\n",  
                        m_pMergeImage->bigImageArea.minTop, 
                        m_pMergeImage->bigImageArea.maxBottom,  
                        m_pMergeImage->bigImageArea.minLeft, 
                        m_pMergeImage->bigImageArea.maxRight);
        //big image width and height
        fprintf(stdout, "bigMergedImageWidHgt[%u, %u]\n",
                        m_pMergeImage->bigImageWid, 
                        m_pMergeImage->bigImageHgt);
    }


#endif
    
    return true; 
}

//copy all png file data to big image buf
bool MergePngTool::copyAllPngData2Buf()
{
    //first confirm big image size
    uint outputWid = this->m_pMergeImage->bigImageWid * this->m_pMergeImage->totalFrames;
    uint outputHgt = this->m_pMergeImage->bigImageHgt * this->m_pMergeImage->totalFrames;

    if (outputHgt == 0 || outputWid == 0)
    {
#if (DEBUG_OPEN)
        _debug("Image output size must not be 0!");
#endif
        return false;
    }
    
    //according big image reset buf size
    RESET_VEC_SIZE(this->m_mergedImageBuf, outputHgt * outputWid * 4);

    //get buffer handle pointer
    png_bytep bufHandlePtr = &this->m_mergedImageBuf[0];
    
    //start to write all data

    uint currHandleCol = 0;
    //traverse all png file
    for (std::vector<PngInfo *>::iterator iter = m_pMergeImage->pngFileVec.begin(); 
            iter != m_pMergeImage->pngFileVec.end(); iter++)
    {
        //use unit png size
        uint deltaH = 0;
        for (uint h = m_pMergeImage->bigImageArea.minTop; h < m_pMergeImage->bigImageArea.maxBottom; h++)
        {
            uint deltaW = 0;
            for (uint w = m_pMergeImage->bigImageArea.minLeft; w < m_pMergeImage->bigImageArea.maxRight; w++)
            {
                uint *imageSrcPtr = (uint *) ((*iter)->pixelData + h * (*iter)->width * 4 + w * 4);
                uint _dw = currHandleCol * m_pMergeImage->bigImageWid + deltaW;
                uint _dh = deltaH;
                uint *imageBuffPtr = (uint *)(bufHandlePtr + _dh * outputWid * 4 + _dw * 4);
                deltaW ++;
                *imageBuffPtr = *imageSrcPtr;
            }
            deltaH ++;
        }
        currHandleCol ++;
    }

    return true;
}

//write data to file with m_mergedImageBuf
bool MergePngTool::writeData2File(uint dstWid, uint dstHgt)
{
#if(DEBUG_OPEN)
    assert(m_pMergeImage != NULL);
#endif

    if (m_pMergeImage->mergedImageName.empty())
    {
        fprintf(stderr, "%s\n", "m_pMergeImage->mergedImageName must be set!");
        return false;
    }
    if (dstHgt == 0 || dstWid == 0)
    {
        fprintf(stderr, "%s\n", "Image output size must not be 0!");
        return false;
    }
    //pre declare with libpng

    uint wid = dstWid;
    uint hgt = dstHgt;
    FILE *wfp = NULL;
    png_structp pngPtr;
    png_infop infoPtr;

    //open file special with m_pMergeImage->mergedImageName
    if (!(wfp = fopen(m_pMergeImage->mergedImageName.c_str(), "wb")))
    {
        fprintf(stderr, "Open file [%s] error!\n", m_pMergeImage->mergedImageName.c_str());
        return false;
    }
    //inital png struct
    pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr)
    {
        fclose(wfp);
        fprintf(stderr, "%s\n", "Create png write struct error!");
        return false;
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr)
    {
        fclose(wfp);
        png_destroy_write_struct(&pngPtr, (png_infopp)NULL);
        fprintf(stderr, "%s\n", "Create png info struct error!");
        return false;
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        fclose(wfp);
        png_destroy_write_struct(&pngPtr, &infoPtr);
        fprintf(stderr, "%s\n", "Reading png file error!");
        return false;
    }

    //start to writing ...
    
    //inital read and write pointer
    png_init_io(pngPtr, wfp);

    //get pixel data for each pixel
    uint bytesPerPixel = 4; 
    
    //set IHDR
    png_set_IHDR(pngPtr, infoPtr, wid, hgt, 8, PNG_COLOR_TYPE_RGB_ALPHA,
		         PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    //write info
    png_write_info(pngPtr, infoPtr);
    //boundary check
    if (hgt > PNG_UINT_32_MAX/sizeof(png_bytep))
    {
		png_error(pngPtr, "Image is too large to prddocess in memory!");
        return false;
    }

    //row data buffer
    std::vector<BYTE> rowDataBuffer(wid * 4);
    //tmp png struct handle variable
    png_bytep rowDataBufPtr = &rowDataBufPtr[0];

    //src image buffer pointer
    unsigned char *srcDataBufPtr = &this->m_mergedImageBuf[0];

    //traversing data in imagebuffer
    for (uint h = 0; h < hgt; h++)
    {
        for (uint w = 0; w < wid; w++)
        {
            if (w > wid || h > hgt)
            {
                fclose(wfp);
                fprintf(stderr, "%s\n", "Out of image size bounday!");
                return false;
            }
            //get each row data
            unsigned char *rowTmp = srcDataBufPtr + h * wid * bytesPerPixel + w * bytesPerPixel;
            png_bytep dstTmp = rowDataBufPtr + w * 4;

            //copy data from src big image data
            if (bytesPerPixel == 4)//normal ARGB png format
            {
                dstTmp[0] = rowTmp[0];
                dstTmp[1] = rowTmp[1];
                dstTmp[2] = rowTmp[2];
                dstTmp[3] = rowTmp[3];
            }
        }
        //write row data 
        png_write_row(pngPtr, rowDataBufPtr);
    }
    //write completed
    png_write_end(pngPtr, infoPtr);
    
    //clean resource
    png_destroy_write_struct(&pngPtr, &infoPtr);
    fclose(wfp);

    return true;
}


//get file extension name, result in ext
void MergePngTool::getFileExtName(const char *fileName, char *ext)
{
#if (DEBUG_OPEN)
    assert(fileName);
#endif

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
        //have not extension name, ext set null
        strcpy(ext, "\0");
    }

#if (DEBUG_OPEN)
    _debug("File [%s] extension name is [%s]", fileName, ext);
#endif

}
