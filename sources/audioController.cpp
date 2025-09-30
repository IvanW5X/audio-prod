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
    audioBuffer(SyncedAudioQueue())
{

}

// Creates the worker thread and connects signals
void AudioController::init()
{
    // Pass in shared thread safe buffer for the engine
    audioEngine = new AudioEngine(&audioBuffer, this);
    engineThread = new QThread(this);
    audioSink = new QAudioSink(QAudioFormat(), this);

    audioEngine->moveToThread(engineThread);

    (void) connect(QApplication::instance(), &QApplication::aboutToQuit, this, &AudioController::cleanupThread);
    (void) connect(engineThread, &QThread::started, audioEngine, &AudioEngine::init);

    engineThread->start();
}

AudioController::~AudioController()
{

}

void AudioController::cleanupThread()
{
    engineThread->quit();
    engineThread->wait();
}
