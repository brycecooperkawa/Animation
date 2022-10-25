/**
 * @file HeadTop.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"

using namespace std;

/**
 * Constructor
 * @param name The drawable name
 * @param filename The filename for the image
 */
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename) : ImageDrawable(name, filename)
{
    mImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Draw the image drawable
 * @param graphics Graphics context to draw on
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    //upcall the original version
    ImageDrawable::Draw(graphics);

    //eye code
    float wid = 15.0f;
    float hit = 20.0f;

    wxBrush brush(wxColour(*wxBLACK));
    graphics->SetBrush(brush);

    //eye 1
    wxPoint e1=TransformPoint(wxPoint(GetCenter().x-15,GetCenter().y-39));
    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

    //eye 2
    wxPoint e2=TransformPoint(wxPoint(GetCenter().x+15,GetCenter().y-39));
    graphics->PushState();
    graphics->Translate(e2.x, e2.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

    //eyebrows
    wxPen eyebrowPen(*wxBLACK, 2);

    //eyebrow 1 (left)
    wxPoint p1=TransformPoint(wxPoint(GetCenter().x-26,GetCenter().y-52));
    wxPoint p2=TransformPoint(wxPoint(GetCenter().x-10,GetCenter().y-53));
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);

    //eyebrow 2 (right)
    p1=TransformPoint(wxPoint(GetCenter().x+6,GetCenter().y-53));
    p2=TransformPoint(wxPoint(GetCenter().x+22,GetCenter().y-52));
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);

}

/**
 * Transform a point from a location on the bitmap to
 *  a location on the screen.
 * @param  p Point to transform
 * @returns Transformed point
 */
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Sets the keyframe for the headtop
 */
void HeadTop::SetKeyframe()
{
    mChannel.SetKeyframe(GetPosition());
    mChannelR.SetKeyframe(GetRotation());
}

/**
 * Gets the keyframe for the headtop
 */
void HeadTop::GetKeyframe()
{
    if(mChannel.IsValid())
    {
        SetPosition(mChannel.GetPoint());
    }

    if(mChannelR.IsValid())
    {
        SetRotation(mChannelR.GetAngle());
    }

}

/**
 * Add the channels for this drawable to a timeline
 * @param timeline the timeline class
 */
void HeadTop::SetTimeline(Timeline *timeline)
{
    timeline->AddChannel(&mChannel);
    timeline->AddChannel(&mChannelR);
}