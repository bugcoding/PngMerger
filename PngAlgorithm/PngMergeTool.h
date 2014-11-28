/*
#=============================================================================
#     FileName: PngMergeTool.h
#         Desc: get directory all png file transform from PngUtils
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: bugcoding.net
#      Version: 0.0.1
#   LastChange: 2014-11-28 13:54:12
#=============================================================================
*/

#ifndef _PNG_MERGE_TOOL_H_

#define _PNG_MERGE_TOOL_H_

//for using PngUtil class
#include "PngUtils.h"
#include "MaxRectsBinPack.h"

#if (defined(_WIN32) || defined(WIN32) || defined(_win32))

    //file handling on win32 system
    #include <windows.h>

#elif (defined(_LINUX) || defined(__APPLE__) || defined(__MACOSX__)) 

    //file handing api on like UNIX system
    #include <sys/types.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>

#endif

//need focus file extension name
#define EXT_NAME            "png"
//sperator for extension name "."
#define EXT_SEPRETOR        '.'
//path sepretor
#define FILE_SEP            "/"


/*
 * PngMergeTool Class
 *
 * list image file directory,get all png file
 with PntUtil handle each single png file
 * merge all small png that under the special 
 * directory to large png
 */

class PngMergeTool
{
//public member function
public:
    //default comstructor
    PngMergeTool();
    //constructor with directory
    PngMergeTool(std::string dirName);
    //dtor
    ~PngMergeTool();

    /*
     * Load all png that special with m_dirName
     * read png info to FIBITMAP and put it to
     * m_pBitmapVec
     *
     * @return true indicate to read all png to vector
     *  error come out when false will be returned
     */
    bool getAndReadAllImage();

    /*
     * merge images data from that read into m_pBitmapVec
     * use MaxRects algorithm [MaxRectBinPack ] from
     * https://github.com/juj/RectangleBinPack
     * @return true indicate merge success
     *         false indicate merge failed 
     */
    bool mergeImages();


    //temp testing
    void printVecInfo();

//private member function
private:
    //get file extension name
    void getFileExtName(const char *fileName, char *ext);

//private member variable
private:
    //current operating directory
    std::string m_dirName;
    //keep all BasePngPropt pointer what get from PngUtils
    std::vector<BasePngPropt *>m_pBitmapVec;

};


#endif
