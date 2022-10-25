/**
 * @file ViewTimeline.h
 * @author Charles B. Owen
 * @author Bryce Cooperkawa
 *
 * View class for the timeline area of the screen.
 */

#ifndef CANADIANEXPERIENCE_VIEWTIMELINE_H
#define CANADIANEXPERIENCE_VIEWTIMELINE_H

#include "PictureObserver.h"

/**
 * View class for the timeline area of the screen.
 */
class ViewTimeline final : public wxScrolledCanvas, public PictureObserver {
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    /// Bitmap image for the pointer
    std::unique_ptr<wxImage> mPointerImage;

    /// Graphics bitmap to display
    wxGraphicsBitmap mPointerBitmap;

    /// Images directory
    std::wstring mImagesDir;

    /// Flag to indicate we are moving the pointer
    bool mMovingPointer = false;

    /// The current time
    double mTime=0;

public:
    static const int Height = 90;      ///< Height to make this window

    ViewTimeline(wxFrame* parent,std::wstring imagesDir);

    void UpdateObserver() override;

    void OnEditTimelineProperties(wxCommandEvent& event);

    void OnEditSetKeyframe(wxCommandEvent& event);
    void OnEditDeleteKeyframe(wxCommandEvent& event);
    void OnUpdateSetKeyframe(wxUpdateUIEvent& event);
    void OnUpdateDeleteKeyframe(wxUpdateUIEvent& event);
};


#endif //CANADIANEXPERIENCE_VIEWTIMELINE_H
