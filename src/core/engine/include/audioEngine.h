/************************************************************
 * File: audioEngine.h
 * 
 * Description: The AudioEngine class should serve as a worker
 *  thread for the AudioController and is the low level class
 *  responsible for processing audio data
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include "RtAudio.h"
#include <sndfile.h>
#include <cmath>
#include <common.h>
#include <commands.h>
#include <syncedQueue.h>

using TaskQueue_T = SyncedQueue<AudioCmd::Command_T, TaskQueueCapacity>;

class AudioEngine
{
    public:
        //--------------------------------------------------
        // Constructor
        AudioEngine();

        //--------------------------------------------------
        // Destructer
        ~AudioEngine();

        //--------------------------------------------------
        // Initialize function, returns true on success
        bool init(TaskQueue_T *tasksQueue);

        //--------------------------------------------------
        // Loads an audio file into memory, returns true on success
        bool loadAudioFile(const std::string& filePath, AudioFileData_T &outAudioData);

    private:
        TaskQueue_T *tasksQueue;

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
