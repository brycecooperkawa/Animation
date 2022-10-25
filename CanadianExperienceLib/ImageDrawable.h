/**
 * @file ImageDrawable.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"

class ImageDrawable : public Drawable {
private:
    ///The center of the image
    wxPoint mCenter = wxPoint(0,0);

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

public:
    ImageDrawable(const std::wstring &name, const std::wstring &filename);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    /**
     * Set the image center
     * @param pos The new center
     */
    void SetCenter(wxPoint pos) { mCenter = pos; }
    /**
     * Get the image center
     * @return The drawable center
     */
    wxPoint GetCenter() const { return mCenter; }

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;
};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
