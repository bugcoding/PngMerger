/***************************************************************
 * Name:      PngMergerGUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    bugcode (bugcoding@gmail.com)
 * Created:   2014-12-02
 * Copyright: bugcode (bugcode.net)
 * License:
 **************************************************************/

#include "PngMergerGUIMain.h"
#include <wx/msgdlg.h>


//(*InternalHeaders(PngMergerGUIFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "wx/filename.h"
#include "wx/log.h"
#include "wx/choicdlg.h"
#include "wx/imaglist.h"
#include "wx/fileconf.h"
#include "wx/filefn.h"
#include "wx/msgout.h"
#include "wx/scrolwin.h"
#include "wx/dirdlg.h"
#include "PngAlgorithm/PngUtils.h"
#include "PngAlgorithm/PngMergeTool.h"

#if wxUSE_FILEDLG
#include "wx/filedlg.h"
#endif // wxUSE_FILEDLG


//debug output
#define dbg_print(args)             wxMessageOutputDebug().Printf(args)

//listview icon width and height
#define ICON_WID        32
#define ICON_HGT        32



//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PngMergerGUIFrame)
const long PngMergerGUIFrame::ID_STATICBOX1 = wxNewId();
const long PngMergerGUIFrame::ID_CHOICE1 = wxNewId();
const long PngMergerGUIFrame::ID_CHOICE3 = wxNewId();
const long PngMergerGUIFrame::ID_CHOICE4 = wxNewId();
const long PngMergerGUIFrame::ID_CHOICE5 = wxNewId();
const long PngMergerGUIFrame::ID_CHOICE2 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT2 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT3 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT4 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT5 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT6 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT7 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT8 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT9 = wxNewId();
const long PngMergerGUIFrame::ID_STATICTEXT1 = wxNewId();
const long PngMergerGUIFrame::ID_TEXTCTRL2 = wxNewId();
const long PngMergerGUIFrame::ID_TEXTCTRL1 = wxNewId();
const long PngMergerGUIFrame::ID_BUTTON2 = wxNewId();
const long PngMergerGUIFrame::ID_BUTTON1 = wxNewId();
const long PngMergerGUIFrame::ID_STATICLINE2 = wxNewId();
const long PngMergerGUIFrame::ID_SPINCTRL2 = wxNewId();
const long PngMergerGUIFrame::ID_SPINCTRL3 = wxNewId();
const long PngMergerGUIFrame::ID_PANEL1 = wxNewId();
const long PngMergerGUIFrame::ID_STATICLINE1 = wxNewId();
const long PngMergerGUIFrame::ID_STATICBITMAP1 = wxNewId();
const long PngMergerGUIFrame::ID_PANEL2 = wxNewId();
const long PngMergerGUIFrame::ID_LISTVIEW1 = wxNewId();
const long PngMergerGUIFrame::ID_MENUITEM1 = wxNewId();
const long PngMergerGUIFrame::ID_MENUITEM2 = wxNewId();
const long PngMergerGUIFrame::idMenuQuit = wxNewId();
const long PngMergerGUIFrame::ID_MENUITEM5 = wxNewId();
const long PngMergerGUIFrame::ID_MENUITEM3 = wxNewId();
const long PngMergerGUIFrame::ID_MENUITEM4 = wxNewId();
const long PngMergerGUIFrame::idMenuAbout = wxNewId();
const long PngMergerGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PngMergerGUIFrame,wxFrame)
    //(*EventTable(PngMergerGUIFrame)
    //*)
END_EVENT_TABLE()

