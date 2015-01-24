/*
#=============================================================================
#     FileName: PlistConfig.cpp
#         Desc: create plist with merge png header
#       Author: bugcode
#        Email: bugcode@gmail.com
#     HomePage: http://bugcode.net
#      Version: 0.0.1
#   LastChange: 2014-11-30 20:27:31
#=============================================================================
*/

#ifndef _PLIST_CONFIG_H_

#define _PLIST_CONFIG_H_

//for some macro and struct
#include "PngUtils.h"
#include "tinyxml2.h"


//base XML declaration
#define XML_DELARATION "xml version=\"1.0\" encoding=\"UTF-8\""
//DOCTYPE delaration
#define XML_DOCTYPE "!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\""
//plist node
#define PLIST_NODE  "plist"
//plist key
#define KEY_NODE    "key"
//plist dict
#define DICT_NODE   "dict"
//plist string
#define STRING_NODE "string"
//plist integer
#define INT_NODE    "integer"
//plist frames key
#define FRAME_TEXT  "frames"
//plist metadata key
#define METADATA_KEY "metadata"

//plist node base version info
#define PLIST_VER   "version"

//plist ext name
#define PLIST_EXT_NAME  "plist"

//for tinyxml2 class
using namespace tinyxml2;

/*
 * after merge png operate, need to record
 * merge infomation to plist file
 * use tinyxml2 write and read plist file
 */

class PlistConfig
{
public:
    //constructor with plist name
    PlistConfig(std::string plistName);
    //default destructor
    ~PlistConfig();
    
    // create new plist and write to all infomation
    bool createNewPlistWithBaseVec(std::vector<BasePngPropt *> baseVec, uint wid, uint hgt);

    /*
     * read plist file same name to 
     * large merge png file that 
     * special with m_plistName
     */
    bool readPlistToSplitImage();

    /*
     * return BasePngPropt info in m_singlePngInfoVec
     *
     * return BasePngPropt pointer
     */
    
    BasePngPropt *getSingleBasePngPropt(uint index);

    /*
     * get count of single png
     */
    inline uint getSinlePngCount()
    {
        return m_singlePngInfoVec.size();
    }

//private member function
private:

     /*
     * all element will be wrote
     * need BasePngPropt pointer
     * to get all single png base info
     */
    bool writePlistDetailElement(XMLElement *dictElement, BasePngPropt *basePngInfo);


    //get real plist name with '.plist'
    std::string getPlistFileName(std::string pngfileName);
    

//private member variable
private:
    //plist name
    std::string m_plistName;
    //XMLDoc instance
    XMLDocument *m_pDoc;
    
    //save all single png file info to vector
    std::vector<BasePngPropt *> m_singlePngInfoVec;
};



#endif
