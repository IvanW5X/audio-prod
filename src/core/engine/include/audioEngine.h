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
        bool loadAudioFile(const std::string& FilePath, AudioFileData_T &outAudioData);

        //--------------------------------------------------
        // Plays an audio file given a populated AudioFileData_T
        void playAudioData(const AudioFileData_T &AudioData);

    private:
        TaskQueue_T *tasksQueue;

        // 
        static int32_t audioCallback(void *outputBuffer, void * /*inputBuffer*/,
                                     uint32_t bufferFrames, double /*streamTime*/,
                                     RtAudioStreamStatus status, void *userData);

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
