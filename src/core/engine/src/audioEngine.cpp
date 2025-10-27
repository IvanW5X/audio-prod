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
bool AudioEngine::loadAudioFile(const std::string &FilePath, AudioFileData_T &outAudioData)
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
    outAudioData.readIndex = 0;
    outAudioData.samples.resize(numFrames * sfInfo.channels);
    sf_count_t framesRead = sf_read_float(inFile, outAudioData.samples.data(), numFrames);

    // TODO: handle error better later
    if (framesRead != numFrames)
    {
        sf_close(inFile);

        std::cerr << "Error: could not read all frames from audio file: "
                  << FilePath << "\n"
                  << "Frames read: " << framesRead << "\nExpected frames: " << numFrames << std::endl;

        return false;
    }
    sf_close(inFile);

    // TODO: remove later
    std::cout << "Loaded audio file: " << FilePath << "\n"
              << "Sample rate: " << sfInfo.samplerate << "\n"
              << "Channels: " << sfInfo.channels << "\n"
              << "Total frames: " << sfInfo.frames << std::endl;

    return true;
}

// Plays audio given a valid AudioFileData_T
void AudioEngine::playAudioData(const AudioFileData_T &AudioData)
{
    // TODO: Move to different function later
    RtAudio dac;
    
    // TODO: error handle better
    if (dac.getDeviceCount() < 1)
    {
        std::cerr << "Error: No output device found" << std::endl;
        return;
    }
    RtAudio::StreamParameters outputParams;
    outputParams.deviceId = dac.getDefaultOutputDevice();
    outputParams.nChannels = AudioData.channels;
    outputParams.firstChannel = 0u;

    uint32_t numBufferFrames = 512u;
    const bool IsErrorOccurred = RTAUDIO_SYSTEM_ERROR == dac.openStream(&outputParams, nullptr /* inputParams */,
                                                                RTAUDIO_FLOAT32, AudioData.sampleRate_hz, &numBufferFrames, // Audio settings
                                                                &AudioEngine::audioCallback, (void *)&AudioData); // Function and user data
    
    if (IsErrorOccurred || !dac.isStreamOpen())
    {
        std::cerr << "Error: could not open audio stream" << std::endl;
        return;
    }
    dac.startStream();

    char input;
    std::cout << "Playing, press enter to stop" << std::endl;
    std::cin.get(input);

    dac.stopStream();
}

// RtAudio callback function
int32_t AudioEngine::audioCallback(void *outputBuffer, void * /*inputBuffer*/,
                      uint32_t bufferFrames, double /*streamTime*/,
                      RtAudioStreamStatus status, void *userData)
{
    // TODO: may not need error handling
    if (status == RTAUDIO_OUTPUT_UNDERFLOW)
    {
        std::cerr << "Error: Output buffer underflow, too slow to process data" << std::endl;
        return 1;
    }
    AudioFileData_T *audioData = static_cast<AudioFileData_T *>(userData);
    float_t *out = static_cast<float_t *>(outputBuffer);
    const std::vector<float_t> *Samples = &audioData->samples;
    const int32_t NumChannels = audioData->channels;
    
    // TODO: assume 2 channels for now, change later when refactoring to support multiple channels
    size_t totalFrames = Samples->size() / NumChannels;

    // Fill the interleaved output buffer from the sample buffer, advancing readIndex.
    size_t sampleIndex = static_cast<size_t>(audioData->readIndex);
    const size_t totalSamples = Samples->size();
    const int32_t channels = NumChannels;

    for (uint32_t frame = 0; frame < bufferFrames; frame++)
    {
        for (int32_t ch = 0; ch < channels; ch++)
        {
            size_t outIndex = static_cast<size_t>(frame) * channels + static_cast<size_t>(ch);
            if (sampleIndex < totalSamples)
            {
                out[outIndex] = (*Samples)[sampleIndex++];
            }
            else
            {
                // Silence
                out[outIndex] = 0.0f;
                std::cerr << "Warning: Run out of samples" << std::endl;
            }
        }
    }
    audioData->readIndex = static_cast<int64_t>(sampleIndex);

    return 0;
}
