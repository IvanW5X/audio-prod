/************************************************************
 * File: audioController.cpp
 * 
 * Description:
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
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
        // Initialize function
        void init();

    private:
        //--------------------------------------------------
        // Constructor, make private to prevent direct instantiation
        AudioController();
        
        //--------------------------------------------------
        // Destructer
        ~AudioController();

        // Member variables
        TaskQueue_T taskQueue;
        std::unique_ptr<AudioEngine> audioEngine;

        // Disable copy constructor and assignment operator overload
        AudioController(const AudioController &) = delete;
        AudioController &operator=(const AudioController &) = delete;
};
