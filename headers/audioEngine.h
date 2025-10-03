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
        bool insertPropertyData(const AudioData::Keys Key, const TagLib::AudioProperties *Tag, AudioData::MetaDataMap_T &destMap);


        // Disable copy constructor and assignment operator overload
        AudioEngine(const AudioEngine &) = delete;
        AudioEngine &operator=(const AudioEngine &) = delete;

        // Template functions
        // Adds the data tag associated with the key to the map, inserts NA if no tag is found
        template<typename T>
        bool insertTagData(const AudioData::Keys Key, const TagLib::Tag *Tag, AudioData::MetaDataMap_T &destMap, const T &Converter)
        {
            bool success = true;

            if (!tag)
            {
                ErrorHandle::instance().handleError
                (
                    Error::ReadingFileFailed,
                    QString("Failed to get tag data.")
                );
                return !success;
            }
            TagLib::String buffer;
            QVariant data;

            switch (Key)
            {
                case AudioData::Title:
                {
                    buffer = tag->title(); 
                    break;
                }
                case AudioData::Album:{
                    buffer = tag->album();
                    break;
                }
                case AudioData::Artist:
                { 
                    buffer = tag->artist();
                    break;
                }
                case AudioData::Genre:
                {
                    buffer = tag->genre();
                    break;
                }
                default:
                {
                    Error::instance().handleError
                    (
                        Error::ReadingFileFailed,
                        QString("File has no audio tage for %1.").arg(Key)
                    );
                    return !success;
                }
            }
            if (buffer.isEmpty())
            {
                data = QVariant::fromValue(QString("NA"));
                sucess = false;
            }
            else
            {
                data = QVariant::fromValue(QString::fromStdWString(buffer.toCWString()));
            }
            destMap.insert(Key, data);

            return success;
        }
};
