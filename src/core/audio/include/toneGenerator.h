/************************************************************
 * FILE: toneGenerator.h
 * 
 * DESCRIPTION: The ToneGenerator class creates various audio
 *  tones for testing and signal generation purposes
 * 
 * DATE: 2025-11-01
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include "common.h"
#include <cmath>

#define M_PI 3.14159265358979323846

class ToneGenerator
{
    public:
        enum class ToneType_T
        {
            SINE,
            SQUARE,
            TRIANGLE,
            SAWTOOTH
        };

        //--------------------------------------------------
        // Constructor
        ToneGenerator();

        //--------------------------------------------------
        // Destructor
        ~ToneGenerator();

        //--------------------------------------------------
        // Generates a tone of specified type, frequency, amplitude, and duration
        AudioData_T generateTone(const ToneType_T ToneType,
                                 const float32_t Duration_sec = DefaultDuration_sec,
                                 const float32_t Amplitude = DefaultAmplitude,
                                 const uint32_t Frequency_hz = DefaultFrequency_hz,
                                 const uint32_t SampleRate_hz = DefaultSampleRate_hz );

    private:
        // TODO: might not need this
        uint32_t frequency_hz;
        float32_t amplitude;

        // Constants
        static const uint32_t DefaultSampleRate_hz = 44100u;
        static const uint32_t DefaultFrequency_hz = 440u;
        static constexpr float32_t DefaultDuration_sec = 1.0f;
        static constexpr float32_t DefaultAmplitude = 0.5f;

        // Disable copy constructor and assignment operator overload
        ToneGenerator(const ToneGenerator&) = delete;
        ToneGenerator& operator=(const ToneGenerator&) = delete;
};
