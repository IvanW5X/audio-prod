/************************************************************
 * FILE: toneSource.h
 * 
 * DESCRIPTION: The ToneSource class provides an audio 
 *  source interface for generated tones
 * 
 * DATE: 2025-11-01
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#include "abstractAudioSource.h"
#include "common.h"

class ToneSource :public AbstractAudioSource
{
    public:
        //--------------------------------------------------
        // Constructor
        ToneSource(const AudioData_T data);

        //--------------------------------------------------
        // Populate output buffer with audio data
        void render(float32_t *outputBuffer, uint32_t numFrames) override;

        //--------------------------------------------------
        // Getters for internal data
        uint32_t getNumChannels() const override { return this->data.channels; }
        uint32_t getSampleRate_hz() const override { return this->data.sampleRate_hz; }
        uint32_t getCurrentSampleIndex() const { return this->sampleIndex; }
    
    private:
        const AudioData_T data;
        uint32_t sampleIndex;
};
