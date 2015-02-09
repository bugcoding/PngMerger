/*
#=============================================================================
#     FileName: PngMergeTool.cpp
#         Desc: get directory all png file transform from PngUtils implement
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: bugcoding.net
#      Version: 0.0.1
#   LastChange: 2014-11-28 13:54:12
#=============================================================================
*/

#include "PngMergeTool.h"

//with dir name
PngMergeTool::PngMergeTool(std::string dirName)
{
#if DEBUG_MODE
    _debug_print("Directory name [%s]", dirName.c_str());
#endif
    this->m_dirName = dirName;
}

//dtor
PngMergeTool::~PngMergeTool()
{
    //resource clean
    for (std::vector<BasePngPropt *>::iterator iter = m_pBitmapVec.begin();
            iter != m_pBitmapVec.end(); iter++)
    {
        BasePngPropt *bppTmp = *iter;
#if DEBUG_MODE
    _debug_print("Delloc [%s] memory...", bppTmp->pngfileName.c_str());
#endif
        if (bppTmp->bitmapHandler)
        {
            //unload bitmap
            FreeImage_Unload(bppTmp->bitmapHandler);
            bppTmp->bitmapHandler = NULL;
        }
        delete bppTmp;
        bppTmp = NULL;
    }
    m_pBitmapVec.clear();

}

//get all png file from directory
bool PngMergeTool::getAndReadAllImage()
{
    //not set value to dirName, return directly
    if (m_dirName.empty())
    {
        show_msg("m_dirName must be set");
        return false;
    }
    //list file in directory
    //extName var
    char extName[128] = "\0";


//list directory file under win32
#if (defined(_WIN32) || defined(WIN32) || defined(_win32))
    //file info struct
    WIN32_FIND_DATA fileData;
    //handle find file
    HANDLE fileFound = INVALID_HANDLE_VALUE;//default value

    std::string regex = m_dirName + "\\*";
    //remember flags for read file with extension name 'ext'
    bool isRead = false;

    //start traversing
    fileFound = FindFirstFile(regex.c_str(), &fileData);
    //file not found
    if (INVALID_HANDLE_VALUE == fileFound)
    {
        show_msg("File [%s] not found!", m_dirName.c_str());
        return false;
    }

    //list file
    do
    {
        //check is file or not
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
#if DEBUG_MODE
            _debug_print("File name [%s]", fileData.cFileName);
#endif
            //is not a dir and get file ext name
            this->getFileExtName(fileData.cFileName, extName);

            //judge ext name
            if (!strcmp(extName, EXT_NAME))
            {
                //construct file real path
                std::string filePath = m_dirName + FILE_SEP + fileData.cFileName;

#if DEBUG_MODE
        _debug_print("Filepath [%s]", filePath.c_str());
#endif
                //parse png with PngUtils
                PngUtils *pu = new PngUtils(filePath);

                //put value to vector
                this->m_pBitmapVec.push_back(pu->getPnginfo());
                //set reading state
                isRead = true;

                delete pu;
            }
        }
        else
        {
#if DEBUG_MODE
            _debug_print("%s is directory", fileData.cFileName);
#endif
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
    if (!(tmpDir = opendir(m_dirName.c_str())))
    {
#if (DEBUG_OPEN)
        _debug_print("Open directory[%s] error!", m_dirName.c_str());
#endif
        return false;
    }


    //traversing all file under the dir
    while ((files = readdir(tmpDir)))
    {
        //get file real path for absolutly
        std::string filePath = m_dirName + FILE_SEP + files->d_name;

        //check file state if error out , continue
        if (lstat(filePath.c_str(), &fileState) < 0)
        {
#if (DEBUG_OPEN)
            _debug_print("File [%s] state error!", filePath.c_str());
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
                //parse png with PngUtils
                PngUtils *pu = new PngUtils(filePath);

                //put value to vector
                this->m_pBitmapVec.push_back(pu->getPnginfo());

                //set flag for reading state
                isRead = true;

                delete pu;
           }
        }
    }

#endif

#if DEBUG_MODE
    _debug_print("Load all png data completed");
#endif

    return isRead;
}


