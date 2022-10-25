/**
 * @file Picture.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PICTURE_H
#define CANADIANEXPERIENCE_PICTURE_H

class PictureObserver;
class Actor;

#include "Timeline.h"

/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// the actors in the picture
    std::vector<std::shared_ptr<Actor>> mActors;

    /// The animation timeline
    Timeline mTimeline;

public:
    /**
     * Constructor
     */
    Picture() {}

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddActor(std::shared_ptr<Actor> actor);

    /**
     * Get a pointer to the Timeline object
     * @return Pointer to the Timeline object
     */
    Timeline *GetTimeline() {return &mTimeline;}

    /** Iterator that iterates over the collection of actors*/
    class ActorIter
    {
    public:
        /**
         * Constructor
         * @param picture The picture we are iterating over
         * @param pos The position in the collection
         */
        ActorIter(Picture *picture, int pos) : mPicture(picture), mPos(pos) {}

        /**
         * Compare two iterators
         * @param other The other iterator we are comparing to
         * @return  true if this position is not equal to the other position
         */
        bool operator!=(const ActorIter& other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Actor> operator *() const { return mPicture->mActors[mPos]; }

        /**
         * Increment the iterator
         * @return Reference to this iterator
         */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        Picture* mPicture;   ///< City we are iterating over
        int mPos;       ///< Position in the collection
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    ActorIter begin() { return ActorIter(this, 0); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    ActorIter end() { return ActorIter(this, mActors.size()); }

    void SetAnimationTime(double time);

    void SetTimeline(Timeline* timeline);
};

#endif //CANADIANEXPERIENCE_PICTURE_H
