/************************************************************
 * FILE: audioFileSource.cpp
 * 
 * DESCRIPTION: Implementation file for AudioFileSource class
 * 
 * DATE: 2025-10-26
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#include "audioFileSource.h"
#include <iostream>

// Constructor
AudioFileSource::AudioFileSource(const AudioData_T data) :
    data(data),
    sampleIndex(0)
{}

void AudioFileSource::render(float32_t *outputBuffer, uint32_t numFrames)
{
    const uint32_t TotalFrames = static_cast<uint32_t>(data.samples.size() / data.channels);

    for (uint32_t frame = 0; frame < numFrames; frame++)
    {
        for (uint32_t ch = 0; ch < data.channels; ch++)
        {
            const uint32_t OutIndex = (frame * data.channels) + ch;

            if (sampleIndex < TotalFrames)
            {
                const uint32_t InIndex = (sampleIndex * data.channels) + ch;
                outputBuffer[OutIndex] = data.samples[InIndex];
            }
            else
            {
                // Silence
                outputBuffer[OutIndex] = 0.0f;
            }
        }
        sampleIndex++;
    }
}
