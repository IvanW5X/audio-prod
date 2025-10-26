/************************************************************
 * File: runTests.cpp
 * 
 * Description: Runs all unit tests by default or specific tests
 * 
 * Date: 2025-10-25
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    if (argc > 1)
    {
        // Run specific test case if provided as argument
        ::testing::GTEST_FLAG(filter) = argv[1];
    }
    return RUN_ALL_TESTS();
}
