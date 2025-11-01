/************************************************************
 * FILE: toneSource.cpp
 * 
 * DESCRIPTION: The ToneSource implementation file
 * 
 * DATE: 2025-11-01
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#include "toneSource.h"
#include <iostream>

// Constructor
ToneSource::ToneSource(const AudioData_T data) :
    data(data),
    sampleIndex(0u)
{}

// Populate output buffer with audio data
void ToneSource::render(float32_t *outputBuffer, uint32_t numFrames)
{
    for (uint32_t frame = 0; frame < numFrames; frame++)
    {
        for (uint32_t ch = 0; ch < data.channels; ch++)
        {
            const uint32_t OutIndex = (frame * data.channels) + ch;
            outputBuffer[OutIndex] = data.samples[sampleIndex++];
        }
    }
}
