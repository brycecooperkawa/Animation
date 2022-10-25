/**
 * @file AnimChannelAngle.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:
    /// The angle
    double mAngle;

public:
    /// Default constructor
    AnimChannelAngle() { }

    /// Destructor
    virtual ~AnimChannelAngle() {}

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;

    /**
     * Getter for angle
     * @return the angle
     */
     double GetAngle() { return mAngle; }

     void SetKeyframe(double angle);

protected:

    /// Class that represents a keyframe angle
    class KeyframeAngle : public Keyframe
    {
    private:
        /// The angle
        double mAngle;

        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /// Default constructor (disabled)
        KeyframeAngle() = delete;

        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;

        /// Assignment operator
        void operator=(const KeyframeAngle &) = delete;

        /**
         * Getter for angle
         * @return the angle
         */
        double GetAngle() { return mAngle; }

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

    };

    void Tween(double t) override;

private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;


};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
