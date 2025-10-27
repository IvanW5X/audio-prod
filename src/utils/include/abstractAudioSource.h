/************************************************************
 * File: audioSource.h
 * 
 * Description: The AudioSource class provides an abstract
 *  class for an audio source interface. Sources can come from
 *  any sound source, such as a file or tone.
 * 
 * Date: 2025-10-26
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include <stdint.h>

class AbstractAudioSource
{
    public:
        //--------------------------------------------------
        // Virtual Destructer
        virtual ~AbstractAudioSource() = default;

        //--------------------------------------------------
        // Virtual function to populate output buffer with numFrames across numChannels
        virtual bool render(float *outputBuffer, size_t numFrames, uint32_t numChannels) = 0;

    private:
};
