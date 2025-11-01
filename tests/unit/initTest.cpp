/************************************************************
 * FILE: initTests.cpp
 * 
 * DESCRIPTION: Tests for major class initialization functions
 * 
 * DATE: 2025-10-08
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#include <gtest/gtest.h>
#include "audioController.h"
#include "audioEngine.h"

TEST(AudioEngineTest, Initialization) {
    AudioEngine engine;
    TaskQueue_T taskQueue;

    bool success = engine.init(&taskQueue);

    EXPECT_TRUE(success);
}

TEST(AudioControllerTest, Initialization) {
    bool success = AudioController::instance().init();

    EXPECT_TRUE(success);
}
