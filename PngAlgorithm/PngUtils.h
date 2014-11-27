/*=============================================================================
#     FileName: PngUtils.h
#         Desc: single png file handler
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-11-27 22:52:45
=============================================================================*/

#ifndef _PNG_UTILS_H_

#define _PNG_UTILS_H_


#include <cstdio>
#include <cassert>
#include <iostream>

#include "FreeImage.h"

//debug infomation output macro control
#define DEBUG_MODE      1

//costmoze debug ouput macro
#define _debug_print(format, ...)    \
        printf("[Debug Info]: " format " >> func[%s] >> line[%d]\n"\
                            ,##__VA_ARGS__, __func__, __LINE__)


/* 
 * PngUtils Class
 *
 * use FreeImage API operate single png file
 * read, write, get some png file property etc..
 *
 */

class PngUtils
{
public:
    //default ctor
    PngUtils();
    /*
     * ctor with file name
     * @param : will handling png file's name 
     */
     PngUtils(std::string pngfileName);
    //dtor
    ~PngUtils();

    //get file name from Pngutils instance pointer
    std::string getPngfileName();

    /*
     * read png file special with m_pngfileName
     * and set png data to m_pBitmapHandler
     * @return read success return true, 
     *  conversely return false
     */
    bool getPnginfo();


private:
    //png file's name
    std::string m_pngfileName;
    //keep handle a FIBITMAP pointer
    FIBITMAP *m_pBitmapHandler;
};
