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
    audioBuffer(nullptr)
{

}

AudioController::~AudioController()
{
    delete audioEngine;
}

// Creates the worker thread and connects signals
void AudioController::init()
{
    // Pass in shared thread safe buffer for the engine
    audioBuffer = new SyncedAudioQueue();
    audioEngine = new AudioEngine(audioBuffer);
    engineThread = new QThread(this);

    audioEngine->moveToThread(engineThread);

    const QAudioDevice Device = QMediaDevices::defaultAudioOutput();

    if (Device.isNull())
    {
        // audioSink = new QAudioSink(QAudioFormat(), this);
        // TODO: setup an output device or indicate to the user somehow that no output device found
    }
    else
    {
        // audioSink = new QAudioSink(Device, Device.preferredFormat(), this);
    }
    (void) connect(QApplication::instance(), &QApplication::aboutToQuit, this, &AudioController::cleanupThread);
    (void) connect(engineThread, &QThread::started, audioEngine, &AudioEngine::init);
    (void) connect(this, &AudioController::startDecoding, audioEngine, &AudioEngine::startDecoding);

    engineThread->start(QThread::HighestPriority);
    const QString audioFile = "C:/Users/ivanw/OneDrive/Documents/Music/Billie Jean 4.mp3";

    decodeFile(audioFile);
}

// Sends signal to the engine to start decoding the file
bool AudioController::decodeFile(const QString &FilePath)
{
    const QFileInfo FileInfo = QFileInfo(FilePath);
    const bool IsFileExists = (!FilePath.isEmpty()) && (FileInfo.exists());
    bool success = true;

    if (!IsFileExists)
    {
        success = false;
    }
    else
    {
        emit startDecoding(FilePath);
    }
    return success;
}

// Clean up thread usage
void AudioController::cleanupThread()
{
    engineThread->quit();
    engineThread->wait();
}

void AudioController::playAudio()
{

}