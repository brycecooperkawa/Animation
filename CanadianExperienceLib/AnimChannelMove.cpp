/**
 * @file AnimChannelMove.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "AnimChannelMove.h"

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param angle Angle for the keyframe.
 */
void AnimChannelMove::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the point
    auto keyframe = std::make_shared<KeyframeMove>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/**
 *
 */
void AnimChannelMove::Tween(double t)
{
    mPoint = wxPoint(int(mKeyframe1->GetPoint().x + t * (mKeyframe2->GetPoint().x - mKeyframe1->GetPoint().x)),
            int(mKeyframe1->GetPoint().y + t * (mKeyframe2->GetPoint().y - mKeyframe1->GetPoint().y)));
}


