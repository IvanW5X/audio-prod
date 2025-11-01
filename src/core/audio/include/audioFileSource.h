/************************************************************
 * FILE: audioFileSource.h
 * 
 * DESCRIPTION: The AudioFileSource class provides an audio
 *  source interface for file like sources 
 * 
 * DATE: 2025-10-26
 * 
 * AUTHOR: Ivan Wong
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
        void render(float32_t *outputBuffer, uint32_t numFrames) override;

        //--------------------------------------------------
        // Getters for internal data
        uint32_t getNumChannels() const override { return this->data.channels; }
        uint32_t getSampleRate_hz() const override { return this->data.sampleRate_hz; }
        uint32_t getCurrentSampleIndex() const { return this->sampleIndex; }

        //--------------------------------------------------
        // Setters for internal data
        // void setSampleIndex(const uint32_t NewIndex) { this->sampleIndex = NewIndex; }
    
    private:
        const AudioData_T &data;
        uint32_t sampleIndex;
};
