/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Bryce Cooperkawa
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>
#include <wx/graphics.h>
#include <wx/bitmap.h>

#include "ViewTimeline.h"
#include "Timeline.h"
#include "TimelineDlg.h"
#include "Picture.h"
#include "Actor.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 * Constructor
 * @param parent The main wxFrame object
 */
ViewTimeline::ViewTimeline(wxFrame* parent,std::wstring imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));
    parent->Bind(wxEVT_UPDATE_UI, &ViewTimeline::OnUpdateSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_UPDATE_UI, &ViewTimeline::OnUpdateDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));

    mImagesDir=imagesDir;
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    auto size = GetPicture()->GetSize();
    SetVirtualSize(((this->GetPicture())->GetTimeline()->GetNumFrames())*TickSpacing+BorderLeft+BorderRight, size.GetHeight());
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 128, 0), 1);
    graphics->SetPen(pen);
    graphics->DrawRectangle(10, 10, 200, 60);

    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);
    graphics->DrawText(L"Timeline!", 15, 15);

    auto time = wxDateTime::Now();
    auto timeStr = time.Format(L"%x %T");
    graphics->DrawText(timeStr, 15, 40);

    //pen for ticks
    wxPen TickPen(*wxBLACK, 1);
    graphics->SetPen(TickPen);

    //draws the timeline with ticks
    for(int i=0;i<(this->GetPicture())->GetTimeline()->GetNumFrames();i=i+1)
    {
        // Convert the tick number to seconds in a string
        std::wstringstream str;
        str << i/ (this->GetPicture())->GetTimeline()->GetFrameRate();
        std::wstring wstr = str.str();

        double w, h;
        graphics->GetTextExtent(wstr, &w, &h);

        //gets the x value for the tick
        int x=BorderLeft+TickSpacing*i;

        //gets the y values for the tick
        int y1=TickTop;
        int y2=y1-TickShort;

        //gets the second y value for the tick if its a number
        if(bool onSecond = (i % (this->GetPicture())->GetTimeline()->GetFrameRate()) == 0)
        {
            y1=TickLong;
            //displays the string under the long ticks
            graphics->DrawText(wstr,x-5,y1+3);
        }

        graphics->StrokeLine(x, y1, x, y2);
    }

    //gets the image for the pointer
    mPointerImage = std::make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);

    //creates the bitmap for the pointer
    mPointerBitmap=graphics->CreateBitmapFromImage(*mPointerImage);

    //equations to determine the x value of the pointer
    double CurrentTime = (this->GetPicture())->GetTimeline()->GetCurrentTime();
    double j = CurrentTime*(this->GetPicture())->GetTimeline()->GetFrameRate();

    //draws the pointer
    graphics->DrawBitmap(mPointerBitmap,
            j*TickSpacing+5, 10,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;

}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    if(mMovingPointer)
    {
        if (event.LeftIsDown())
        {
            double x = double(click.x)/double(TickSpacing)/double((this->GetPicture())->GetTimeline()->GetFrameRate());
            //sets the current time to the mouse location
            (this->GetPicture())->SetAnimationTime(x);

            //sets the current time
            mTime=x;
        }
    }

    Refresh();
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(),(this->GetPicture())->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
       (this->GetPicture())->UpdateObservers();
    }
}

/**
 * Handles the setkeyframe menu interaction
 * @param event the input
 */
void ViewTimeline::OnEditSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Handles the delete keyframe menu interaction
 * @param event the input
 */
void ViewTimeline::OnEditDeleteKeyframe(wxCommandEvent& event)
{
    //gets the timeline
    auto timeline=(this->GetPicture())->GetTimeline();

    auto frame=timeline->GetCurrentFrame();

    for(auto channel : timeline->GetChannels())
    {
        channel->DeleteKeyframe(frame);
    }

    GetPicture()->SetAnimationTime(mTime);
}

/**
 * Updates the set keyframe option
 * @param event the input
 */
void ViewTimeline::OnUpdateSetKeyframe(wxUpdateUIEvent& event)
{

}

/**
 * Updates the delete keyframe option
 * @param event the input
 */
void ViewTimeline::OnUpdateDeleteKeyframe(wxUpdateUIEvent& event)
{

}




