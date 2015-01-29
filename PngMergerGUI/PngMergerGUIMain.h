/***************************************************************
 * Name:      PngMergerGUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    bugcode (bugcoding@gmail.com)
 * Created:   2014-12-02
 * Copyright: bugcode (bugcode.net)
 * License:
 **************************************************************/

#ifndef PNGMERGERGUIMAIN_H
#define PNGMERGERGUIMAIN_H

//(*Headers(PngMergerGUIFrame)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)





#include <iostream>
#include <vector>
#include "PngMergerConf.h"
#include "wx/scrolwin.h"

//max items
#define MAX_ITEMS       256


class PngMergerGUIFrame: public wxFrame
{
    public:

        PngMergerGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PngMergerGUIFrame();

    private:

        //flags for item is selected in listview
        int isSelectFlags[MAX_ITEMS];
        //delete all select item or not
        bool isDeleteCompleted;
        //from single png file to create icon file in listview
        wxImageList *m_imageListSmall;
        //image name -- all png file name
        std::vector<wxString>m_imageNameVec;

        //
        //load new image file with file selector
        void loadnewImageFromSelector(wxString imageFilePath);
        //update status bar
        void updateStatusBar(wxString fileName);
        void createListView(long flags, std::vector<wxString> fileNameVec);
        //set plist or png file path to TextLabel
        void setFilePathText(wxTextCtrl *textCtrl, wxString text);
        //set default conf value when app init
        void setConfDefaultValue(DATA_TYPE dt);
        //set option for setting
        void setViewOption();
        //create listview
        void generateListviewWithFiles(std::vector<wxString> fileNameVec);
        //reset all flags to -1
        void resetItemSelectFlags();


        //(*Handlers(PngMergerGUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPanel2Paint(wxPaintEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnListView1BeginDrag(wxListEvent& event);
        void OnListView1InsertItem(wxListEvent& event);
        void OnfileOpenMenuItemSelected(wxCommandEvent& event);
        void OnsaveFileMenuItemSelected(wxCommandEvent& event);
        void OndataFileLocButtonClick(wxCommandEvent& event);
        void OntextureFileLocButtonClick(wxCommandEvent& event);
        void OnsaveSettingSelected(wxCommandEvent& event);
        void OndeleteSettingMenuItemSelected(wxCommandEvent& event);
        void OnaddDirMenuItemSelected(wxCommandEvent& event);
        void OnfileListViewKeyDown(wxListEvent& event);
        void OnfileListViewItemSelect(wxListEvent& event);
        void OnfileListViewItemDeselect(wxListEvent& event);
        void OnfileListViewDeleteItem(wxListEvent& event);
        void OnfileListViewDeleteAllItems(wxListEvent& event);
        //*)

        //(*Identifiers(PngMergerGUIFrame)
        static const long ID_STATICBOX1;
        static const long ID_CHOICE1;
        static const long ID_CHOICE3;
        static const long ID_CHOICE4;
        static const long ID_CHOICE5;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON1;
        static const long ID_STATICLINE2;
        static const long ID_SPINCTRL2;
        static const long ID_SPINCTRL3;
        static const long ID_PANEL1;
        static const long ID_STATICLINE1;
        static const long ID_STATICBITMAP1;
        static const long ID_PANEL2;
        static const long ID_LISTVIEW1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long idMenuQuit;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM4;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(PngMergerGUIFrame)
        wxMenu* separateMenu;
        wxStaticBox* settingStaticBox;
        wxMenuItem* saveFileMenuItem;
        wxStaticBitmap* loadPngBitmap;
        wxStaticText* datafileLabel;
        wxMenuItem* fileOpenMenuItem;
        wxMenu* saveSettingMenu;
        wxButton* dataFileLocButton;
        wxStaticText* shapePadLabel;
        wxStaticText* textureFmtLabel;
        wxScrolledWindow* leftPanel;
        wxStaticLine* leftAndRightLineSep;
        wxListView* fileListView;
        wxSpinCtrl* borderPadCtrl;
        wxChoice* dataFmtChoice;
        wxStaticText* imageFmtLabel;
        wxMenu* publishMenu;
        wxTextCtrl* textureFilePathText;
        wxTextCtrl* datafilePathText;
        wxChoice* textureFmtChoice;
        wxMenuItem* saveSetting;
        wxStaticText* textureFileLabel;
        wxChoice* maxHgtChoice;
        wxStatusBar* bottomStatusBar;
        wxStaticText* maxHgtLabel;
        wxMenuItem* deleteSettingMenuItem;
        wxMenuItem* addDirMenuItem;
        wxStaticText* borderPadLabel;
        wxScrolledWindow* rightPanel;
        wxStaticText* dataFmtLabel;
        wxMenu* editMenu;
        wxStaticText* maxWidLbl;
        wxChoice* maxWidChoice;
        wxButton* textureFileLocButton;
        wxStaticLine* setting1Line;
        wxChoice* imageChoice;
        wxSpinCtrl* shapePadCtrl;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PNGMERGERGUIMAIN_H
