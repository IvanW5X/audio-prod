/************************************************************
 * FILE: toneTest.cpp
 * 
 * DESCRIPTION: Unit tests for ToneGenerator class
 *
 * DATE: 2025-11-01
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#include <gtest/gtest.h>
#include "RtAudio.h"
#include "audioEngine.h"
#include "toneGenerator.h"
#include "toneSource.h"

TEST(ToneGenTest, GenerateTones)
{
    ToneGenerator tg;
    AudioData_T audioData;
    
    audioData = tg.generateTone(ToneGenerator::ToneType_T::SINE);
    ASSERT_TRUE(audioData.samples.size() > 0);
    audioData.samples.clear();

    audioData = tg.generateTone(ToneGenerator::ToneType_T::SQUARE);
    ASSERT_TRUE(audioData.samples.size() > 0);
    audioData.samples.clear();

    audioData = tg.generateTone(ToneGenerator::ToneType_T::TRIANGLE);
    ASSERT_TRUE(audioData.samples.size() > 0);
    audioData.samples.clear();

    audioData = tg.generateTone(ToneGenerator::ToneType_T::SAWTOOTH);
    ASSERT_TRUE(audioData.samples.size() > 0);
}

TEST(ToneGenTest, PlaySineTone)
{
    AudioEngine eng;
    ToneGenerator tg;
    AudioData_T audioData;
    TaskQueue_T tq;
    
    const float32_t Duration_sec = 2.0f;
    const float32_t Amplitude = 1.0f;
    const uint32_t BufferSize = 512u;
    
    eng.init(&tq);
    audioData = tg.generateTone(ToneGenerator::ToneType_T::SINE, Duration_sec, Amplitude);
    ToneSource ts(audioData);

    eng.loadAudioSource(ts, BufferSize);
    eng.startAudioOutputStream();

    // Let it play for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    eng.stopAudioOutputStream();
    EXPECT_TRUE(ts.getCurrentSampleIndex() > 0u);
}

TEST(ToneGenTest, PlaySqaureTone)
{
    AudioEngine eng;
    ToneGenerator tg;
    AudioData_T audioData;
    TaskQueue_T tq;
    
    const float32_t Duration_sec = 2.0f;
    const float32_t Amplitude = 1.0f;
    const uint32_t BufferSize = 512u;
    
    eng.init(&tq);
    audioData = tg.generateTone(ToneGenerator::ToneType_T::SQUARE, Duration_sec, Amplitude);
    ToneSource ts(audioData);

    eng.loadAudioSource(ts, BufferSize);
    eng.startAudioOutputStream();

    // Let it play for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    eng.stopAudioOutputStream();
    EXPECT_TRUE(ts.getCurrentSampleIndex() > 0u);
}

TEST(ToneGenTest, PlayTriangleTone)
{
    AudioEngine eng;
    ToneGenerator tg;
    AudioData_T audioData;
    TaskQueue_T tq;
    
    const float32_t Duration_sec = 2.0f;
    const float32_t Amplitude = 1.0f;
    const uint32_t BufferSize = 512u;
    
    eng.init(&tq);
    audioData = tg.generateTone(ToneGenerator::ToneType_T::TRIANGLE, Duration_sec, Amplitude);
    ToneSource ts(audioData);

    eng.loadAudioSource(ts, BufferSize);
    eng.startAudioOutputStream();

    // Let it play for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    eng.stopAudioOutputStream();
    EXPECT_TRUE(ts.getCurrentSampleIndex() > 0u);
}

TEST(ToneGenTest, PlaySawtoothTone)
{
    AudioEngine eng;
    ToneGenerator tg;
    AudioData_T audioData;
    TaskQueue_T tq;
    
    const float32_t Duration_sec = 2.0f;
    const float32_t Amplitude = 1.0f;
    const uint32_t BufferSize = 512u;
    
    eng.init(&tq);
    audioData = tg.generateTone(ToneGenerator::ToneType_T::SAWTOOTH, Duration_sec, Amplitude);
    ToneSource ts(audioData);

    eng.loadAudioSource(ts, BufferSize);
    eng.startAudioOutputStream();

    // Let it play for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    eng.stopAudioOutputStream();
    EXPECT_TRUE(ts.getCurrentSampleIndex() > 0u);
}