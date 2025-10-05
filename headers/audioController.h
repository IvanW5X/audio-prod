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
#include "syncedQueue.h"
#include "commands.h"
#include "utils.h"
#include <QObject>
#include <QThread>
#include <QAudioSink>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QApplication>

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
        // Public APIs
        void init();

        // Interface functions
        void requestAudioMetaData(const QString &FileName);

    signals:
        void startEngine();
        
        // Ready/done processing signals
        void audioMetaDataReady(const AudioData::MetaDataMap_T &audioMetaData);
        // void decodingDone();

    private slots:
        void responseReceived(AudioCommand::PacketPtr package);
        // on response received, use the commandId to switch to emit ready signals
            // connect these ready signals to the UI components to update them

        void shutdownController();

    private:
        const uint32_t MaxThreadTimeout_ms = 5000u;

        // Prevent direct instantiation
        explicit AudioController(QObject *parent = nullptr);
        ~AudioController();

        // Member variables
        AudioEngine *audioEngine;
        QThread *engineThread;
        SyncedQueue<AudioCommand::PacketPtr> *requestBuffer;

        QAudioSink *audioSink;
        QAudioDevice *audioDevice;
        QAudioOutput *audioOutput;
        SyncedQueue<QAudioBuffer> *audioInBuffer;
        SyncedQueue<QAudioBuffer> *audioOutBuffer;
        uint32_t requestId;

        // Helper functions
        inline void incrementId();
        AudioCommand::PacketPtr createPacket(const AudioCommand::Command_T Command, const QVariant &Payload = QVariant());

        // Disable copy constructor and assignment operator overload
        AudioController(const AudioController &) = delete;
        AudioController &operator=(const AudioController &) = delete;
};
