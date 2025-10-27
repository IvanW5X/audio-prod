/************************************************************
 * File: audioFileSource.cpp
 * 
 * Description: Implementation file for AudioFileSource class
 * 
 * Date: 2025-10-26
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include "audioFileSource.h"
#include <iostream>

AudioFileSource::AudioFileSource(const AudioData_T &data) :
    data(data),
    sampleIndex(0)
{}

void AudioFileSource::render(float32_t *outputBuffer, uint32_t numFrames)
{
    const uint32_t TotalSamples = data.samples.size() / data.channels;

    for (uint32_t frame = 0; frame < numFrames; frame++)
    {
        for (uint32_t ch = 0; ch < data.channels; ch++)
        {
            const uint32_t OutIndex = (frame * data.channels) + ch;

            if (sampleIndex < TotalSamples)
            {
                outputBuffer[OutIndex] = data.samples[sampleIndex++];
            }
            else
            {
                // Silence
                outputBuffer[OutIndex] = 0.0f;
            }
        }
    }
}
