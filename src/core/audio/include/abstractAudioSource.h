/************************************************************
 * File: abstractAudioSource.h
 * 
 * Description: The AbstractAudioSource class provides an abstract
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
#include <common.h>

class AbstractAudioSource
{
    public:
        //--------------------------------------------------
        // Virtual Destructor
        virtual ~AbstractAudioSource() = default;

        //--------------------------------------------------
        // Virtual function to populate output buffer with numFrames
        virtual void render(float32_t *outputBuffer, uint32_t numFrames) = 0;

        //--------------------------------------------------
        // Required getters
        virtual uint32_t getNumChannels() const = 0;
        virtual uint32_t getSampleRate_hz() const = 0;

    private:
};

// Wrapper to use abstract audio sources
struct PlaybackContext
{
    AbstractAudioSource *source = nullptr;
};
