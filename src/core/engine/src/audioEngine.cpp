/************************************************************
 * File: audioEngine.cpp
 * 
 * Description: Implementation file for AudioEngine class
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include "audioEngine.h"

// Constructor
AudioEngine::AudioEngine() :
    tasksQueue(nullptr)
{

}

// Destructer
AudioEngine::~AudioEngine()
{
    
}

// Initializes the engine
void AudioEngine::init(TaskQueue_T *tasksQueue)
{
    this->tasksQueue = tasksQueue;
}

// TODO: simple test for input output
void AudioEngine::playSinWave(void* outputBuffer, void* /*inputBuffer*/,
                  unsigned int nBufferFrames,
                  double streamTime,
                  RtAudioStreamStatus status,
                  void* userData)
{
    double* buffer = static_cast<double*>(outputBuffer);
    double* phase = static_cast<double*>(userData);
    double frequency = 440.0; // A4
    double sampleRate = 48000.0;

    if (status) std::cout << "Stream underflow detected!" << std::endl;

    for (unsigned int i = 0; i < nBufferFrames; ++i)
    {
        buffer[i] = 0.2 * sin(2.0 * 3.1415926 * frequency * (*phase) / sampleRate);
        (*phase) += 1.0;
        if (*phase >= sampleRate) *phase -= sampleRate;
    }
}
