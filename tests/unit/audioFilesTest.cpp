/************************************************************
 * FILE: audioTests.cpp
 * 
 * DESCRIPTION: Tests for sending audio file to output device
 * 
 * DATE: 2025-10-25
 *
 * AUTHOR: Ivan Wong
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
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.readAudioFile("../../tests/testFiles/Billie Jean 4.mp3", audioData);

    EXPECT_TRUE(loadSuccess);
    EXPECT_TRUE(audioData.samples.size() > 0);
}

TEST(AudioEngineTest, LoadInvalidAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadDoesNotExist = engine.readAudioFile("../../tests/testFiles/fakeFile.mp3", audioData);
    EXPECT_FALSE(loadDoesNotExist);
}

TEST(AudioEngineTest, LoadEmptyAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadInvalid = engine.readAudioFile("../../tests/testFiles/emptyFile.mp3", audioData);
    EXPECT_FALSE(loadInvalid);
}

TEST(AudioEngineTest, PlayAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.readAudioFile("../../tests/testFiles/Billie Jean 4.mp3", audioData);
    EXPECT_TRUE(loadSuccess);
    EXPECT_TRUE(audioData.samples.size() > 0);

    std::cout << audioData.samples.size() << std::endl;
    
    AudioFileSource source(audioData);
    bool createdSource = source.getSampleRate_hz() > 0;
    ASSERT_TRUE(createdSource);

    const uint32_t bufferSize = 512u;
    engine.loadAudioSource(source, bufferSize);
    engine.startAudioOutputStream();

    // Let it play for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    ASSERT_TRUE(source.getCurrentSampleIndex() > 0u);
    engine.stopAudioOutputStream();
}