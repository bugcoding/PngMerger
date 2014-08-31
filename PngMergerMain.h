/***************************************************************
 * Name:      PngMergerMain.h
 * Purpose:   Defines Application Frame
 * Author:    bugcode (bugcoding@gmail.com)
 * Created:   2014-08-30
 * Copyright: bugcode (bugcode.net)
 * License:
 **************************************************************/

#ifndef PNGMERGERMAIN_H
#define PNGMERGERMAIN_H

//(*Headers(PngMergerFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class PngMergerFrame: public wxFrame
{
    public:

        PngMergerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PngMergerFrame();

    private:

        //(*Handlers(PngMergerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnListbook1PageChanged(wxListbookEvent& event);
        //*)

        //(*Identifiers(PngMergerFrame)
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(PngMergerFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PNGMERGERMAIN_H
