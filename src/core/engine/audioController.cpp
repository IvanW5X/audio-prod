#include "audioController.h"
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

void AudioController::init()
{
    audioEngine = std::make_unique<AudioEngine>();

    audioEngine->init(&taskQueue);

    // TODO: this should be last thing to do
    // audioEngine->start();
}