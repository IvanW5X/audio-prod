/************************************************************
 * FILE: audioEngine.h
 * 
 * DESCRIPTION: The AudioEngine class should serve as a worker
 *  thread for the AudioController and is the low level class
 *  responsible for processing audio data
 * 
 * DATE: 2025-10-08
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include "RtAudio.h"
#include <sndfile.h>
#include <memory>
#include "audioFileSource.h"
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
        // Destructor
        ~AudioEngine();

        //--------------------------------------------------
        // Initialize function, returns true on success
        bool init(TaskQueue_T *tasksQueue);

        //--------------------------------------------------
        // Loads an audio file into memory, returns true on success
        bool readAudioFile(const std::string& FilePath, AudioData_T &outAudioData);

        //--------------------------------------------------
        // Loads an audio source into the engine
        void loadAudioSource(AbstractAudioSource &audioSource, uint32_t bufferSize);

        //--------------------------------------------------
        // Starts the audio streaming process
        void startAudioOutputStream();

        //--------------------------------------------------
        // Stops the audio output streaming process
        void stopAudioOutputStream();

    private:
        TaskQueue_T *tasksQueue;
        PlaybackContext currentContext;

        // TODO: move to device manager class later
        std::unique_ptr<RtAudio> dac;

        // Call back function when audio output stream starts
        static int32_t streamAudioCallback(void *outputBuffer, void * /*inputBuffer*/,
                                           uint32_t bufferFrames, double /*streamTime*/,
                                           RtAudioStreamStatus status, void *userData);

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
