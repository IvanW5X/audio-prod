/************************************************************
 * File: initTests.cpp
 * 
 * Description: Tests for major class initialization functions
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
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
