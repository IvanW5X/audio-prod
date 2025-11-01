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
#include "audioEngine.h"

TEST(EngineTest, LoadValidAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.readAudioFile("../../tests/testFiles/Billie Jean 4.mp3", audioData);

    EXPECT_TRUE(loadSuccess);
    EXPECT_TRUE(audioData.samples.size() > 0);
}

TEST(EngineTest, LoadInvalidAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadDoesNotExist = engine.readAudioFile("../../tests/testFiles/fakeFile.mp3", audioData);
    EXPECT_FALSE(loadDoesNotExist);
}

TEST(EngineTest, LoadEmptyAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSuccess = engine.init(&taskQueue);
    bool loadInvalid = engine.readAudioFile("../../tests/testFiles/emptyFile.mp3", audioData);
    EXPECT_FALSE(loadInvalid);
}

TEST(EngineTest, PlayAudioFile)
{
    AudioEngine engine;
    TaskQueue_T taskQueue;
    AudioData_T audioData;

    bool initSSuccess = engine.init(&taskQueue);
    bool loadSuccess = engine.readAudioFile("../../tests/testFiles/Billie Jean 4.mp3", audioData);
    EXPECT_TRUE(audioData.samples.size() > 0);

    AudioFileSource source(audioData);
    bool createdSource = source.getSampleRate_hz() > 0;
    ASSERT_TRUE(createdSource);

    const uint32_t bufferSize = 512u;
    engine.loadAudioSource(source, bufferSize);
    engine.startAudioOutputStream();

    // Let it play for 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    engine.stopAudioOutputStream();
    ASSERT_TRUE(source.getCurrentSampleIndex() > 0u);
}