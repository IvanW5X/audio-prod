/************************************************************
 * FILE: runTests.cpp
 * 
 * DESCRIPTION: Runs all unit tests by default or specific
 *  tests if running executable directly.
 *  
 * NOTE: The audioFilesTest may fail due to incorrect path.
 *       The tests were written assuming ctest will be
 *       running from the build/tests/unit/ directory.
 * 
 * DATE: 2025-10-25
 * 
 * AUTHOR: Ivan Wong
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