PngMergerGUIFrame::PngMergerGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(PngMergerGUIFrame)
    wxMenuBar* homeMenuBar;
    wxMenu* fileOpMenu;
    wxMenuItem* aboutMenuItem;
    wxMenu* helpMenu;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenuItem* quitMenuItem;

    Create(parent, wxID_ANY, _("PngMerger"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1383,675));
    SetMinSize(wxSize(1380,700));
    SetMaxSize(wxSize(1393,705));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("D:\\github\\pngmerger\\PngMergerGUI\\pngmerger.ico"))));
    	SetIcon(FrameIcon);
    }
    FlexGridSizer1 = new wxFlexGridSizer(4, 4, wxDLG_UNIT(this,wxSize(0,0)).GetWidth(), wxDLG_UNIT(this,wxSize(0,0)).GetWidth());
    leftPanel = new wxScrolledWindow(this, ID_PANEL1, wxDefaultPosition, wxSize(321,628), wxTAB_TRAVERSAL|wxVSCROLL|wxHSCROLL, _T("ID_PANEL1"));
    settingStaticBox = new wxStaticBox(leftPanel, ID_STATICBOX1, _("Setting"), wxPoint(0,5), wxSize(303,850), 0, _T("ID_STATICBOX1"));
    dataFmtChoice = new wxChoice(leftPanel, ID_CHOICE1, wxPoint(130,40), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    dataFmtChoice->Append(_("Cocos2d"));
    dataFmtChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    textureFmtChoice = new wxChoice(leftPanel, ID_CHOICE3, wxPoint(130,104), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    textureFmtChoice->Append(_("Png (.png)"));
    textureFmtChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    imageChoice = new wxChoice(leftPanel, ID_CHOICE4, wxPoint(130,136), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    imageChoice->Append(_("RGBA"));
    imageChoice->Append(_("RGBA8888"));
    imageChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    maxWidChoice = new wxChoice(leftPanel, ID_CHOICE5, wxPoint(144,288), wxSize(128,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    maxWidChoice->Append(_("2048"));
    maxWidChoice->Append(_("1024"));
    maxWidChoice->Append(_("512"));
    maxWidChoice->Append(_("256"));
    maxWidChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    maxHgtChoice = new wxChoice(leftPanel, ID_CHOICE2, wxPoint(144,320), wxSize(128,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    maxHgtChoice->Append(_("2048"));
    maxHgtChoice->Append(_("1024"));
    maxHgtChoice->Append(_("512"));
    maxHgtChoice->Append(_("256"));
    maxHgtChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    dataFmtLabel = new wxStaticText(leftPanel, ID_STATICTEXT2, _("Data Format"), wxPoint(24,42), wxSize(68,32), 0, _T("ID_STATICTEXT2"));
    wxFont dataFmtLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    dataFmtLabel->SetFont(dataFmtLabelFont);
    datafileLabel = new wxStaticText(leftPanel, ID_STATICTEXT3, _("Data File"), wxPoint(24,74), wxSize(88,17), 0, _T("ID_STATICTEXT3"));
    wxFont datafileLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    datafileLabel->SetFont(datafileLabelFont);
    textureFmtLabel = new wxStaticText(leftPanel, ID_STATICTEXT4, _("Texture Format"), wxPoint(24,106), wxSize(88,17), 0, _T("ID_STATICTEXT4"));
    wxFont textureFmtLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    textureFmtLabel->SetFont(textureFmtLabelFont);
    imageFmtLabel = new wxStaticText(leftPanel, ID_STATICTEXT5, _("Image Format"), wxPoint(24,138), wxSize(88,17), 0, _T("ID_STATICTEXT5"));
    wxFont imageFmtLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    imageFmtLabel->SetFont(imageFmtLabelFont);
    textureFileLabel = new wxStaticText(leftPanel, ID_STATICTEXT6, _("Texture File"), wxPoint(24,170), wxSize(88,17), 0, _T("ID_STATICTEXT6"));
    wxFont textureFileLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    textureFileLabel->SetFont(textureFileLabelFont);
    borderPadLabel = new wxStaticText(leftPanel, ID_STATICTEXT7, _("Border Padding"), wxPoint(24,223), wxSize(88,17), 0, _T("ID_STATICTEXT7"));
    wxFont borderPadLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    borderPadLabel->SetFont(borderPadLabelFont);
    shapePadLabel = new wxStaticText(leftPanel, ID_STATICTEXT8, _("Shape Padding"), wxPoint(24,256), wxSize(88,17), 0, _T("ID_STATICTEXT8"));
    wxFont shapePadLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    shapePadLabel->SetFont(shapePadLabelFont);
    maxWidLbl = new wxStaticText(leftPanel, ID_STATICTEXT9, _("Max Width"), wxPoint(24,289), wxSize(88,17), 0, _T("ID_STATICTEXT9"));
    wxFont maxWidLblFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    maxWidLbl->SetFont(maxWidLblFont);
    maxHgtLabel = new wxStaticText(leftPanel, ID_STATICTEXT1, _("Max Height"), wxPoint(24,321), wxSize(88,17), 0, _T("ID_STATICTEXT1"));
    wxFont maxHgtLabelFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    maxHgtLabel->SetFont(maxHgtLabelFont);
    datafilePathText = new wxTextCtrl(leftPanel, ID_TEXTCTRL2, _("Data File Path..."), wxPoint(130,72), wxSize(104,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    datafilePathText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    textureFilePathText = new wxTextCtrl(leftPanel, ID_TEXTCTRL1, _("Texture File Path..."), wxPoint(130,168), wxSize(104,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    textureFilePathText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    dataFileLocButton = new wxButton(leftPanel, ID_BUTTON2, _("..."), wxPoint(242,72), wxSize(32,22), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    textureFileLocButton = new wxButton(leftPanel, ID_BUTTON1, _("..."), wxPoint(242,168), wxSize(32,22), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    setting1Line = new wxStaticLine(leftPanel, ID_STATICLINE2, wxPoint(24,205), wxSize(248,2), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    borderPadCtrl = new wxSpinCtrl(leftPanel, ID_SPINCTRL2, _T("0"), wxPoint(144,222), wxSize(129,22), 0, 0, 100, 0, _T("ID_SPINCTRL2"));
    borderPadCtrl->SetValue(_T("0"));
    borderPadCtrl->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    shapePadCtrl = new wxSpinCtrl(leftPanel, ID_SPINCTRL3, _T("0"), wxPoint(144,256), wxSize(129,22), 0, 0, 100, 0, _T("ID_SPINCTRL3"));
    shapePadCtrl->SetValue(_T("0"));
    shapePadCtrl->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    FlexGridSizer1->Add(leftPanel, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    leftAndRightLineSep = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(2,625), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    leftAndRightLineSep->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRADIENTACTIVECAPTION));
    leftAndRightLineSep->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
    FlexGridSizer1->Add(leftAndRightLineSep, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    rightPanel = new wxScrolledWindow(this, ID_PANEL2, wxDefaultPosition, wxSize(862,628), wxTAB_TRAVERSAL|wxVSCROLL|wxHSCROLL, _T("ID_PANEL2"));
    loadPngBitmap = new wxStaticBitmap(rightPanel, ID_STATICBITMAP1, wxBitmap(wxImage(_T("D:\\github\\pngmerger\\PngMergerGUI\\PngAlgorithm\\pngTest.png")).Rescale(wxSize(1024,1024).GetWidth(),wxSize(1024,1024).GetHeight())), wxPoint(2,2), wxSize(1024,1024), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    FlexGridSizer1->Add(rightPanel, 1, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    fileListView = new wxListView(this, ID_LISTVIEW1, wxDefaultPosition, wxSize(200,630), wxLC_LIST, wxDefaultValidator, _T("ID_LISTVIEW1"));
    fileListView->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    fileListView->SetHelpText(_("Put Single Png File Tips"));
    FlexGridSizer1->Add(fileListView, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    homeMenuBar = new wxMenuBar();
    fileOpMenu = new wxMenu();
    fileOpenMenuItem = new wxMenuItem(fileOpMenu, ID_MENUITEM1, _("Open"), _("Open image what you selected"), wxITEM_NORMAL);
    fileOpMenu->Append(fileOpenMenuItem);
    fileOpMenu->AppendSeparator();
    saveFileMenuItem = new wxMenuItem(fileOpMenu, ID_MENUITEM2, _("Save as"), _("Save current image file with other name"), wxITEM_NORMAL);
    fileOpMenu->Append(saveFileMenuItem);
    fileOpMenu->AppendSeparator();
    quitMenuItem = new wxMenuItem(fileOpMenu, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    fileOpMenu->Append(quitMenuItem);
    homeMenuBar->Append(fileOpMenu, _("&File"));
    editMenu = new wxMenu();
    homeMenuBar->Append(editMenu, _("Edit"));
    publishMenu = new wxMenu();
    addDirMenuItem = new wxMenuItem(publishMenu, ID_MENUITEM5, _("Add directory"), wxEmptyString, wxITEM_NORMAL);
    publishMenu->Append(addDirMenuItem);
    homeMenuBar->Append(publishMenu, _("Merge"));
    separateMenu = new wxMenu();
    homeMenuBar->Append(separateMenu, _("Separate"));
    saveSettingMenu = new wxMenu();
    saveSetting = new wxMenuItem(saveSettingMenu, ID_MENUITEM3, _("Save setting"), _("save curent setting to local config file"), wxITEM_NORMAL);
    saveSettingMenu->Append(saveSetting);
    deleteSettingMenuItem = new wxMenuItem(saveSettingMenu, ID_MENUITEM4, _("Revert to default"), _("delete all setting have saved in local file"), wxITEM_NORMAL);
    saveSettingMenu->Append(deleteSettingMenuItem);
    homeMenuBar->Append(saveSettingMenu, _("Setting config"));
    helpMenu = new wxMenu();
    aboutMenuItem = new wxMenuItem(helpMenu, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    helpMenu->Append(aboutMenuItem);
    homeMenuBar->Append(helpMenu, _("Help"));
    SetMenuBar(homeMenuBar);
    bottomStatusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, 400, 180 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    bottomStatusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    bottomStatusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(bottomStatusBar);
    bottomStatusBar->SetExtraStyle( bottomStatusBar->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PngMergerGUIFrame::OndataFileLocButtonClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PngMergerGUIFrame::OntextureFileLocButtonClick);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&PngMergerGUIFrame::OnListView1BeginDrag);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_DELETE_ITEM,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileListViewDeleteItem);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileListViewDeleteAllItems);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileListViewItemSelect);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileListViewItemDeselect);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileListViewKeyDown);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_INSERT_ITEM,(wxObjectEventFunction)&PngMergerGUIFrame::OnListView1InsertItem);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileOpenMenuItemSelected);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnsaveFileMenuItemSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnQuit);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnaddDirMenuItemSelected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnsaveSettingSelected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OndeleteSettingMenuItemSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnAbout);
    //*)

    for (int i = 0; i < MAX_ITEMS; i++)
    {
        isSelectFlags[i] = -1;
    }
    isDeleteCompleted = false;
    int boxWid, boxHgt;
    settingStaticBox->GetSize(&boxWid, &boxHgt);
    leftPanel->SetScrollbars(10, 10, boxWid / 10, boxHgt / 10);

    int wid, hgt;
    loadPngBitmap->GetSize(&wid, &hgt);
    rightPanel->SetScrollbars(10, 10, wid / 10, hgt / 10);
    rightPanel->Scroll(0, 0);


    //PngMergerConf *conf = PngMergerConf::sharedInstance();
    //setting config, if not exist, create it and set default value
    bool isConfigExist = wxFile::Exists(wxGetCwd() + "/" + LOCAL_CONF_NAME);
    if (!isConfigExist)
    {
        PngMergerConf::sharedInstance()->writeSetting(NULL);
    }
    setViewOption();
}

//according nameVec param create listView at right
void PngMergerGUIFrame::generateListviewWithFiles(std::vector<wxString> fileNameVec)
{
    //create imagelist for icon
    m_imageListSmall = new wxImageList(ICON_WID, ICON_HGT, true);

    for (int i = 0; i < fileNameVec.size(); i++)
    {
        wxImage *tmp = new wxImage(fileNameVec.at(i), wxBITMAP_TYPE_PNG);
        tmp->Scale(ICON_WID, ICON_HGT);

        wxBitmap bmap(*tmp);
        wxIcon icon;
        icon.CopyFromBitmap(bmap);
        m_imageListSmall->Add(icon);
    }
    createListView(0, fileNameVec);
}


void PngMergerGUIFrame::setViewOption()
{
    PngMergerConf *conf = PngMergerConf::sharedInstance();
    dataFmtChoice->SetSelection(conf->readInt(SETTING_KEY_DATA_FMT));
    textureFmtChoice->SetSelection(conf->readInt(SETTING_KEY_TEXTURE_FMT));
    imageChoice->SetSelection(conf->readInt(SETTING_KEY_IMAGE_FMT));
    borderPadCtrl->SetValue(conf->readInt(SETTING_KEY_BDR_PADDING));
    shapePadCtrl->SetValue(conf->readInt(SETTING_KEY_SPE_PADDING));
    maxHgtChoice->SetSelection(conf->readInt(SETTING_KEY_MAX_HGT));
    maxWidChoice->SetSelection(conf->readInt(SETTING_KEY_MAX_WID));
}

PngMergerGUIFrame::~PngMergerGUIFrame()
{
    //(*Destroy(PngMergerGUIFrame)
    //*)
}

void PngMergerGUIFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PngMergerGUIFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = "PngMerger -- pack small png into large single png \n"
                    "Author : Bugcode\n"
                    "Mail     : bugcoding@gmail.com";
    wxMessageBox(msg, "About PngMerger");
}


void PngMergerGUIFrame::OnPanel2Paint(wxPaintEvent& event)
{
}

void PngMergerGUIFrame::OnListView1BeginDrag(wxListEvent& event)
{
}

void PngMergerGUIFrame::OnListView1InsertItem(wxListEvent& event)
{
}

//texture file button handler
void PngMergerGUIFrame::OntextureFileLocButtonClick(wxCommandEvent& event)
{
    //open tetxure dialog selector
    wxFileDialog texturefileDialog
    (
     this,
     wxT("Open texture file"),
     wxEmptyString,
     wxEmptyString,
#ifdef __WXMOTIF__
     wxT("Png files (*.png)|*.png")
#else
     wxT("Png files (*.png)|*.png;")
#endif
     );
    //display on window's center
    texturefileDialog.CenterOnParent();
    //set directory of file selector
    texturefileDialog.SetDirectory(wxGetHomeDir());

    //press open button
    if (texturefileDialog.ShowModal() == wxID_OK)
    {
        //save plist file path
        wxString texturePath = texturefileDialog.GetPath();
        //set to label
        this->setFilePathText(textureFilePathText, texturePath);
    }}

//save plist file path
void PngMergerGUIFrame::setFilePathText(wxTextCtrl *textCtrl, wxString text)
{
    //first clear
    textCtrl->SetValue("");
    //set real plist path string to TextCtrl
    textCtrl->SetValue(text);
}


//data file button handler
void PngMergerGUIFrame::OndataFileLocButtonClick(wxCommandEvent& event)
{
    //open file dialog selector
    wxFileDialog datafileDialog
    (
     this,
     wxT("Open plist file"),
     wxEmptyString,
     wxEmptyString,
#ifdef __WXMOTIF__
     wxT("Plist files (*.plist)|*.plist")
#else
     wxT("Plist files (*.plist)|*.plist;")
#endif
     );
    //display on window's center
    datafileDialog.CenterOnParent();
    //set directory of file selector
    datafileDialog.SetDirectory(wxGetHomeDir());

    //press open button
    if (datafileDialog.ShowModal() == wxID_OK)
    {
        //save plist file path
        wxString plistPath = datafileDialog.GetPath();
        //set to label
        this->setFilePathText(datafilePathText, plistPath);
    }
}

//updatw status bar
void PngMergerGUIFrame::updateStatusBar(wxString imageName)
{
    char statusBuf[128] = "\0";

    wxBitmap bitmap = loadPngBitmap->GetBitmap();

    sprintf(statusBuf, " Image Name : [%s] >> Image Size : [%d, %d] >> Image Bit Depth : [%d]", imageName.ToStdString().c_str(),
            bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetDepth());

    wxString imageStatus(statusBuf);
    //display image detail infomation in status bar
    bottomStatusBar->SetStatusText(imageStatus, 0);
}


//load new image file with file selector
void PngMergerGUIFrame::loadnewImageFromSelector(wxString imageFilePath)
{
    //disable Warning of png sRGB profiler
    wxLog::SetLogLevel(0);
    //check filename is valid or not
    if (!imageFilePath.empty())
    {
        wxString extName;
        wxString imageName;

        //get file extension name
        wxFileName::SplitPath(imageFilePath, NULL, &imageName, &extName);

        //check file extension is png or not
        if (extName == "png")
        {
            //load new png special with file selector
            loadPngBitmap->SetBitmap(wxBitmap(wxImage(imageFilePath)));

            //fresh first field of status bar
            this->updateStatusBar(imageName + "." + extName);

            //fresh current window
            Refresh();
        }
    }
}

//open the file handler
void PngMergerGUIFrame::OnfileOpenMenuItemSelected(wxCommandEvent& event)
{
    //testing for menuitem open click

    //file open dialog
    wxFileDialog dialog
    (
        this,
        wxT("Open image file"),
        wxEmptyString,
        wxEmptyString,
#ifdef __WXMOTIF__
        wxT("Png files (*.png)|*.png")
#else
        wxT("Png files (*.png)|*.png;")
#endif
    );

    //display on home windows center
    dialog.CentreOnParent();
    //defualt search directory
    dialog.SetDirectory(wxGetHomeDir());

    //if press 'Open' button
    if (dialog.ShowModal() == wxID_OK)
    {
        //image file path
        wxString imageFilePath = dialog.GetPath();
        this->loadnewImageFromSelector(imageFilePath);
    }

}

//listView create
void PngMergerGUIFrame::createListView(long flags, std::vector<wxString> fileNameVec)
{
    //rebuild listview
    fileListView->SetImageList(m_imageListSmall, wxIMAGE_LIST_SMALL);
    //listview item, image name need to remove path separater
    for ( int i = 0; i < fileNameVec.size(); i++ )
    {
        wxString tmp = fileNameVec.at(i);
        int pos = 0;
        if ((pos = tmp.Find('/', true)) != std::string::npos)
        {
            tmp = tmp.SubString(pos + 1, tmp.Len() - 1);
        }
        fileListView->InsertItem(i, tmp, i);
    }
}


//save the file with image compression algorithm
void PngMergerGUIFrame::OnsaveFileMenuItemSelected(wxCommandEvent& event)
{
#if wxUSE_FILEDLG
    wxBitmap bitmap = loadPngBitmap->GetBitmap();
    wxImage image = bitmap.ConvertToImage();

    wxString savefilename = wxFileSelector( wxT("Save Image"),
                                            wxEmptyString,
                                            wxEmptyString,
                                            wxEmptyString,
                                            wxT("BMP files (*.bmp)|*.bmp|")
#if wxUSE_LIBPNG
                                            wxT("PNG files (*.png)|*.png|")
#endif
#if wxUSE_LIBJPEG
                                            wxT("JPEG files (*.jpg)|*.jpg|")
#endif
#if wxUSE_GIF
                                            wxT("GIF files (*.gif)|*.gif|")
#endif
#if wxUSE_LIBTIFF
                                            wxT("TIFF files (*.tif)|*.tif|")
#endif
#if wxUSE_PCX
                                            wxT("PCX files (*.pcx)|*.pcx|")
#endif
#if wxUSE_XPM
                                            wxT("X PixMap files (*.xpm)|*.xpm|")
#endif
                                            wxT("ICO files (*.ico)|*.ico|")
                                            wxT("CUR files (*.cur)|*.cur"),
                                            wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                                            this);

    if ( savefilename.empty() )
    {
        return;
    }

    wxString extension;
    wxFileName::SplitPath(savefilename, NULL, NULL, &extension);

    bool saved = false;

    if ( extension == wxT("bmp") )
    {
        static const int bppvalues[] =
        {
            wxBMP_1BPP,
            wxBMP_1BPP_BW,
            wxBMP_4BPP,
            wxBMP_8BPP,
            wxBMP_8BPP_GREY,
            wxBMP_8BPP_RED,
            wxBMP_8BPP_PALETTE,
            wxBMP_24BPP
        };

        const wxString bppchoices[] =
        {
            wxT("1 bpp color"),
            wxT("1 bpp B&W"),
            wxT("4 bpp color"),
            wxT("8 bpp color"),
            wxT("8 bpp greyscale"),
            wxT("8 bpp red"),
            wxT("8 bpp own palette"),
            wxT("24 bpp")
        };

        int bppselection = wxGetSingleChoiceIndex(wxT("Set BMP BPP"),
                           wxT("Image sample: save file"),
                           WXSIZEOF(bppchoices),
                           bppchoices,
                           this);

        if ( bppselection != -1 )
        {
            int format = bppvalues[bppselection];
            image.SetOption(wxIMAGE_OPTION_BMP_FORMAT, format);

            if ( format == wxBMP_8BPP_PALETTE )
            {
                unsigned char *cmap = new unsigned char [256];

                for ( int i = 0; i < 256; i++ )
                {
                    cmap[i] = (unsigned char)i;
                }

                image.SetPalette(wxPalette(256, cmap, cmap, cmap));

                delete[] cmap;
            }
        }
    }

#if wxUSE_LIBPNG
    else if ( extension == wxT("png") )
    {
        static const int pngvalues[] =
        {
            wxPNG_TYPE_COLOUR,
            wxPNG_TYPE_COLOUR,
            wxPNG_TYPE_GREY,
            wxPNG_TYPE_GREY,
            wxPNG_TYPE_GREY_RED,
            wxPNG_TYPE_GREY_RED,
        };

        const wxString pngchoices[] =
        {
            wxT("Colour 8bpp"),
            wxT("Colour 16bpp"),
            wxT("Grey 8bpp"),
            wxT("Grey 16bpp"),
            wxT("Grey red 8bpp"),
            wxT("Grey red 16bpp"),
        };

        int sel = wxGetSingleChoiceIndex(wxT("Set PNG format"),
                                         wxT("Image sample: save file"),
                                         WXSIZEOF(pngchoices),
                                         pngchoices,
                                         this);

        if ( sel != -1 )
        {
            image.SetOption(wxIMAGE_OPTION_PNG_FORMAT, pngvalues[sel]);
            image.SetOption(wxIMAGE_OPTION_PNG_BITDEPTH, sel % 2 ? 16 : 8);

            // these values are taken from OptiPNG with -o3 switch
            const wxString compressionChoices[] =
            {
                wxT("compression = 9, memory = 8, strategy = 0, filter = 0"),
                wxT("compression = 9, memory = 9, strategy = 0, filter = 0"),
                wxT("compression = 9, memory = 8, strategy = 1, filter = 0"),
                wxT("compression = 9, memory = 9, strategy = 1, filter = 0"),
                wxT("compression = 1, memory = 8, strategy = 2, filter = 0"),
                wxT("compression = 1, memory = 9, strategy = 2, filter = 0"),
                wxT("compression = 9, memory = 8, strategy = 0, filter = 5"),
                wxT("compression = 9, memory = 9, strategy = 0, filter = 5"),
                wxT("compression = 9, memory = 8, strategy = 1, filter = 5"),
                wxT("compression = 9, memory = 9, strategy = 1, filter = 5"),
                wxT("compression = 1, memory = 8, strategy = 2, filter = 5"),
                wxT("compression = 1, memory = 9, strategy = 2, filter = 5"),
            };

            int sel = wxGetSingleChoiceIndex(wxT("Select compression option (Cancel to use default)\n"),
                                             wxT("PNG Compression Options"),
                                             WXSIZEOF(compressionChoices),
                                             compressionChoices,
                                             this);

            if (sel != -1)
            {
                const int zc[] = {9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 1, 1};
                const int zm[] = {8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 8, 9};
                const int zs[] = {0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2};
                const int f[]  = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
                                  0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8
                                 };

                image.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_LEVEL      , zc[sel]);
                image.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_MEM_LEVEL  , zm[sel]);
                image.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_STRATEGY   , zs[sel]);
                image.SetOption(wxIMAGE_OPTION_PNG_FILTER                 , f[sel]);
                image.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_BUFFER_SIZE, 1048576); // 1 MB
            }
        }
    }

#endif // wxUSE_LIBPNG
    else if ( extension == wxT("cur") )
    {
        image.Rescale(32, 32);
        image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 0);
        image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 0);
        // This shows how you can save an image with explicitly
        // specified image format:
        saved = image.SaveFile(savefilename, wxBITMAP_TYPE_CUR);
    }

    if ( !saved )
    {
        // This one guesses image format from filename extension
        // (it may fail if the extension is not recognized):
        image.SaveFile(savefilename);
    }

#endif // wxUSE_FILEDLG
}

