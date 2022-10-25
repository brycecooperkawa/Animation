/**
 * @file DrawableTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

class DrawableMock : public Drawable
{
public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    virtual bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest,Constructor)
{
    DrawableMock drawable(L"Joe");
    ASSERT_EQ(std::wstring(L"Joe"), drawable.GetName());
}

TEST(DrawableTest,Position)
{
    DrawableMock drawable(L"LeBron");

    wxPoint point=wxPoint(0,0);

    //test default value
    ASSERT_EQ(point,drawable.GetPosition());

    //make new value, test setter and getter
    wxPoint point2=wxPoint(999,23);
    drawable.SetPosition(point2);
    ASSERT_EQ(point2,drawable.GetPosition());
}

TEST(DrawableTest,Rotation)
{
    DrawableMock drawable(L"Eli");

    //test default value
    double base=0;
    ASSERT_NEAR(base,drawable.GetRotation(),0.00001);

    //set new value, test setter and getter
    double value=999;
    drawable.SetRotation(value);
    ASSERT_NEAR(value,drawable.GetRotation(),0.00001);
}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}




