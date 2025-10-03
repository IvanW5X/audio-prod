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
AudioEngine::AudioEngine(SyncedAudioQueue *inBuffer, SyncedAudioQueue *outBuffer, QObject *parent) :
    QObject(parent),
    decoder(nullptr),
    format(nullptr),
    audioInBuffer(inBuffer),
    audioOutBuffer(outBuffer)
{
    
}

// Destructer
AudioEngine::~AudioEngine()
{
    delete decoder;
    delete format;
}

// Initialize engine
void AudioEngine::init()
{
    decoder = new QAudioDecoder(this);
    format = new QAudioFormat();
}

// Directs request to the desired function
void AudioEngine::processRequest(const AudioCommand::RequestPtr Request)
{
    using namespace AudioCommand;

    const Command_T Command = Request->commandType;
    const QVariant Data = Request->data;
    const uint64_t RequestId = Request->requestId;

    switch (Command)
    {
        case (GetMetaData):
        {
            getAudioMetaData(RequestId, Data.toString());
            break;
        }
        
        default:
        {
            ResponsePtr Unknown = ResponsePtr::create();

            Unknown->responseId = RequestId;
            // Unknown->data = QVariant::fromValue();
        }
    }
}

// Stops processing audio data
void AudioEngine::shutdown()
{
    if (decoder->isDecoding())
    {
        decoder->stop();
    }
}

void AudioEngine::getAudioMetaData(const uint64_t RequestId, const QString &FileName)
{
    
}