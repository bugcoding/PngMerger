/*=============================================================================
#     FileName: PngMergerScrollWindow.h
#         Desc: new scroll window to implement wxScrollWindow
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2015-02-05 22:17:05
=============================================================================*/

#ifndef _PNGMERGER_SCROLL_WINDOW_H_

#define _PNGMERGER_SCROLL_WINDOW_H_


#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <wx/dc.h>

class PngMergerScrollWindow : public wxScrolledWindow
{
public:
    //constructor for new scroll window
    PngMergerScrollWindow(wxWindow *parent,
                            wxWindowID winid = wxID_ANY,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxScrolledWindowStyle,
                            const wxString& name = wxPanelNameStr);

    //paint event
    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void drawWindow(wxDC& dc);

    DECLARE_EVENT_TABLE()
};

#endif
