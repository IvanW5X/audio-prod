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

bool AudioFileSource::render(float32_t *outputBuffer, uint32_t numFrames, uint32_t numChannels)
{
    bool active = true;
    const uint32_t TotalFrames = data.samples.size() / data.channels;
    const uint32_t OutChannels = std::min(numChannels, data.channels);  // Use the smaller of the two to prevent buffer overrun

    for (uint32_t frame = 0; frame < numFrames && currentFrame < TotalFrames; frame++)
    {
        // For each output frame
        for (uint32_t ch = 0; ch < OutChannels; ch++)
        {
            // Calculate indices for both input and output buffers
            uint32_t outputIndex = frame * numChannels + ch;
            uint32_t inputIndex = currentFrame * data.channels + ch;
            outputBuffer[outputIndex] = data.samples[inputIndex];
        }
        
        // Fill remaining channels with silence if output has more channels than input
        for (uint32_t ch = OutChannels; ch < numChannels; ch++)
        {
            outputBuffer[frame * numChannels + ch] = 0.0f;
        }
        currentFrame++;
    }
    // Fill remaining frames with silence if we've reached the end
    for (uint32_t frame = currentFrame; frame < numFrames; frame++)
    {
        for (uint32_t ch = 0; ch < numChannels; ch++)
        {
            outputBuffer[frame * numChannels + ch] = 0.0f;
        }
    }

    // Return false when we've reached the end of the audio data
    active = (currentFrame < TotalFrames);
    return active;
}
