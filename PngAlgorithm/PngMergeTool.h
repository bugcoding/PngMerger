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
#include "PlistConfig.h"


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

    //split single png from large merged png file
    bool splitSinglePngFromMergedImage(std::string mergedImageName);


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
