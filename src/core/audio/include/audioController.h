/************************************************************
 * FILE: audioController.cpp
 * 
 * DESCRIPTION: The AudioController class is a API wrapper
 *  for the low level AudioEngine class and handles the
 *  multithreading architecture for backend/audio processing.
 * 
 * This singleton class is the class that handles the interface
 *  for the engine and should be used to
 *
 * DATE: 2025-10-08
 *
 * AUTHOR: Ivan Wong
 *
 ************************************************************/

#pragma once

#include "audioEngine.h"
#include "memory"

class AudioController
{
    public:
        //--------------------------------------------------
        // Thread safe singleton
        static AudioController &instance()
        {
            static AudioController instance;
            return instance;
        }

        //--------------------------------------------------
        // Initialize function, returns true on success
        bool init();

        //--------------------------------------------------
        

    private:
        //--------------------------------------------------
        // Constructor, make private to prevent direct instantiation
        AudioController();
        
        //--------------------------------------------------
        // Destructor
        ~AudioController();

        // Member variables
        TaskQueue_T taskQueue;
        std::unique_ptr<AudioEngine> audioEngine;

        // Disable copy constructor and assignment operator overload
        AudioController(const AudioController &) = delete;
        AudioController &operator=(const AudioController &) = delete;
};
