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
    currentFrame(0)
{}

bool AudioFileSource::render(float *outputBuffer, uint32_t numFrames, uint32_t numChannels)
{
    bool active = true;
    const uint32_t TotalFrames = data.samples.size() / data.channels;

    for (uint32_t frame = 0; frame < numFrames; frame++)
    {
        for (uint32_t ch = 0; ch < data.channels; ch++)
        {
            uint32_t outputIndex = (frame * data.channels) + ch;

            if (currentFrame < TotalFrames)
            {
                outputBuffer[outputIndex] = data.samples[currentFrame++];
            }
            else
            {
                outputBuffer[outputIndex] = 0.0f;
            }
        }
        if (currentFrame >= TotalFrames)
        {
            active = false;
            break;
        }
    }
    return active;
}
