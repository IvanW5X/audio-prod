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
    tasksQueue(nullptr),
    dac(nullptr)
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
    this->dac = std::make_unique<RtAudio>();

    return success;
}

// Loads an audio file into memory
bool AudioEngine::loadAudioFile(const std::string &FilePath, AudioData_T &outAudioData)
{
    SF_INFO sfInfo;
    SNDFILE *inFile = sf_open(FilePath.c_str(), SFM_READ, &sfInfo);
    
    if (!inFile)
    {
        std::cerr << "Error: could not open audio file: "
                  << FilePath << "\n"
                  << "Error message: " << sf_strerror(nullptr) << std::endl;

        return false;
    }
    // Set audio data
    int64_t numFrames = sfInfo.frames;
    outAudioData.sampleRate_hz = sfInfo.samplerate;
    outAudioData.channels = sfInfo.channels;
    outAudioData.samples.resize(numFrames * sfInfo.channels);
    sf_count_t framesRead = sf_read_float(inFile, outAudioData.samples.data(), numFrames);

    sf_close(inFile);

    // TODO: handle error better later
    if (framesRead != numFrames)
    {
        std::cerr << "Error: could not read all frames from audio file: "
                  << FilePath << "\n"
                  << "Frames read: " << framesRead << "\nExpected frames: " << numFrames << std::endl;

        return false;
    }
    // TODO: remove later
    std::cout << "Loaded audio file: " << FilePath << "\n"
              << "Sample rate: " << sfInfo.samplerate << "\n"
              << "Channels: " << sfInfo.channels << "\n"
              << "Total frames: " << sfInfo.frames << std::endl;

    return true;
}

// Plays audio given a valid AudioFileSource
void AudioEngine::playAudioFile(AudioFileSource &audioData)
{
    // TODO: error handle better
    if (dac->getDeviceCount() < 1)
    {
        std::cerr << "Error: No output device found" << std::endl;
        return;
    }
    // TODO: support multiple context sources later
    currentContext.source = &audioData;
    RtAudio::StreamParameters outputParams;
    outputParams.deviceId = dac->getDefaultOutputDevice();
    outputParams.nChannels = audioData.getNumChannels();
    outputParams.firstChannel = 0u;

    uint32_t bufferSize = 512u;
    const bool IsErrorOccurred = dac->openStream(&outputParams, nullptr /* inputParams */,
                                                RTAUDIO_FLOAT32, audioData.getSampleRate_hz(), &bufferSize, // Audio settings
                                                &AudioEngine::streamAudioCallback, (void *)&currentContext) // Function and user data
                                                == RTAUDIO_SYSTEM_ERROR;

    if (IsErrorOccurred || !dac->isStreamOpen())
    {
        std::cerr << "Error: could not open audio stream" << std::endl;
        return;
    }
    dac->startStream();
}

// RtAudio callback function, plays audio from arbitrary context source
int32_t AudioEngine::streamAudioCallback(void *outputBuffer, void * /*inputBuffer*/,
                                         uint32_t bufferFrames, double /*streamTime*/,
                                         RtAudioStreamStatus status, void *userData)
{
    // TODO: may not need error handling
    if (status == RTAUDIO_OUTPUT_UNDERFLOW)
    {
        std::cerr << "Error: Output buffer underflow, too slow to process data" << std::endl;
        return 1;
    }
    auto context = static_cast<PlaybackContext *>(userData);
    float32_t *out = static_cast<float32_t *>(outputBuffer);
    
    // TODO: support multiple channels later
    const uint32_t NumChannels = 2u;

    if (context->source)
    {
        context->source->render(out, bufferFrames);
    }
    else
    {
        std::fill(out, out + (bufferFrames * NumChannels), 0.0f);
        return 1;
    }
    return 0;
}
