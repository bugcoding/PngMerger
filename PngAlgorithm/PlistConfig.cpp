/*
#=============================================================================
#     FileName: PlistConfig.cpp
#         Desc: create plist with merge png implement
#       Author: bugcode
#        Email: bugcode@gmail.com
#     HomePage: http://bugcode.net
#      Version: 0.0.1
#   LastChange: 2014-11-30 20:27:31
#=============================================================================
*/

#include "PlistConfig.h"

//ctor with plist name
PlistConfig::PlistConfig(std::string plistName):
m_pDoc(NULL)
{
#if (DEBUG_MODE)
    _debug_print("Plist name [%s]", plistName.c_str());
#endif

    this->m_plistName = plistName;
}
//dtor
PlistConfig::~PlistConfig()
{
    //delloc BasePngPropt 
    for (uint i = 0; i < m_singlePngInfoVec.size(); i++)
    {
        BasePngPropt *bpp = (BasePngPropt *)m_singlePngInfoVec.at(i);
        delete bpp;
        bpp = NULL;
    }
    m_singlePngInfoVec.clear();

    //clean resource and delloc memory
    if (m_pDoc)
    {
        delete m_pDoc;
        m_pDoc = NULL;
    }
}

//create new file with base infomation
bool PlistConfig::createNewPlistWithBaseVec(std::vector<BasePngPropt *> baseVec, uint wid, uint hgt)
{
    //check m_plistName
    if (m_plistName.empty())
    {
       show_msg("m_plistName must be set");
        return false;
    }

    //base png must be have
    if (baseVec.size() < 1)
    {
        show_msg("baseVec must be have png info");
        return false;
    }
    //create new instance of XMLDocument to operate plist
    m_pDoc = new XMLDocument();
    if (!m_pDoc)
    {
        show_msg(" **** ALLOCATE MEMORY ERROR! ****");
        return false;
    }
    //start to writing
    
    //first, write to declaration
    XMLDeclaration *declaration = m_pDoc->NewDeclaration(XML_DELARATION);

    if (!declaration) 
    {
        show_msg("NewDeclaration error");
        return false;
    }
    m_pDoc->LinkEndChild(declaration);

    //plist doctype
    XMLElement *docTypeElement = m_pDoc->NewElement(XML_DOCTYPE);
    m_pDoc->InsertAfterChild(declaration, docTypeElement);


    //plist node
    XMLElement *plistElement = m_pDoc->NewElement(PLIST_NODE);
    if (!plistElement)
    {
        show_msg("NewElement for [PLIST NODE] error");
        return false;
    }
    
    //set plist attribution (version attr)
    plistElement->SetAttribute(PLIST_VER, "1.0");

    //closed plist node
    m_pDoc->LinkEndChild(plistElement);

    //dict node
    XMLElement *dictElement = m_pDoc->NewElement(DICT_NODE);
    if (!dictElement)
    {
        show_msg("NewElement for [DICT NODE] error");
        return false;
    }
    //closed dict node
    plistElement->LinkEndChild(dictElement);


    //write to "frames" key
    XMLElement *frameKey = m_pDoc->NewElement(KEY_NODE);
    if (!frameKey)
    {
        show_msg("NewElement for [KEY NODE error]");
        return false;
    }
    //<key>frames</key>
    frameKey->LinkEndChild(m_pDoc->NewText(FRAME_TEXT));

    //closed dict node for frames key
    dictElement->LinkEndChild(frameKey);

    //dict under the frames key
    XMLElement *dictUnderFrameKey = m_pDoc->NewElement(DICT_NODE);
    if (!dictUnderFrameKey)
    {
        show_msg("NewElement for [DICT NODE] error");
        return false;
    } 
    
    //closed node under the framkey
    dictElement->LinkEndChild(dictUnderFrameKey);

    /*
     * write to all single png file info with circle, 
     * under all node LinkEndChild with *dictUnderFrameKey*
     */
    for (uint i = 0; i < baseVec.size(); i++) 
    {
        BasePngPropt *bpp = (BasePngPropt *)baseVec.at(i);
        if (bpp)
        {
            //create all single png infomation
            this->writePlistDetailElement(dictUnderFrameKey, bpp);
        }
    }

    //finally metadata node belongs dictElement
    XMLElement *metadataKey = m_pDoc->NewElement(KEY_NODE);
    if (!metadataKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    metadataKey->LinkEndChild(m_pDoc->NewText(METADATA_KEY));
    dictElement->LinkEndChild(metadataKey);
    //create dict node under the metadataKey
    
    XMLElement *metadataDict = m_pDoc->NewElement(DICT_NODE);
    if (!metadataDict)
    {
        show_msg("NewElement for [DICT NODE] error");
        return false;
    }
    //belongs dictElement
    dictElement->LinkEndChild(metadataDict);
    //format key
    XMLElement *formatKey = m_pDoc->NewElement(KEY_NODE);
    if (!formatKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    formatKey->LinkEndChild(m_pDoc->NewText("format"));
    //under the metadataDict
    metadataDict->LinkEndChild(formatKey);
    //format value
    XMLElement *formatValue = m_pDoc->NewElement(INT_NODE); 
    if (!formatValue)
    {
        show_msg("NewElement for [INT NODE] error");
        return false;
    }
    formatValue->LinkEndChild(m_pDoc->NewText("2"));//default value == 2
    metadataDict->LinkEndChild(formatValue);

    //real texture file name key
    XMLElement *realTexureNameKey = m_pDoc->NewElement(KEY_NODE);
    if (!realTexureNameKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    realTexureNameKey->LinkEndChild(m_pDoc->NewText("realTextureFileName"));
    metadataDict->LinkEndChild(realTexureNameKey);

    //realTextureFileName value
    XMLElement *realTexureNameValue = m_pDoc->NewElement(STRING_NODE);
    if (!realTexureNameValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    }
    realTexureNameValue->LinkEndChild(m_pDoc->NewText(m_plistName.c_str()));
    metadataDict->LinkEndChild(realTexureNameValue);
    
    //size key
    XMLElement *sizeKey = m_pDoc->NewElement(KEY_NODE);
    if (!sizeKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    sizeKey->LinkEndChild(m_pDoc->NewText("size"));
    metadataDict->LinkEndChild(sizeKey);

    //size Value
    XMLElement *sizeValue = m_pDoc->NewElement(STRING_NODE);
    if (!sizeValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    }

    char largeImageSize[32] = "\0";
    sprintf(largeImageSize, "{%u,%u}", wid, hgt);

    sizeValue->LinkEndChild(m_pDoc->NewText(largeImageSize));
    metadataDict->LinkEndChild(sizeValue);

    //textureFileName key
    XMLElement *textureNameKey = m_pDoc->NewElement(KEY_NODE);
    if (!textureNameKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    textureNameKey->LinkEndChild(m_pDoc->NewText("textureFileName"));
    metadataDict->LinkEndChild(textureNameKey);

    //textureName Value
    XMLElement *textureNameValue = m_pDoc->NewElement(STRING_NODE);
    if (!textureNameValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    }
    textureNameValue->LinkEndChild(m_pDoc->NewText(m_plistName.c_str()));
    metadataDict->LinkEndChild(textureNameValue);


    //construct plist file name
    std::string plistFileName = this->getPlistFileName(m_plistName);

    //save data to file return 0 indicate success
    bool isSuccess = m_pDoc->SaveFile(plistFileName.c_str());

#if (DEBUG_MODE)
    //output plist file content
    m_pDoc->Print();
#endif

    return !isSuccess;
}

std::string PlistConfig::getPlistFileName(std::string pngfileName)
{
    //construct plist file name
    std::string plistFileName(pngfileName);
    std::string::size_type pos = plistFileName.find_last_of('.');
    if (pos != std::string::npos)
    {
        plistFileName = plistFileName.substr(0, pos + 1);
        plistFileName += PLIST_EXT_NAME;
    } 
    return plistFileName;
}

//single png info writing, called from PngMergeTool circle
bool PlistConfig::writePlistDetailElement(XMLElement *dictElement, BasePngPropt *basePngInfo)
{
    //check parmater
    if (!basePngInfo || !dictElement)
    {
        show_msg("BasePngPropt | XMLElement must be set");
        return false;
    }
    
    //single png info
    XMLElement *singlePngNamekey = m_pDoc->NewElement(KEY_NODE);
    if (!singlePngNamekey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    
    //get file name without path
    std::string path = basePngInfo->pngfileName;
    std::string::size_type pos = path.find_last_of(FILE_SEP);
    if (pos != std::string::npos)
    {
        path = path.substr(pos + 1, path.size());
    }

    singlePngNamekey->LinkEndChild(m_pDoc->NewText(path.c_str()));
    dictElement->LinkEndChild(singlePngNamekey);
    
    //detail png info with dict
    XMLElement *detailInfoDict = m_pDoc->NewElement(DICT_NODE);
    if (!detailInfoDict)
    {
        show_msg("NewElement for [DICT NODE] error");
        return false;
    }
    dictElement->LinkEndChild(detailInfoDict);

    //under this line, all png detail info with LinkEndChild -> detailInfoDict
    XMLElement *singleFrameKey = m_pDoc->NewElement(KEY_NODE);
    if (!singleFrameKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    singleFrameKey->LinkEndChild(m_pDoc->NewText("frame"));
    detailInfoDict->LinkEndChild(singleFrameKey);

    //frame value
    XMLElement *singleFrameValue = m_pDoc->NewElement(STRING_NODE);
    if (!singleFrameValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    } 

    char frameArea[32] = "\0";
    sprintf(frameArea, "{{%u,%u},{%u,%u}}", basePngInfo->offsetX, basePngInfo->offsetY
                                            ,basePngInfo->wid, basePngInfo->hgt);

    singleFrameValue->LinkEndChild(m_pDoc->NewText(frameArea));
    detailInfoDict->LinkEndChild(singleFrameValue);

    //offset key
    XMLElement *offsetKey = m_pDoc->NewElement(KEY_NODE);
    if (!offsetKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    offsetKey->LinkEndChild(m_pDoc->NewText("offset"));
    detailInfoDict->LinkEndChild(offsetKey);

    //offset value
    XMLElement *offsetValue = m_pDoc->NewElement(STRING_NODE);
    if (!offsetValue)
    {
        show_msg("NewElement for [STRING NODE] error"); 
        return false;
    }

    char offset[32] = "\0";
    //single self
    sprintf(offset, "{%u,%u}", 0, 0);

    offsetValue->LinkEndChild(m_pDoc->NewText(offset));
    detailInfoDict->LinkEndChild(offsetValue);

    //rotation 
    //
    // add later
    //
    //ratation

    //sourceColorRect key
    XMLElement *sourceColorRectKey = m_pDoc->NewElement(KEY_NODE);
    if (!sourceColorRectKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }
    sourceColorRectKey->LinkEndChild(m_pDoc->NewText("sourceColorRect"));
    detailInfoDict->LinkEndChild(sourceColorRectKey);

    //sourceColorRect value
    XMLElement *sourceColorRectValue = m_pDoc->NewElement(STRING_NODE);
    if (!sourceColorRectValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    }
    
    sprintf(frameArea, "{{%u,%u},{%u,%u}}", 0, 0, basePngInfo->wid, basePngInfo->hgt);

    sourceColorRectValue->LinkEndChild(m_pDoc->NewText(frameArea));
    detailInfoDict->LinkEndChild(sourceColorRectValue);

    //sourceSize key
    XMLElement *sourceSizeKey = m_pDoc->NewElement(KEY_NODE);
    if (!sourceSizeKey)
    {
        show_msg("NewElement for [KEY NODE] error");
        return false;
    }

    sourceSizeKey->LinkEndChild(m_pDoc->NewText("sourceSize"));
    detailInfoDict->LinkEndChild(sourceSizeKey);

    //sourceSize value
    XMLElement *sourceSizeValue = m_pDoc->NewElement(STRING_NODE);
    if (!sourceSizeValue)
    {
        show_msg("NewElement for [STRING NODE] error");
        return false;
    } 

    char sourceSize[32] = "\0";
    sprintf(sourceSize, "{%u,%u}", basePngInfo->wid, basePngInfo->hgt);

    sourceSizeValue->LinkEndChild(m_pDoc->NewText(sourceSize));
    detailInfoDict->LinkEndChild(sourceSizeValue);

    return true; 
}

//parse plist file and read single png file info to vector
bool PlistConfig::readPlistToSplitImage()
{
    //temp var for sourceSize, pngfileName, offset
    int offsetX = -1, offsetY = -1;
    int wid = -1, hgt = -1;
     std::string singlePngName;

    //check plist file name
    if (m_plistName.empty())
    {
        show_msg("m_plistName must be set to read infomation");
        return false;
    }

    //new instance of XMLDocument
    m_pDoc = new XMLDocument();
    if (!m_pDoc)
    {
        show_msg(" **** ALLOCATE MEMORY FAILED ***");
        return false;
    }
    //load plist file
    XMLError errorId = m_pDoc->LoadFile((this->getPlistFileName(m_plistName)).c_str());
    if (errorId)
    {
        show_msg("Load plist file error");
        return false;
    }

    //get root node
    XMLElement *rootNode = m_pDoc->RootElement();
    if (!rootNode)
    {
        show_msg("Root node is NULL");
        return false;
    }
    //get first dict node
    XMLElement *dictElement = rootNode->FirstChildElement(DICT_NODE);
    if (!dictElement)
    {
        show_msg("First dict is NULL");
        return false;
    }
    //get key of "frames"
    XMLElement *framekey = dictElement->FirstChildElement(KEY_NODE);
    if (!framekey)
    {
        show_msg("First key is NULL");
        return false;
    }



    //get dict of 'frames'
    XMLElement *underFramesDict = dictElement->FirstChildElement(DICT_NODE);
    if (!underFramesDict)
    {
        show_msg("underFramesDict is NULL");
        return false;
    }

#if (DEBUG_MODE)
show_msg("-----------------------------metadata_BGN---------------------------------------");
#endif

    XMLElement *metadataKey = framekey->NextSiblingElement(KEY_NODE);
    if (!metadataKey)
    {
        show_msg("metadataKey is NULL");
        return false;
    }

    //read matadata infomation
    if (!strcmp(metadataKey->GetText(), "metadata"))
    {
        XMLElement *metadataDict = underFramesDict->NextSiblingElement(DICT_NODE);
        if (!metadataDict)
        {
            show_msg("metadataDict is NULL");
            return false;
        }

        //parse info under the metadata dict node
        XMLElement *subKeyofMetadataDict = metadataDict->FirstChildElement(KEY_NODE);
        if (!subKeyofMetadataDict)
        {
            show_msg("subKeyofMetadataDict is NULL");
            return false;
        }
        XMLElement *subStringofMetadataDict = metadataDict->FirstChildElement(STRING_NODE);
        if (!subStringofMetadataDict)
        {
            show_msg("subStringofMetadataDict is NULL");
            return false;
        }

        //handle integer key
        if (!strcmp(subKeyofMetadataDict->GetText(), "format"))
        {
            XMLElement *subIntegerOfMetadataDict = metadataDict->FirstChildElement(INT_NODE);
            if (!subIntegerOfMetadataDict)
            {
                show_msg("subIntegerOfMetadataDict is NULL");
                return false;
            }
            std::string format(subIntegerOfMetadataDict->GetText());
            show_msg("format = %s", format.c_str());

            //read this integer and skil the integer key
            subKeyofMetadataDict = subKeyofMetadataDict->NextSiblingElement(KEY_NODE);
        }

        //traversing all metadata dict info
        while (subKeyofMetadataDict && subStringofMetadataDict)
        {
            if (!strcmp(subKeyofMetadataDict->GetText(), "realTextureFileName"))
            {
                std::string realFileName(subStringofMetadataDict->GetText());

                show_msg("realFileName = %s", realFileName.c_str());
            }
            else if (!strcmp(subKeyofMetadataDict->GetText(), "size"))
            {
                std::string realSize(subStringofMetadataDict->GetText());

                show_msg("realSize = %s", realSize.c_str());
            }
            else if (!strcmp(subKeyofMetadataDict->GetText(), "textureFileName"))
            {
                std::string textureName(subStringofMetadataDict->GetText());

                show_msg("textureName = %s", textureName.c_str());

                if (strcmp(textureName.c_str(), m_plistName.c_str()))
                {
                    show_msg("Not same plist file");
                    return false;
                }
            }

            //get next
            subKeyofMetadataDict = subKeyofMetadataDict->NextSiblingElement(KEY_NODE);
            subStringofMetadataDict = subStringofMetadataDict->NextSiblingElement(STRING_NODE);
        }
    }

#if (DEBUG_MODE)
show_msg("-----------------------------metadata_END---------------------------------------");



show_msg("-----------------------------every single png info_BGN--------------------------");
#endif

    //handle each key under the 'frames' , current <key>xxx.png</key>
    XMLElement *subKeyNodeUnderFrames = underFramesDict->FirstChildElement(KEY_NODE);
    if (!subKeyNodeUnderFrames)
    {
        show_msg("subKeyNodeUnderFrames is NULL");
        return false;
    }

    //get every dict belongs subKeyNodeUnderFrames
    XMLElement *subDictOfFrames = underFramesDict->FirstChildElement(DICT_NODE);
    if (!subDictOfFrames)
    {
        show_msg("subDictOfFrames is NULL");
    }

    //traversing all key under 'frame'
    while (subKeyNodeUnderFrames && subDictOfFrames)
    {
        //according to subKeyNodeUnderFrames, get single png file name
        singlePngName = subKeyNodeUnderFrames->GetText();


        //get info from subDictOfFrames
        XMLElement *keyOfFinalDict = subDictOfFrames->FirstChildElement(KEY_NODE);
        if (!keyOfFinalDict)
        {
            show_msg("keyOfFinalDict is NULL");
            return false;
        }
        XMLElement *stringOfFinalDict = subDictOfFrames->FirstChildElement(STRING_NODE);
        if (!stringOfFinalDict)
        {
            show_msg("stringOfFinalDict is NULL");
            return false;
        }
        while (keyOfFinalDict && stringOfFinalDict)
        {

            //get frame rect of single png file
            if (!strcmp(keyOfFinalDict->GetText(), "frame"))
            {
                //get string from stringOfFinalDict is frame rect info
                std::string frameRectString(stringOfFinalDict->GetText());

                show_msg("frameRectString = %s", frameRectString.c_str());
                //set offsetX, offsetY
                sscanf(frameRectString.c_str(), "{{%u,%u},{0,0}}", &offsetX, &offsetY);
            }
            else if (!strcmp(keyOfFinalDict->GetText(), "offset"))
            {
                //get string from stringOfFinalDict is png offset info
                std::string frameOffsetString(stringOfFinalDict->GetText());
                
                show_msg("frameOffsetString = %s", frameOffsetString.c_str());


            }
            else if (!strcmp(keyOfFinalDict->GetText(), "sourceColorRect"))
            {
                //get string from stringOfFinalDict is png rect info
                std::string frameColorRectString(stringOfFinalDict->GetText());

                show_msg("frameColorRectString = %s", frameColorRectString.c_str());
            }
            else if (!strcmp(keyOfFinalDict->GetText(), "sourceSize"))
            {
                //get string from stringOfFinalDict is size info
                std::string frameSrcSizeString(stringOfFinalDict->GetText());

                show_msg("frameSrcSizeString = %s", frameSrcSizeString.c_str());
                //set wid and hgt
                sscanf(frameSrcSizeString.c_str(), "{%u,%u}", &wid, &hgt);
            }
            else //something else
            {
                //error
                show_msg("keyOfFinalDict->GetText() == %s, stringOfFinalDict->GetText() == %s", 
                            keyOfFinalDict->GetText(), stringOfFinalDict->GetText());

                return false;
            }

            //find next
            keyOfFinalDict = keyOfFinalDict->NextSiblingElement(KEY_NODE);
            stringOfFinalDict = stringOfFinalDict->NextSiblingElement(STRING_NODE);
        }

        //single png file info [BasePngPropt]
        BasePngPropt *baseInfo = new BasePngPropt();

        baseInfo->pngfileName = singlePngName;
        baseInfo->wid = wid;
        baseInfo->hgt = hgt;
        baseInfo->offsetX = offsetX;
        baseInfo->offsetY = offsetY;

#if (DEBUG_MODE)
        _debug_print("wid=[%u], hgt=[%u], offsetX=[%u], offsetY=[%u]", 
                     wid, hgt, offsetX, offsetY);
#endif
        
        m_singlePngInfoVec.push_back(baseInfo);
#if (DEBUG_MODE)
        _debug_print("m_singlePngInfoVec.size=[%u]", m_singlePngInfoVec.size());
#endif


        //get next node of key
        subKeyNodeUnderFrames = subKeyNodeUnderFrames->NextSiblingElement(KEY_NODE);
        //get next node of dict
        subDictOfFrames = subDictOfFrames->NextSiblingElement(DICT_NODE);
    }
#if (DEBUG_MODE)
show_msg("-----------------------------every single png info_END--------------------------");
#endif


    return true;    
}

//return BasePngPropt in m_singlePngInfoVec
BasePngPropt *PlistConfig::getSingleBasePngPropt(uint index)
{
    if (index >= m_singlePngInfoVec.size())
    {
        show_msg("Index[%u] out of m_singlePngInfoVec boundary", index);
        return NULL;
    }
    return (BasePngPropt *)m_singlePngInfoVec.at(index);
}