//get file ext name
void PngMergeTool::getFileExtName(const char *fileName, char *ext)
{
#if (DEBUG_MODE)
    assert(fileName);
#endif

    char temp[256] = "\0";
    //get copy of fileName
    strcpy(temp, fileName);
    char *loc = strrchr(temp, EXT_SEPRETOR);

    //find dot location
    if (loc)
    {
        //for exp: get "file.ext" put "ext" to ext var
        strcpy(ext, loc + 1);
    }
    else
    {
        //have not extension name, ext set null
        strcpy(ext, "\0");
    }

#if (DEBUG_OPEN)
    _debug_print("File [%s] extension name is [%s]", fileName, ext);
#endif

}


//testing print log funtion
void PngMergeTool::printVecInfo()
{
    for (uint i = 0; i < m_pBitmapVec.size(); i++)
    {
        BasePngPropt *temp = (BasePngPropt *)m_pBitmapVec.at(i);
        show_msg("%s => [%u, %u, %u, %u]\n",
                temp->pngfileName.c_str(), temp->wid,
                temp->hgt, temp->bpp, temp->clrType);
    }
}


uint PngMergeTool::mergeImages()
{
    //check vector of image FIBITMAP pointer
    if (m_pBitmapVec.size() < 1)
    {
        show_msg("Image data have be lost!");
        return false;
    }

    //create new large transparency
    FIBITMAP *largeBitmap = FreeImage_Allocate(WID_DEFAULT, HGT_DEFAULT, 32, 0, 0, 0);
    if (!largeBitmap)
    {
        show_msg("Create new image error");
        return false;
    }
    //init MaxRectsBinPack param
    rbp::MaxRectsBinPack mrbp;
    rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestLongSideFit;
    mrbp.Init(WID_DEFAULT, HGT_DEFAULT);

    //image count
    uint successCnt = 0;

    //traversing all image data
    for (std::vector<BasePngPropt *>::iterator iter = m_pBitmapVec.begin();
            iter != m_pBitmapVec.end(); iter++)
    {
        BasePngPropt *bppTmp = *iter;

        //compute image location
        rbp::Rect packRect = mrbp.Insert(bppTmp->wid, bppTmp->hgt, heuristic);
        //judge packRect boundary
        if (packRect.height > 0)
        {
            //set original image BasePngPropt offsetX and offsetY
            bppTmp->offsetX = packRect.x;
            bppTmp->offsetY = packRect.y;

            //put original image from vector to large image
            FIBITMAP *cutImage = FreeImage_Copy(bppTmp->bitmapHandler, 0, 0, bppTmp->wid, bppTmp->hgt);
            if (cutImage)
            {
                //from cutImage paste to large image
                bool success = FreeImage_Paste(largeBitmap, cutImage, packRect.x, packRect.y, 255);
                if (success)
                {
                    show_msg("[%s]>>%s\n", bppTmp->pngfileName.c_str(), "Fill to large image success");
                    //compute all image file count
                    successCnt++;
                }
            }
        }
    }

    //merge image end
    m_finalBitmap = largeBitmap;
    return successCnt;

}

//get m_finalBitmap
FIBITMAP *PngMergeTool::getBitmapPtr()
{
    return m_finalBitmap;
}