//set conf.ini default value
void PngMergerGUIFrame::setConfDefaultValue(DATA_TYPE dt)
{
    switch(dt)
    {
    case COCOS2D:
        dbg_print("Cocos2d");
        break;
    default:
        dbg_print("None Type");
        break;
    }
}

//set Png



//save software setting to local config file
void PngMergerGUIFrame::OnsaveSettingSelected(wxCommandEvent& event)
{
    //get conf handler
    PngMergerConf *conf = PngMergerConf::sharedInstance();

    //write current software setting information
    SETTING_FIELD setting;
    setting.datafmt = wxString::Format("%d", dataFmtChoice->GetCurrentSelection());
    setting.texturefmt = wxString::Format("%d", textureFmtChoice->GetCurrentSelection());
    setting.imagefmt = wxString::Format("%d", imageChoice->GetCurrentSelection());
    setting.borderpadding = wxString::Format("%d", borderPadCtrl->GetValue());
    setting.shapepadding = wxString::Format("%d", shapePadCtrl->GetValue());
    setting.maxwid = wxString::Format("%d", maxWidChoice->GetCurrentSelection());
    setting.maxhgt = wxString::Format("%d", maxHgtChoice->GetCurrentSelection());

    if (conf->writeSetting(&setting))
    {
        wxMessageBox("save settings success!", "Save Settings");
    }

}
//delete all software setting in local
void PngMergerGUIFrame::OndeleteSettingMenuItemSelected(wxCommandEvent& event)
{
    //delete all saved settings information
    if (PngMergerConf::sharedInstance()->deleteSavedSetting())
    {
        wxMessageBox("Delete saved settings success!", "Delete Information");

        //change gui now, set option to default
        PngMergerConf::sharedInstance()->writeSetting(NULL);
        setViewOption();
    }
}


