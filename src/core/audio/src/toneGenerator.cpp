/************************************************************
 * FILE: toneGenerator.cpp
 *
 * DESCRIPTION: The ToneGenerator implementation file
 *
 * DATE: 2025-11-01
 *
 * AUTHOR: Ivan Wong
 *
 ************************************************************/

#include "toneGenerator.h"

// Constructor
ToneGenerator::ToneGenerator()
{

}

// Destructor
ToneGenerator::~ToneGenerator()
{

}

AudioData_T ToneGenerator::generateTone(const ToneType_T ToneType,
                                        const uint32_t Frequency_hz,
                                        const uint32_t SampleRate_hz,
                                        const float32_t Amplitude,
                                        const float32_t Duration_s)
{
    AudioData_T audioData;
    audioData.sampleRate_hz = SampleRate_hz;

    // TODO: support multiple channels later
    audioData.channels = 1u;

    const uint32_t TotalSamples = SampleRate_hz * static_cast<uint32_t>(Duration_s);
    audioData.samples.resize(TotalSamples);

    const float32_t TwoPiF = 2.0f * static_cast<float32_t>(M_PI) * static_cast<float32_t>(Frequency_hz);

    for (uint32_t i = 0; i < TotalSamples; i++)
    {
        const float32_t t = static_cast<float32_t>(i) / static_cast<float32_t>(SampleRate_hz);
        float32_t sampleValue = 0.0f;

        switch (ToneType)
        {
            case ToneType_T::SINE:
                sampleValue = Amplitude * std::sin(TwoPiF * t);
                break;

            case ToneType_T::SQUARE:
                sampleValue = Amplitude * (std::sin(TwoPiF * t) >= 0.0f ? 1.0f : -1.0f);
                break;

            case ToneType_T::TRIANGLE:
                sampleValue = (2.0f * Amplitude / static_cast<float32_t>(M_PI)) *
                              std::asin(std::sin(TwoPiF * t));
                break;

            case ToneType_T::SAWTOOTH:
                sampleValue = (2.0f * Amplitude / static_cast<float32_t>(M_PI)) *
                              (TwoPiF * t - static_cast<float32_t>(M_PI) *
                              std::floor(0.5f + TwoPiF * t / static_cast<float32_t>(M_PI)));
                break;
        }
        audioData.samples[i] = sampleValue;
    }
    return audioData;
}
