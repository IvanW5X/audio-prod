/************************************************************
 * FILE: audioController.h
 *
 * DESCRIPTION: Implementation file for AudioController class
 *
 * DATE: 2025-10-08
 *
 * AUTHOR: Ivan Wong
 *
 ************************************************************/

#include "audioController.h"

AudioController::AudioController() :
    taskQueue(),
    audioEngine(nullptr)
{

}

AudioController::~AudioController()
{

}

bool AudioController::init()
{
    bool success = true;

    audioEngine = std::make_unique<AudioEngine>();
    
    if (!audioEngine)
    {
        success = false;
    }
    success &= audioEngine->init(&taskQueue);


    // TODO: this should be last thing to do
    // audioEngine->start();

    // TODO: handle failure cases better
    return success;
}
