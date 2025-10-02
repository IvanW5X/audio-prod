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
        bool decodeFile(const QString &FilePath);
        void playAudio();
        // bool isBufferEmpty();

    signals:
        void startDecoding(const QString &FilePath);

    private slots:
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
