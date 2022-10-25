/**
 * @file AnimChannelAngleTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>


TEST(AnimChannelAngleTest,Name)
{
    AnimChannelAngle channel;

    channel.SetName(L"Saquon");

    ASSERT_EQ(channel.GetName(),L"Saquon");
}