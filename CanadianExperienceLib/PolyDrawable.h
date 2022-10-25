/**
 * @file PolyDrawable.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable {
private:
    /// The polygon color
    wxColor mColor = *wxBLACK;

    /// collection of points
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;


public:
    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable &) = delete;

    /// Assignment operator
    void operator=(const PolyDrawable &) = delete;

    PolyDrawable(const std::wstring &name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    void AddPoint(wxPoint point);

    /**
     * Set the polydrawable color
     * @param color The new polydrawable color
     */
    void SetColor(wxColor color) { mColor = color; }
    /**
     * Get the polydrawable color
     * @return The polydrawable color
     */
    wxColor GetColor() const { return mColor; }


};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