//add directory handler
void PngMergerGUIFrame::OnaddDirMenuItemSelected(wxCommandEvent& event)
{
    //directory open dialog
    wxDirDialog dirDialog
    (
        this,
        wxT("Open contains image file directory")
    );

    //display on home windows center
    dirDialog.CentreOnParent();
    //defualt search directory
    dirDialog.SetPath(wxGetHomeDir());

    //if press 'Open' button
    if (dirDialog.ShowModal() == wxID_OK)
    {
        //images file directory
        wxString imagesFileDir = dirDialog.GetPath();

        //get each png data in this directory
        PngMergeTool *pmt = new PngMergeTool(imagesFileDir.ToStdString());
        if (pmt->getAndReadAllImage())
        {
            std::vector<BasePngPropt *> vec = pmt->getInfoVec();

            std::vector<wxString> fileNameVec;
            for (int i = 0; i < vec.size(); i++)
            {
                BasePngPropt *tmp = vec.at(i);
                wxString nameStr(tmp->pngfileName);
                fileNameVec.push_back(nameStr);
            }
            //create list view
            generateListviewWithFiles(fileNameVec);

        }
    }
}

//delete item key event handler
void PngMergerGUIFrame::OnfileListViewKeyDown(wxListEvent& event)
{
//    wxString keyCode = wxString::Format("%d", event.GetKeyCode());
//    wxMessageBox(keyCode);

    //handle 'press delete key' event
    if (event.GetKeyCode() == WXK_DELETE)
    {
        int index = event.GetIndex();
        //delete single item
        if (index != -1 && fileListView->GetSelectedItemCount() == 1)
        {
            fileListView->DeleteItem(index);
        }
        //delete all items
        else if (fileListView->GetSelectedItemCount() == fileListView->GetItemCount())
        {
            fileListView->DeleteAllItems();
        }
        else
        {
            isDeleteCompleted = false;
            //delete items between 1 and fileListView->GetItemCount
            for (int i = 0; i < MAX_ITEMS; i++)
            {
                if (isSelectFlags[i] == 0)
                {
                    isSelectFlags[i] = -1;
                    fileListView->DeleteItem(i);
                }
            }
            isDeleteCompleted = false;
        }
    }

}

void PngMergerGUIFrame::resetItemSelectFlags()
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        isSelectFlags[i] = -1;
    }
}

void PngMergerGUIFrame::OnfileListViewItemSelect(wxListEvent& event)
{
    //set flag for isSelectFlag
    wxMessageBox(wxString::Format("%d", event.GetIndex()));

    isSelectFlags[event.GetIndex()] = 0;
}

void PngMergerGUIFrame::OnfileListViewItemDeselect(wxListEvent& event)
{
    //reset to -1 for unselect
    isSelectFlags[event.GetIndex()] = -1;
}
//reset all flags to -1 in isSelectFlags
void PngMergerGUIFrame::OnfileListViewDeleteItem(wxListEvent& event)
{
    if (isDeleteCompleted)
    {
        //resetItemSelectFlags();
    }
}

void PngMergerGUIFrame::OnfileListViewDeleteAllItems(wxListEvent& event)
{
    //resetItemSelectFlags();
}
