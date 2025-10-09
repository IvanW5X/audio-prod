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
