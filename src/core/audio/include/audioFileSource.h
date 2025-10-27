/************************************************************
 * File: audioFileSource.h
 * 
 * Description: The AudioFileSource class provides an audio
 *  source interface for file like sources 
 * 
 * Date: 2025-10-26
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include "abstractAudioSource.h"
#include "common.h"

class AudioFileSource : public AbstractAudioSource
{
    public:
        //--------------------------------------------------
        // Constructor
        AudioFileSource(const AudioData_T &data);

        //--------------------------------------------------
        // Populate output buffer with audio data
        bool render(float *outputBuffer, uint32_t numFrames, uint32_t numChannels) override;

        //--------------------------------------------------
        // Getters for internal data
        uint32_t getSampleRate_hz() const { return data.sampleRate_hz; }
        uint32_t getNumChannels() const { return data.channels; }
        uint32_t getCurrentFrame() const { return currentFrame; }

        //--------------------------------------------------
        // Setters for internal data
        void setCurrentFrame(const uint32_t NewFrame) { this->currentFrame = NewFrame; }
    
    private:
        const AudioData_T &data;
        uint32_t currentFrame;
};
