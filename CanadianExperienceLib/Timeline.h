/**
 * @file Timeline.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINE_H
#define CANADIANEXPERIENCE_TIMELINE_H

class AnimChannel;

/**
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline {
private:
    /// The number of frames
    int mNumFrames = 300;
    
    /// the frame rate
    int mFrameRate = 30;
    
    /// The current time
    double mCurrentTime = 0;

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;

public:
    Timeline();

    /// Copy constructor (disabled)
    Timeline(const Timeline &) = delete;
    
    /// Assignment operator
    void operator=(const Timeline &) = delete;

    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    void SetCurrentTime(double t);

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return double(mNumFrames)/mFrameRate; }

    /** Get the current frame.
     *
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return mCurrentTime*mFrameRate; }

    void AddChannel(AnimChannel *channel);

    /**
     * Get the channels
     * @return the vector of channels
     */
    std::vector<AnimChannel *> GetChannels() {return mChannels;}
};

#endif //CANADIANEXPERIENCE_TIMELINE_H
