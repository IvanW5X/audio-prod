/************************************************************
 * File:
 * 
 * Description: 
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include "audioController.h"

TEST(AudioControllerTest, Initialization) {
    AudioController::instance().init();

    SUCCEED();
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
