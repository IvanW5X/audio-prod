/**********************************************************
 * Description: Implementation file for the audio engine
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioEngine.h"

/*******************************
 *
 * SyncedAudioQueue definitions
 *
 *******************************/

// Adds audio buffer to queue using a mutex
void SyncedAudioQueue::enqueue(const QAudioBuffer &Buffer)
{
    QMutexLocker lock(&mutex);
    audioBuffer.enqueue(Buffer);

    qDebug() << "Cur Size: " << audioBuffer.size();
}

// Returns the audio buffer and pops it off the queue if non empty using a mutex, 
// returns an empty buffer otherwise
QAudioBuffer SyncedAudioQueue::dequeue()
{
    QMutexLocker lock(&mutex);
    return (audioBuffer.isEmpty()) ? QAudioBuffer() : audioBuffer.dequeue();
}

// Clears the audio buffer with a mutex
void SyncedAudioQueue::clear()
{
    QMutexLocker lock(&mutex);
    audioBuffer.clear();
}

/*******************************
 *
 * AudioEngine definitions
 *
 *******************************/

// Constructor
AudioEngine::AudioEngine(SyncedAudioQueue *buffer, QObject *parent) :
    QObject(parent),
    decoder(nullptr),
    audioBuffer(buffer)
{
    
}

// Destructer
AudioEngine::~AudioEngine()
{

}

// Initialize member variables here for thread setup for AudioController
void AudioEngine::init()
{
    decoder = new QAudioDecoder(this);

    (void) connect(decoder, &QAudioDecoder::finished, this, &AudioEngine::onDecodingFinished);
    (void) connect(decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error), this, &AudioEngine::onErrorOccurred);
    (void) connect(decoder, &QAudioDecoder::bufferReady, this, &AudioEngine::addAudioChunkToBuffer);

}

// If the decoder is done, assume the audio file was successfully read so emits
// a success signal
void AudioEngine::onDecodingFinished()
{
    emit statusChanged(EngineStatus_T::Success);
}

// DEBUG
void AudioEngine::test()
{
    
}

// Sends a signal when the decoder comes across an error while decoding
void AudioEngine::onErrorOccurred(const QAudioDecoder::Error Error)
{
    emit statusChanged(EngineStatus_T::Error);
}

void AudioEngine::startDecoding(const QString &FilePath)
{
    const QFileInfo FileInfo = QFileInfo(FilePath);
    const bool IsFileExists = (!FilePath.isEmpty()) && (FileInfo.exists());
    
    if (!IsFileExists || !decoder)
    {
        emit statusChanged(EngineStatus_T::InvalidFile);
        return;
    }
    decoder->setSource(QUrl::fromLocalFile(FilePath));
    decoder->start();
}

// Adds a decoded chunk into the thread safe queue/buffer
void AudioEngine::addAudioChunkToBuffer()
{
    const QAudioBuffer DecodedChunk = decoder->read();

    if (DecodedChunk.isValid())
    {
        audioBuffer->enqueue(DecodedChunk);
    }
}