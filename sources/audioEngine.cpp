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

    (void) connect(decoder, &QAudioDecoder::finished, this, &AudioEngine::onDecodingFinished);
    (void) connect(decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error), this, &AudioEngine::onErrorDecoding);
    (void) connect(decoder, &QAudioDecoder::bufferReady, this, &AudioEngine::addAudioChunkToBuffer);
}

// If the decoder is done, assume the audio file was successfully read so emits
// a success signal
void AudioEngine::onDecodingFinished()
{
    emit decoderStatus(EngineStatus_T::DecodingFinished);
}

// Sends a signal when the decoder comes across an error while decoding
void AudioEngine::onErrorDecoding(const QAudioDecoder::Error Error)
{
    emit decoderStatus(EngineStatus_T::ErrorDecoding);
}

// Loads file into the path and starts decoding the audio file
void AudioEngine::startDecoding(const QString &FilePath)
{    
    if (!decoder)
    {
        return;
    }
    decoder->setSource(QUrl::fromLocalFile(FilePath));
    decoder->start();

    emit decoderStatus(EngineStatus_T::StartedDecoding);
}

void AudioEngine::stopDecoding()
{
    if (!decoder->isDecoding())
    {
        return;
    }
    decoder->stop();
    emit decoderStatus(EngineStatus_T::DecodingStopped);
}

// Adds raw PCM chunk to the thread safe queue/buffer
void AudioEngine::addAudioChunkToBuffer()
{
    const QAudioBuffer DecodedChunk = decoder->read();

    if (DecodedChunk.isValid())
    {
        audioBuffer->enqueue(DecodedChunk);
    }
}
