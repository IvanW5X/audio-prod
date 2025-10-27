/************************************************************
 * File: audioController.h
 *
 * Description: Implementation file for AudioController class
 *
 * Date: 2025-10-08
 *
 * Author: Ivan Wong
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
