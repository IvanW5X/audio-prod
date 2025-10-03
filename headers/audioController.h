/**********************************************************
 * Description: Header file for the audio controller.
 * This class is the high level interface for the AudioEngine
 * class and follows the singleton design pattern.
 * 
 * Date: 2025-09-30
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "audioEngine.h"
#include "syncedAudioQueue.h"
#include "commands.h"
#include <QObject>
#include <QThread>
#include <QAudioSink>
#include <QApplication>
#include <QMediaDevices>

class AudioController : public QObject
{
    Q_OBJECT

    public:
        // Thread safe as of C++11
        static AudioController &instance()
        {
            static AudioController instance;
            return instance;
        }
        void init();

    signals:
        // Main signal
        void sendRequest(AudioCommand::RequestPtr payload);

    private slots:
        void responseReceived(AudioCommand::ResponsePtr package);
        // on response received, use the commandId to switch to emit ready signals
            // connect these ready signals to the UI components to update them

        void cleanupThread();

    private:
        // Prevent direct instantiation
        explicit AudioController(QObject *parent = nullptr);
        ~AudioController();

        // Member variables
        AudioEngine *audioEngine;
        QThread *engineThread;
        QAudioSink *audioSink;
        SyncedAudioQueue *audioBuffer;

        // Disable copy constructor and assignment operator overload
        AudioController(const AudioController &) = delete;
        AudioController &operator=(const AudioController &) = delete;
};
