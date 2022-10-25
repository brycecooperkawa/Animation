/**
 * @file TimelineTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>
#include <AnimChannelAngle.h>
#include <AnimChannelMove.h>

TEST(TimelineTest,numFrames)
{
    Timeline timeline;

    //test default
    ASSERT_EQ(timeline.GetNumFrames(),300);

    //set new num of frames
    timeline.SetNumFrames(999);

    //test the setter
    ASSERT_EQ(timeline.GetNumFrames(),999);
}

TEST(TimelineTest,frameRate)
{
    Timeline timeline;

    //test default
    ASSERT_EQ(timeline.GetFrameRate(),30);

    //set new frame rate
    timeline.SetFrameRate(99);

    //test the setter
    ASSERT_EQ(timeline.GetFrameRate(),99);
}

TEST(TimelineTest,currentTime)
{
    Timeline timeline;

    //test default
    ASSERT_NEAR(timeline.GetCurrentTime(),0,0.0001);

    //set new current time
    timeline.SetCurrentTime(9.9);

    //test the setter
    ASSERT_NEAR(timeline.GetCurrentTime(),9.9,0.0001);
}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;
    AnimChannelMove channel2;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());

    timeline.AddChannel(&channel2);
    ASSERT_EQ(&timeline, channel2.GetTimeline());
}