/**********************************************************
 * Description: Implementation file for the audio controller.
 * singleton class
 * 
 * Date: 2025-09-30
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioController.h"

// Constructor
AudioController::AudioController(QObject *parent) :
    QObject(parent),
    audioEngine(nullptr),
    engineThread(nullptr),
    audioSink(nullptr),
    audioInBuffer(nullptr),
    audioOutBuffer(nullptr),
    requestId(0u)
{

}

// Free memory and exit thread
AudioController::~AudioController()
{
    engineThread->quit();

    if (!engineThread->wait(MaxThreadTimeout_ms))
    {
        engineThread->terminate();
    }
    delete requestBuffer;
    delete audioInBuffer;
    delete audioOutBuffer;
    delete audioSink;
}

// Creates the worker thread and connects signals
void AudioController::init()
{
    audioSink = new QAudioSink(QAudioFormat(), this);
    requestBuffer = new SyncedQueue<AudioCommand::PacketPtr>();
    audioInBuffer = new SyncedQueue<QAudioBuffer>();
    audioOutBuffer = new SyncedQueue<QAudioBuffer>();

    // Pass in shared thread safe buffers for the engine
    audioEngine = new AudioEngine(requestBuffer, audioInBuffer, audioOutBuffer);
    engineThread = new QThread(this);
    
    // Thread management
    audioEngine->moveToThread(engineThread);
    (void) connect(engineThread, &QThread::started, audioEngine, &AudioEngine::init);
    (void) connect(QApplication::instance(), &QApplication::aboutToQuit, this, &AudioController::shutdownController);
    (void) connect(audioEngine, &AudioEngine::finished, audioEngine, &QObject::deleteLater);
    (void) connect(engineThread, &QThread::finished, engineThread, &QObject::deleteLater);

    // Engine processing connections
    (void) connect(this, &AudioController::startEngine, audioEngine, &AudioEngine::bootEngine);
    (void) connect(audioEngine, &AudioEngine::requestFinished, this, &AudioController::responseReceived);

    engineThread->start(QThread::HighestPriority);

    emit startEngine();
}

// Sends request to engine for the AudioMetaData
// Assumes the file is a valid audio file
void AudioController::requestAudioMetaData(const QString &FileName)
{
    AudioCommand::PacketPtr request = createPacket(AudioCommand::GetMetaData, FileName);
    requestBuffer->enqueue(request);
}

// Directs the response from the engine to the ready signal
void AudioController::responseReceived(AudioCommand::PacketPtr response)
{
    using namespace AudioCommand;

    const Command_T Command = response->commandType;
    const QVariant ResponseData = response->data;
    
    switch (Command)
    {
        case GetMetaData:
            emit audioMetaDataReady(ResponseData.value<AudioData::MetaDataMap_T>());
            break;
        default:
            break;
    }
}

// Sends request to exit engine loop
void AudioController::shutdownController()
{
    AudioCommand::PacketPtr shutdownRequest = createPacket(AudioCommand::RequestShutdown);
    requestBuffer->enqueue(shutdownRequest);
}

// Updates the request Id
inline void AudioController::incrementId()
{
    requestId = (requestId == UINT32_MAX) ? 0 : requestId++;
}

// Creates a shared pointer request with the command, payload, and request Id
AudioCommand::PacketPtr AudioController::createPacket(const AudioCommand::Command_T Command, const QVariant &Payload)
{
    AudioCommand::PacketPtr newRequest = AudioCommand::PacketPtr::create();

    newRequest->commandType = Command;
    newRequest->data = Payload;
    newRequest->id = requestId;
    incrementId();

    return newRequest;
}
