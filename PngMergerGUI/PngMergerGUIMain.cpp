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

#if wxUSE_FILEDLG
#include "wx/filedlg.h"
#endif // wxUSE_FILEDLG

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
const long PngMergerGUIFrame::ID_MENUITEM3 = wxNewId();
const long PngMergerGUIFrame::idMenuQuit = wxNewId();
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
    SetClientSize(wxSize(1333,675));
    SetMinSize(wxSize(1330,700));
    SetMaxSize(wxSize(1343,705));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("D:\\github\\pngmerger\\PngMergerGUI\\pngmerger.ico"))));
    	SetIcon(FrameIcon);
    }
    FlexGridSizer1 = new wxFlexGridSizer(4, 4, wxDLG_UNIT(this,wxSize(0,0)).GetWidth(), wxDLG_UNIT(this,wxSize(0,0)).GetWidth());
    leftPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(321,628), wxTAB_TRAVERSAL|wxVSCROLL|wxHSCROLL, _T("ID_PANEL1"));
    settingStaticBox = new wxStaticBox(leftPanel, ID_STATICBOX1, _("Setting"), wxPoint(0,5), wxSize(303,850), 0, _T("ID_STATICBOX1"));
    dataFmtChoice = new wxChoice(leftPanel, ID_CHOICE1, wxPoint(130,40), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    dataFmtChoice->Append(_("Cocos2d"));
    dataFmtChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    textureFmtChoice = new wxChoice(leftPanel, ID_CHOICE3, wxPoint(130,104), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    textureFmtChoice->Append(_("Png (.png)"));
    textureFmtChoice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    Choice1 = new wxChoice(leftPanel, ID_CHOICE4, wxPoint(130,136), wxSize(144,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    Choice1->Append(_("RGBA"));
    Choice1->Append(_("RGBA8888"));
    Choice1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
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
    rightPanel = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(862,628), wxTAB_TRAVERSAL|wxVSCROLL|wxHSCROLL, _T("ID_PANEL2"));
    loadPngPanel = new wxStaticBitmap(rightPanel, ID_STATICBITMAP1, wxBitmap(wxImage(_T("D:\\github\\pngmerger\\PngAlgorithm\\pngTest.png")).Rescale(wxSize(1024,1024).GetWidth(),wxSize(1024,1024).GetHeight())), wxPoint(2,2), wxSize(1024,1024), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    FlexGridSizer1->Add(rightPanel, 1, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    fileListView = new wxListView(this, ID_LISTVIEW1, wxDefaultPosition, wxSize(150,682), wxLC_LIST, wxDefaultValidator, _T("ID_LISTVIEW1"));
    fileListView->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    FlexGridSizer1->Add(fileListView, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    homeMenuBar = new wxMenuBar();
    fileOpMenu = new wxMenu();
    fileOpenMenuItem = new wxMenuItem(fileOpMenu, ID_MENUITEM1, _("Open"), wxEmptyString, wxITEM_NORMAL);
    fileOpMenu->Append(fileOpenMenuItem);
    fileOpMenu->AppendSeparator();
    saveFileMenuItem = new wxMenuItem(fileOpMenu, ID_MENUITEM2, _("Save"), wxEmptyString, wxITEM_NORMAL);
    fileOpMenu->Append(saveFileMenuItem);
    saveAsMenuItem = new wxMenuItem(fileOpMenu, ID_MENUITEM3, _("Save as..."), wxEmptyString, wxITEM_NORMAL);
    fileOpMenu->Append(saveAsMenuItem);
    fileOpMenu->AppendSeparator();
    quitMenuItem = new wxMenuItem(fileOpMenu, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    fileOpMenu->Append(quitMenuItem);
    homeMenuBar->Append(fileOpMenu, _("&File"));
    editMenu = new wxMenu();
    homeMenuBar->Append(editMenu, _("Edit"));
    publishMenu = new wxMenu();
    homeMenuBar->Append(publishMenu, _("Publish"));
    separateMenu = new wxMenu();
    homeMenuBar->Append(separateMenu, _("Separate"));
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

    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&PngMergerGUIFrame::OnListView1BeginDrag);
    Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_INSERT_ITEM,(wxObjectEventFunction)&PngMergerGUIFrame::OnListView1InsertItem);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnfileOpenMenuItemSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PngMergerGUIFrame::OnAbout);
    //*)
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
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
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
        wxMessageBox("File Open MenuItem Pressed! >> " + dialog.GetPath());
    }

}




















