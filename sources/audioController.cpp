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
    requestId(0)
{

}

AudioController::~AudioController()
{
    delete audioEngine;
    delete audioInBuffer;
    delete audioOutBuffer;
}

// Creates the worker thread and connects signals
void AudioController::init()
{
    // Pass in shared thread safe buffer for the engine
    audioInBuffer = new SyncedAudioQueue();
    audioOutBuffer = new SyncedAudioQueue();

    audioEngine = new AudioEngine(audioInBuffer, audioOutBuffer);
    engineThread = new QThread(this);

    audioEngine->moveToThread(engineThread);

    (void) connect(QApplication::instance(), &QApplication::aboutToQuit, this, &AudioController::shutdown);
    (void) connect(engineThread, &QThread::started, audioEngine, &AudioEngine::init);
    (void) connect(this, &AudioController::sendRequest, audioEngine, &AudioEngine::processRequest);

    engineThread->start(QThread::HighestPriority);
}

// Sends request to engine for the AudioMetaData
// Assumes the file is a valid audio file
void AudioController::requestAudioMetaData(const QString &FileName)
{
    AudioCommand::RequestPtr request = createRequest(AudioCommand::GetMetaData, FileName);
    emit sendRequest(request);
}

// Directs the response from the engine to the ready signal
void AudioController::responseReceived(AudioCommand::ResponsePtr package)
{

}

// Shut down thread and processing in this class
void AudioController::shutdown()
{
    if (engineThread->isRunning())
    {
        QMetaObject::invokeMethod(audioEngine, "shutdown", Qt::BlockingQueuedConnection);
        engineThread->quit();
        engineThread->wait();
    }
    if (audioSink->state() == QAudio::ActiveState)
    {
        audioSink->stop();
    }
}

// Updates the request Id
inline void AudioController::incrementId()
{
    requestId =  (requestId == UINT64_MAX) ? 0 : requestId++;
}

// Creates a shared pointer request with the command, payload, and request Id
AudioCommand::RequestPtr AudioController::createRequest(const AudioCommand::Command_T Command, const QVariant &Payload)
{
    AudioCommand::RequestPtr newRequest = AudioCommand::RequestPtr::create();

    newRequest->commandType = Command;
    newRequest->data = Payload;
    newRequest->requestId = requestId;
    incrementId();

    return newRequest;
}