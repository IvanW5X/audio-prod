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
#include "errorHandler.h"
#include "utils.h"
#include <QObject>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QFileInfo>

class AudioEngine : public QObject
{
    Q_OBJECT

    public:
        // Constructor and destructer
        explicit AudioEngine(SyncedAudioQueue *inBuffer, SyncedAudioQueue *outBuffer, QObject *parent = nullptr);
        ~AudioEngine();

    signals:
        void requestFinished(const AudioCommand::PacketPtr Response);

    public slots:
        void init();
        void processRequest(const AudioCommand::PacketPtr Request);
        
    private slots:
        void shutdown();

    private:
        QAudioDecoder *decoder;
        QAudioFormat *format;
        SyncedAudioQueue *audioInBuffer;
        SyncedAudioQueue *audioOutBuffer;

        // Helper functions
        inline void sendResponse(AudioCommand::PacketPtr &packet, const QVariant &Payload);
        AudioData::MetaDataMap_T getAudioMetaData(const QString &FileName);
        bool insertTagData(const AudioData::Keys Key, const TagLib::Tag *Tag, AudioData::MetaDataMap_T &destMap);
        bool insertPropertyData(const AudioData::Keys Key, const TagLib::AudioProperties *Tag, AudioData::MetaDataMap_T &destMap);

        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;
};
