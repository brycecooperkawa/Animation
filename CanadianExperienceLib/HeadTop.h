/**
 * @file HeadTop.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"
#include "AnimChannelMove.h"

class HeadTop : public ImageDrawable {
private:
    ///The center of the image
    wxPoint mCenter = wxPoint(0,0);

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// The animation channel for animating the move of this drawable
    AnimChannelMove mChannel;

    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannelR;

public:
    HeadTop(const std::wstring &name, const std::wstring &filename);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Says if the head top is movable
     * @return true because the head top is movable
     */
    bool IsMovable() override {return true;};

    //wxPoint TransformPoint(wxPoint p);
    wxPoint TransformPoint(wxPoint p);

    void SetKeyframe() override;
    void GetKeyframe() override;
    void SetTimeline(Timeline *timeline) override;
};

#endif //CANADIANEXPERIENCE_HEADTOP_H
