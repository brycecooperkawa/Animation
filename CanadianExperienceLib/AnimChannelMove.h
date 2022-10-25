/**
 * @file AnimChannelMove.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELMOVE_H
#define CANADIANEXPERIENCE_ANIMCHANNELMOVE_H

#include "AnimChannel.h"

/**
 * Animation channel for moving.
 */
class AnimChannelMove : public AnimChannel {
private:
    /// The point
    wxPoint mPoint;

public:
    /// Default constructor
    AnimChannelMove() { }

    /// Destructor
    virtual ~AnimChannelMove() {}

    /// Copy constructor (disabled)
    AnimChannelMove(const AnimChannelMove &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelMove &) = delete;

    void SetKeyframe(wxPoint point);

    /**
     * Gets the point value
     * @return the point
     */
    wxPoint GetPoint() {return mPoint;}

protected:
    void Tween(double t);

    class KeyframeMove : public Keyframe
    {
    private:
        ///the point
        wxPoint mPoint;

        /// The channel associated with
        AnimChannelMove *mChannel;

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeMove(AnimChannelMove *channel, wxPoint point) :
        Keyframe(channel), mChannel(channel), mPoint(point) {}

        /// Default constructor (disabled)
        KeyframeMove() = delete;

        /// Copy constructor (disabled)
        KeyframeMove(const KeyframeMove &) = delete;

        /// Assignment operator
        void operator=(const KeyframeMove &) = delete;

        /**
         * Gets the point value
         * @return the point
         */
        wxPoint GetPoint() {return mPoint;}

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mPoint = mPoint; }

    };

private:
    /// The first move keyframe
    KeyframeMove *mKeyframe1 = nullptr;

    /// The second move keyframe
    KeyframeMove *mKeyframe2 = nullptr;


};

#endif //CANADIANEXPERIENCE_ANIMCHANNELMOVE_H
