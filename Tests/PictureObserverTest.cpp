/**
 * @file PictureObserverTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <PictureObserver.h>
#include <Picture.h>

class PictureObserverMock : public PictureObserver
{
public:
    PictureObserverMock() : PictureObserver() {}
    virtual void UpdateObserver() override { mUpdated = true; }
    bool mUpdated = false;

};

TEST(PictureObserverTest, Construct) {
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, GetPicture){
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    //test if the picture is correctly gotten
    ASSERT_EQ(observer.GetPicture(),picture);

    // Allocate a second Picture object
    auto picture2 = std::make_shared<Picture>();
    // And set it for the observer:
    observer.SetPicture(picture2);
    //test if the picture is correctly gotten
    ASSERT_EQ(observer.GetPicture(),picture2);

}

TEST(PictureObserverTest, TwoObservers) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create two mock observer objects
    PictureObserverMock observer1;
    PictureObserverMock observer2;

    // And set it for the observer:
    observer1.SetPicture(picture);
    observer2.SetPicture(picture);

    picture->UpdateObservers();

    //make sure that both observers are updated
    ASSERT_TRUE(observer1.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, TwoObserversDestory) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create two mock observer objects
    PictureObserverMock observer1;

    observer1.SetPicture(picture);

    //create and destroy the second observer
    {
        PictureObserverMock observer2;

        // And set it for the observer:
        observer2.SetPicture(picture);
    }

    picture->UpdateObservers();

    ASSERT_TRUE(observer1.mUpdated);

}