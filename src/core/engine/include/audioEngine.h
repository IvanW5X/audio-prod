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
        // Initialize funxtion
        void init(TaskQueue_T *tasksQueue);

        //--------------------------------------------------
        // TODO: debug
        void playSinWave(void* outputBuffer, void* /*inputBuffer*/,
                  unsigned int nBufferFrames,
                  double streamTime,
                  RtAudioStreamStatus status,
                  void* userData);

    private:
        TaskQueue_T *tasksQueue;

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
