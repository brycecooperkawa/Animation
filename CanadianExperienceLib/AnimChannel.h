/**
 * @file AnimChannel.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;

/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:
    /// the name
    std::wstring mName;

    /// keyframe1
    int mKeyframe1=-1;

    /// keyframe2
    int mKeyframe2=-1;

    /// The timeline object
    Timeline *mTimeline = nullptr;

public:
    /// Destructor
    virtual ~AnimChannel() {}

    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;

    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    /**
     * Getter for name
     * @return the name
     */
     std::wstring GetName() const { return mName; }
     /**
      * Set the name
      * @param name the name to be set
      */
     void SetName(std::wstring name) { mName=name;}

     bool IsValid();

     void SetFrame(int currFrame);

     /**
      * Getter for timeline
      * @return the timeline
      */
      Timeline* GetTimeline() { return mTimeline; }
      /**
       * Set the timeline
       * @param timeline the timeline being set
       */
       void SetTimeline(Timeline *timeline) { mTimeline=timeline; }

protected:
    /// Default constructor
    AnimChannel() { }

    /// Class that represents a keyframe
    class Keyframe
    {
    private:
        /// The frame
        int mFrame;

        /// The channel this keyframe is associated with
        AnimChannel *mChannel;

    public:
        /// Default constructor (disabled)
        Keyframe() = delete;

        /// Copy constructor (disabled)
        Keyframe(const Keyframe &) = delete;

        /// Assignment operator
        void operator=(const Keyframe &) = delete;

        /**
         * Getter for frame
         * @return the frame
         */
         int GetFrame() {return mFrame;}
         /**
          * Set the frame
          * @param the value to set the frame to
          */
          void SetFrame(int frame) { mFrame=frame; }

          virtual void UseAs1()=0;
          virtual void UseAs2()=0;
          virtual void UseOnly()=0;

    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}
    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    virtual void Tween(double t) = 0;

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:
    void DeleteKeyframe(int frame);

};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
