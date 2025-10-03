/**********************************************************
 * Description: Implementation file for the audio engine
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioEngine.h"

// Constructor
AudioEngine::AudioEngine(SyncedAudioQueue *buffer, QObject *parent) :
    QObject(parent),
    decoder(nullptr),
    format(nullptr),
    audioBuffer(buffer)
{
    
}

// Destructer
AudioEngine::~AudioEngine()
{
    if (decoder->isDecoding())
    {
        decoder->stop();
    }
    delete decoder;
    delete format;
}

// Initialize engine
void AudioEngine::init()
{
    decoder = new QAudioDecoder(this);
    format = new QAudioFormat();

}
