

#include "wx/fileconf.h"

//data file type (cocos2d .. etc)
typedef enum datafiletype
{
    COCOS2D = 0,//cocos2d for default
    OTHERS    = 1 //others
}DATA_TYPE;

//local config file
#define LOCAL_CONF_NAME         "config.conf"
//application name
#define APP_NAME                "PngMerger"

//some setting key name
#define SETTING_KEY_DATA_FMT            "datafmt"
#define SETTING_KEY_TEXTURE_FMT         "texturefmt"
#define SETTING_KEY_IMAGE_FMT           "imagefmt"
#define SETTING_KEY_BDR_PADDING         "borderpadding"
#define SETTING_KEY_SPE_PADDING         "shapepadding"
#define SETTING_KEY_MAX_WID             "maxwid"
#define SETTING_KEY_MAX_HGT             "maxhgt"
//setting name above


//struct of setting string
typedef struct setting
{
    wxString datafmt;
    wxString texturefmt;
    wxString imagefmt;
    wxString borderpadding;
    wxString shapepadding;
    wxString maxwid, maxhgt;
} SETTING_FIELD;



//local config class
class PngMergerConf
{
public:
    PngMergerConf();
    ~PngMergerConf();

    //singleton
    static PngMergerConf *sharedInstance();
    void setDataType(DATA_TYPE dt);
    //overwrite Read for wxFileConfig
    bool readInfo(wxString key, wxString *value);
    //overwrite Write for wxFileConfig
    bool writeInfo(wxString key, wxString value);
    //check key is exist
    bool keyExist(wxString key);
    //read int value from local config file
    int readInt(wxString key, int defaultval = -1);

    //write to setting with datatype
    bool writeSetting(SETTING_FIELD *setting);
    //delete all key and value in local config file
    bool deleteSavedSetting();


private:
    //cuurent data type
    DATA_TYPE m_dataType;
    //wxFileConfig instance
    wxFileConfig *m_fileConfig;
};
