/***************************************************************
 * Name:      PngMergerGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    bugcode (bugcoding@gmail.com)
 * Created:   2014-12-02
 * Copyright: bugcode (bugcode.net)
 * License:
 **************************************************************/

#include "PngMergerGUIApp.h"

//(*AppHeaders
#include "PngMergerGUIMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PngMergerGUIApp);

bool PngMergerGUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PngMergerGUIFrame* Frame = new PngMergerGUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
