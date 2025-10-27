/************************************************************
 * File: audioTests.cpp
 * 
 * Description: Tests for sending audio data to output device
 * 
 * Date: 2025-10-25
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include <gtest/gtest.h>
#include "RtAudio.h"
#include "audioController.h"
#include "audioEngine.h"

TEST(AudioEngineTest, LoadValidAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioFileData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.loadAudioFile("tests/testFiles/Billie Jean 4.mp3", audioData);

    EXPECT_TRUE(loadSuccess);
    EXPECT_TRUE(audioData.samples.size() > 0);
}

TEST(AudioEngineTest, LoadInvalidAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioFileData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadDoesNotExist = engine.loadAudioFile("tests/testFiles/fakeFile.mp3", audioData);
    EXPECT_FALSE(loadDoesNotExist);
}

TEST(AudioEngineTest, LoadEmptyAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioFileData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadInvalid = engine.loadAudioFile("tests/testFiles/emptyFile.mp3", audioData);
    EXPECT_FALSE(loadInvalid);
}

TEST(AudioEngineTest, PlayAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioFileData_T audioData;

    bool initSSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.loadAudioFile("tests/testFiles/Billie Jean 4.mp3", audioData);
    EXPECT_TRUE(loadSuccess);
    EXPECT_TRUE(audioData.samples.size() > 0);
    
    engine.playAudioData(audioData);

    std::string ans;
    std::cout << "Did you hear data?\n (y) (n): " << std::endl;
    std::cin >> ans;

    if (ans.empty() || ans[0] == 'n')
    {
        FAIL();
    }
    else if (ans[0] == 'y')
    {
        SUCCEED();
    }
}