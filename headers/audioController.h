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
#include <QObject>
#include <QThread>
#include <QAudioSink>
#include <QApplication>

class AudioController : public QObject
{
    Q_OBJECT

    public:
        // Thread safe as of C++11
        static AudioController &Instance()
        {
            static AudioController instance;
            return instance;
        }
    
        void init();

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
        SyncedAudioQueue audioBuffer;

        // Disable copy constructor and assignment operator overload
        AudioController(const AudioController &) = delete;
        AudioController &operator=(const AudioController &) = delete;
};
