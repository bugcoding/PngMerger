/***************************************************************
 * Name:      PngMergerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    bugcode (bugcoding@gmail.com)
 * Created:   2014-08-30
 * Copyright: bugcode (bugcode.net)
 * License:
 **************************************************************/

#include "PngMergerApp.h"

//(*AppHeaders
#include "PngMergerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PngMergerApp);

bool PngMergerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PngMergerFrame* Frame = new PngMergerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
