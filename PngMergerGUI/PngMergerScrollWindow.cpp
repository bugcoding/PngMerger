/*=============================================================================
#     FileName: PngMergerScrollWindow.cpp
#         Desc: imp for PngMergerScrollWindow
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2015-02-05 22:21:13
=============================================================================*/

#include "PngMergerScrollWindow.h"

BEGIN_EVENT_TABLE(PngMergerScrollWindow, wxPanel)
// catch paint events
EVT_PAINT(PngMergerScrollWindow::paintEvent)

END_EVENT_TABLE()

PngMergerScrollWindow::PngMergerScrollWindow(wxWindow *parent,
                                            wxWindowID winid,
                                            const wxPoint& pos,
                                            const wxSize& size,
                                            long style,
                                            const wxString& name) :
wxScrolledWindow(parent, winid, pos, size, style, name)
{
}

void PngMergerScrollWindow::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    drawWindow(dc);
}

void PngMergerScrollWindow::paintNow()
{
    wxClientDC dc(this);
    drawWindow(dc);
}

void PngMergerScrollWindow::drawWindow(wxDC&  dc)
{

    int xScrollUnits, yScrollUnits, xOrigin, yOrigin;

    this->GetViewStart( &xOrigin, &yOrigin);
    this->GetScrollPixelsPerUnit( &xScrollUnits, &yScrollUnits );


    //wxPoint p(500 - xOrigin * xScrollUnits, 500 - yOrigin * yScrollUnits);
    wxPoint p(200, 300);
    wxSize size(200, 200);
    wxPen pen(*wxBLACK, 5, wxPENSTYLE_SHORT_DASH);
    dc.SetPen(pen);

    wxBrush bs(wxColour(0, 255, 0, 128));

    dc.SetBrush(bs);
    dc.DrawRectangle(p, size);
}


