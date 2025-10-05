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

#include "syncedQueue.h"
#include "commands.h"
#include "errorHandler.h"
#include "utils.h"
#include <QObject>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QFileInfo>
#include <QThread>

class AudioEngine : public QObject
{
    Q_OBJECT

    public:
        // Constructor and destructer
        explicit AudioEngine(SyncedQueue<AudioCommand::PacketPtr> *requestBuffer, SyncedQueue<QAudioBuffer> *inBuffer, SyncedQueue<QAudioBuffer> *outBuffer, QObject *parent = nullptr);
        ~AudioEngine();

    signals:
        void initFinished();
        void requestFinished(const AudioCommand::PacketPtr Response);
        void finished();

    public slots:
        void init();
        void bootEngine();
        
    private slots:

    private:
        QAudioDecoder *decoder;
        QAudioFormat *format;
        SyncedQueue<AudioCommand::PacketPtr> *requestBuffer;
        SyncedQueue<QAudioBuffer> *audioInBuffer;
        SyncedQueue<QAudioBuffer> *audioOutBuffer;

        // Main private functions
        std::optional<QVariant> processRequest(const AudioCommand::PacketPtr Request);
        void shutdownEngine();

        // Process command functions
        std::optional<AudioData::MetaDataMap_T> getAudioMetaData(const QString &FileName);

        // Helpers
        // QVariant unpackOptional();
        bool insertTagData(const AudioData::Keys Key, const TagLib::Tag *Tag, AudioData::MetaDataMap_T &destMap);
        bool insertPropertyData(const AudioData::Keys Key, const TagLib::AudioProperties *Properties, AudioData::MetaDataMap_T &destMap);

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
