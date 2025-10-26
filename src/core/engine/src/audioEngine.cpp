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
bool AudioEngine::init(TaskQueue_T *tasksQueue)
{
    bool success = true;

    if (!tasksQueue)
    {
        // TODO: handle error in a different way
        success = false;
    }
    this->tasksQueue = tasksQueue;

    return success;
}

// Loads an audio file into memory
bool AudioEngine::loadAudioFile(const std::string &filePath,
                                AudioFileData_T &outAudioData)
{
    SF_INFO sfInfo;
    SNDFILE *inFile = sf_open(filePath.c_str(), SFM_READ, &sfInfo);
    
    if (!inFile)
    {
        std::cerr << "Error: could not open audio file: "
                  << filePath << "\n"
                  << "Error message: " << sf_strerror(nullptr) << std::endl;

        return false;
    }
    // Read audio data
    int64_t numFrames = sfInfo.frames;
    outAudioData.channels = sfInfo.channels;
    outAudioData.readIndex = 0;
    outAudioData.samples.resize(numFrames * sfInfo.channels);
    sf_count_t framesRead = sf_read_float(inFile, outAudioData.samples.data(), numFrames);

    // TODO: handle error better later
    if (framesRead != numFrames)
    {
        sf_close(inFile);

        std::cerr << "Error: could not read all frames from audio file: "
                  << filePath << "\n"
                  << "Frames read: " << framesRead << "\nExpected frames: " << numFrames << std::endl;

        return false;
    }
    sf_close(inFile);

    // TODO: remove later
    std::cout << "Loaded audio file: " << filePath << "\n"
              << "Sample rate: " << sfInfo.samplerate << "\n"
              << "Channels: " << sfInfo.channels << "\n"
              << "Total frames: " << sfInfo.frames << std::endl;

    return true;
}
