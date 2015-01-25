#include "PngMergerConf.h"
#include "wx/fileconf.h"


PngMergerConf::PngMergerConf():
m_dataType(COCOS2D),
m_fileConfig(NULL)
{
    m_fileConfig = new wxFileConfig("PngMerger", wxEmptyString, wxGetCwd() + "/" + LOCAL_CONF_NAME,
                                    wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_GLOBAL_FILE);
    m_fileConfig->Flush();
}

PngMergerConf::~PngMergerConf()
{
    if (m_fileConfig)
    {
        delete m_fileConfig;
        m_fileConfig = NULL;
    }
}

static PngMergerConf *conf = NULL;

// shared instace for wxConfigFile handle
PngMergerConf * PngMergerConf::sharedInstance()
{
    if (!conf)
    {
        conf = new PngMergerConf();
    }
    return conf;
}
//set data file tyoe'
void PngMergerConf::setDataType(DATA_TYPE dt)
{
    m_dataType = dt;
}

//same as wxFileConfig Read
bool PngMergerConf::readInfo(wxString key, wxString *value)
{
    if (m_fileConfig)
    {
        return m_fileConfig->Read(key, value);
    }
    else
    {
        return false;
    }
}

//same as wxFileConfig Write
bool PngMergerConf::writeInfo(wxString key, wxString value)
{
    bool sus = false;
    if (m_fileConfig)
    {

        sus = m_fileConfig->Write(key, value);
        m_fileConfig->Flush();
    }
    return sus;
}

//same as wxFileBase Exist
bool PngMergerConf::keyExist(wxString key)
{
    if (m_fileConfig)
    {
        return m_fileConfig->Exists(key);
    }
    else
    {
        return false;
    }
}
//read int from local config file
int PngMergerConf::readInt(wxString key, int defaultval)
{
    if (m_fileConfig)
    {
        return (int)m_fileConfig->ReadLong(key, defaultval);
    }
    else
    {
        return defaultval;
    }
}

//same as wxFileConfig DeleteAll
bool PngMergerConf::deleteSavedSetting()
{
    if (m_fileConfig)
    {
        return m_fileConfig->DeleteAll();
    }
    else
    {
        return false;
    }
}


//write software setting info
bool PngMergerConf::writeSetting(SETTING_FIELD *setting)
{
    bool sus = false;
    if (setting)
    {
        sus = writeInfo(SETTING_KEY_DATA_FMT, setting->datafmt);
        sus = writeInfo(SETTING_KEY_TEXTURE_FMT, setting->texturefmt);
        sus = writeInfo(SETTING_KEY_IMAGE_FMT, setting->imagefmt);
        sus = writeInfo(SETTING_KEY_BDR_PADDING, setting->borderpadding);
        sus = writeInfo(SETTING_KEY_SPE_PADDING, setting->shapepadding);
        sus = writeInfo(SETTING_KEY_MAX_HGT, setting->maxhgt);
        sus = writeInfo(SETTING_KEY_MAX_WID, setting->maxwid);
    }
    else // set default value
    {
        sus = writeInfo(SETTING_KEY_DATA_FMT, "0");
        sus = writeInfo(SETTING_KEY_TEXTURE_FMT, "0");
        sus = writeInfo(SETTING_KEY_IMAGE_FMT, "0");
        sus = writeInfo(SETTING_KEY_BDR_PADDING, "0");
        sus = writeInfo(SETTING_KEY_SPE_PADDING, "0");
        sus = writeInfo(SETTING_KEY_MAX_HGT, "1");
        sus = writeInfo(SETTING_KEY_MAX_WID, "1"); 
    }
    return sus;
}


