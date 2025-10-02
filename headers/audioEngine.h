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
        enum EngineStatus_T
        {
            ErrorDecoding = 0,
            StartedDecoding,
            DecodingFinished,
            DecodingStopped,
            InvalidAudioFormat
        };
        // Constructor and destructer
        explicit AudioEngine(SyncedAudioQueue *buffer, QObject *parent = nullptr);
        ~AudioEngine();

    signals:
        void decoderStatus(const EngineStatus_T Status);

    public slots:
        void init();
        void startDecoding(const QString &FilePath);
        void stopDecoding();
        void onDecodingFinished();
        void onErrorDecoding(const QAudioDecoder::Error Error);
        
    private slots:    
        void addAudioChunkToBuffer();

    private:
        static const uint32_t MaxQueueSize = 20;

        QAudioDecoder *decoder;
        QAudioFormat *format;
        SyncedAudioQueue *audioBuffer;

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
