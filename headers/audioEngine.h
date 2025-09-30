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

#include <QObject>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QFileInfo>
#include <QMutex>
#include <QQueue>
#include <QUrl>
#include <QTimer>

// Forward declaration for a thread safe queue
class SyncedAudioQueue;

class AudioEngine : public QObject
{
    Q_OBJECT

    public:
        enum EngineStatus_T
        {
            Error = 0,
            Success,
            InvalidFile
        };

        // Constructor and destructer
        explicit AudioEngine(SyncedAudioQueue *buffer, QObject *parent = nullptr);
        ~AudioEngine();

        // DEBUG stuff
        void test();
        const QString testFile = "C:/Users/ivanw/OneDrive/Documents/Music/21 Savage, Offset & Metro Boomin - _Ghostface Killers_ Ft Travis Scott (Official Audio) 0.mp3";
        
    signals:
        void statusChanged(const EngineStatus_T Status);
        void getBuffer();

    public slots:
        void init();
        void startDecoding(const QString &FilePath);
        void onDecodingFinished();
        void onErrorOccurred(const QAudioDecoder::Error Error);
        void onGetBuffer();

    private:
        QAudioDecoder *decoder;
        SyncedAudioQueue *audioBuffer;

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};

// Helper Class for a thread safe audio queue
class SyncedAudioQueue
{
    public:
        // Use default constructor and destructor
        SyncedAudioQueue() = default;
        ~SyncedAudioQueue() = default;

        void enqueue(const QAudioBuffer &Buffer);
        QAudioBuffer dequeue();
        void clear();

    private:
        QMutex mutex;
        QQueue<QAudioBuffer> audioBuffer;
};
