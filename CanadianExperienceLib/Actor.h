/**
 * @file Actor.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include "AnimChannelMove.h"

class Drawable;
class Picture;

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor {
private:
    ///name of the actor
    std::wstring mName;

    ///is this actor enabled (drawable)?
    bool mEnabled=true;

    ///a point representing the actors current position
    wxPoint mPosition;

    ///is this actor mouse clickable?
    bool mClickable=true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    ///pointer to the picture
    Picture *mPicture=nullptr;

    /// The animation channel for animating the move of this drawable
    AnimChannelMove mChannel;

public:
    /// Destructor
    virtual ~Actor() {}

    /// Default constructor (disabled)
    Actor() = delete;
    
    /// Copy constructor (disabled)
    Actor(const Actor &) = delete;
    
    /// Assignment operator
    void operator=(const Actor &) = delete;

    ///constructor
    Actor(const std::wstring &name);

    void SetRoot(std::shared_ptr<Drawable> root);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get the actor name
     * @return Actor name
     **/
    std::wstring GetName() const { return mName; }

    /**
     * Get the value of enabled
     * @return bool value of enabled
     **/
    bool IsEnabled() const { return mEnabled; }
    /**
     * Set Actor enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Get the position
     * @return point representing position
     **/
    wxPoint GetPosition() const { return mPosition; }
    /**
     * Set position
     * @param point new position
     */
    void SetPosition(wxPoint point) { mPosition = point; }

    /**
     * Get the value of clickabe
     * @return bool value of clickable
     **/
    bool IsClickable() const { return mClickable; }
    /**
     * Set Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    void SetPicture(Picture *picture);

    /**
     * Set the picture for the actor
     * @param picture the picture for the actor
     */
    Picture* GetPicture() { return mPicture; }

    virtual void SetKeyframe();
    virtual void GetKeyframe();

    void SetTimeline(Timeline* timeline);

    /**
     * Gets the position channel
     * @return a pointer to the channel
     */
    AnimChannelMove *GetPositionChannel() {return &mChannel;}
};

#endif //CANADIANEXPERIENCE_ACTOR_H