//from m_finalBitmap save to local file
bool PngMergeTool::save2Local(uint sucCnt)
{
    //all image file should be fill to large image
    if (sucCnt == m_pBitmapVec.size())
    {
        //contruct large image name with diretory name
        std::string largePngName = m_dirName + "." + EXT_NAME;

        //save success
        if (FreeImage_Save(FIF_PNG, m_finalBitmap, largePngName.c_str(), PNG_DEFAULT))
        {

            uint wid = FreeImage_GetWidth(m_finalBitmap);
            uint hgt = FreeImage_GetHeight(m_finalBitmap);

            show_msg("Save large image to [%s] success\n", largePngName.c_str());

            //after use FIBITMAP, unload it
            FreeImage_Unload(m_finalBitmap);

            PlistConfig *plistCreator = new PlistConfig(largePngName);
            //create plist file with merge info
            bool isCreateSuccess = plistCreator->createNewPlistWithBaseVec( m_pBitmapVec, wid, hgt);

            //test
            //plistCreator->readPlistToSplitImage();

            delete plistCreator;
            plistCreator = NULL;

            // write to plist failed
            if (!isCreateSuccess)
            {
                show_msg("Create plist failed for image [%s]", largePngName.c_str());
                return false;
            }

            return true;
        }
    }
    return false;

}


//split single png from large merged png file
bool PngMergeTool::splitSinglePngFromMergedImage(std::string mergedImageName)
{
    //check mergedImageName
    if (mergedImageName.empty())
    {
        show_msg("Merged image name must be special");
        return false;
    }

    PlistConfig *pc = new PlistConfig(mergedImageName);
    if (!pc)
    {
        show_msg("%s", "**** ALLOCATE MEMORY FAILED ****");
        return false;
    }
    bool readSuccess = pc->readPlistToSplitImage();
    if (!readSuccess)
    {
        show_msg("Read [%s] with plist failed", mergedImageName.c_str());
        delete pc;
        pc = NULL;
        return false;
    }

    FIBITMAP *mergedBitmap = FreeImage_Load(FIF_PNG, mergedImageName.c_str(), 0);
    if (!mergedBitmap)
    {
        show_msg("Read image [%s] failed", mergedImageName.c_str());
        delete pc;
        pc = NULL;
        return false;
    }

    uint count = pc->getSinlePngCount();
    for (uint i = 0; i < count; i++)
    {

        BasePngPropt *bpp = pc->getSingleBasePngPropt(i);

#if (DEBUG_MODE)
        _debug_print("wid=[%u], hgt=[%u], offsetX=[%u], offsetY=[%u]",
                     bpp->wid, bpp->hgt, bpp->offsetX, bpp->offsetY);
#endif


        FIBITMAP *singlePngData = FreeImage_Copy(mergedBitmap,
                                                bpp->offsetX, bpp->offsetY,
                                                bpp->offsetX + bpp->wid, bpp->offsetY + bpp->hgt);
        if (!singlePngData)
        {
            show_msg("Copy png data from mergedBitmap failed");
            delete pc;
            pc = NULL;
            return false;
        }

        //allocate new image
        FIBITMAP *singlePng = FreeImage_Allocate(bpp->wid, bpp->hgt, 32, 0, 0, 0);
        if (!singlePng)
        {
            show_msg("%s", "Allocate FIBITMAP failed");
            return false;
        }

        //paste new singlePngData to new image
         bool pasteSuccess = FreeImage_Paste(singlePng, singlePngData, 0, 0, 255);
         if (!pasteSuccess)
         {
             show_msg("Paste new image failed");
             delete pc;
             pc = NULL;
             FreeImage_Unload(singlePng);
             return false;
         }
        //save new image

        if (!FreeImage_Save(FIF_PNG, singlePng, bpp->pngfileName.c_str(), PNG_DEFAULT))
        {
            //error handle
            show_msg("Save file[%s] failed", bpp->pngfileName.c_str());
            delete pc;
            pc = NULL;
            FreeImage_Unload(singlePng);
            return false;
        }
        //tips
#if (DEBUG_MODE)
        _debug_print("[%d -> %s] - %s", i, bpp->pngfileName.c_str(), "Create single png file success");
#endif
        FreeImage_Unload(singlePng);
        singlePng = NULL;

    }
    delete pc;
    pc = NULL;
    return true;

}

//get png info vector

std::vector<BasePngPropt *> PngMergeTool::getInfoVec()
{
    return m_pBitmapVec;
}














/*
