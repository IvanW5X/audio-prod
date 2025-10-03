/**********************************************************
 * Description: Header file for the audio engine. Main 
 * class responsible for handling the audio processing 
 * functionality and providing low and high level 
 * interfaces for other components.
 * 
 * This class will be placed into another thread to prevent
 * freezing the GUI thread.
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "syncedAudioQueue.h"
#include "commands.h"
#include <QObject>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QFileInfo>
#include <QMutex>
#include <QQueue>
#include <QUrl>
#include <QTimer>

class AudioEngine : public QObject
{
    Q_OBJECT

    public:
        // Constructor and destructer
        explicit AudioEngine(SyncedAudioQueue *inBuffer, SyncedAudioQueue *outBuffer, QObject *parent = nullptr);
        ~AudioEngine();

    signals:
        void requestFinished(AudioCommand::Response Response);

    public slots:
        void init();
        void processRequest(const AudioCommand::RequestPtr Request);
        
    private slots:
        void shutdown();

    private:
        static const uint32_t MaxQueueSize = 20;

        QAudioDecoder *decoder;
        QAudioFormat *format;
        SyncedAudioQueue *audioInBuffer;
        SyncedAudioQueue *audioOutBuffer;

        // Helper functions
        void getAudioMetaData(const uint64_t RequestId, const QString &FileName);

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
