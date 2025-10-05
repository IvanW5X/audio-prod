/**********************************************************
 * Description: Implementation file for the audio engine
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioEngine.h"

namespace Internal
{
    
}

// Constructor
AudioEngine::AudioEngine(SyncedQueue<AudioCommand::PacketPtr> *requestBuffer, SyncedQueue<QAudioBuffer> *inBuffer, SyncedQueue<QAudioBuffer> *outBuffer, QObject *parent) :
    QObject(parent),
    decoder(nullptr),
    format(nullptr),
    requestBuffer(requestBuffer),
    audioInBuffer(inBuffer),
    audioOutBuffer(outBuffer)
{
    
}

// Destructer
AudioEngine::~AudioEngine()
{
    delete decoder;
    delete format;
}

// Initialize engine
void AudioEngine::init()
{
    decoder = new QAudioDecoder(this);
    format = new QAudioFormat();
}

// Start the processing loop
void AudioEngine::bootEngine()
{
    while (true)
    {
        auto request = requestBuffer->waitAndTake();

        if (request->commandType == AudioCommand::RequestShutdown)
        {
            break;
        }
        auto response = std::move(processRequest(request));

        if (response.has_value())
        {
            request->data = std::move(response.value());
            emit requestFinished(request);
        }
    }
    shutdownEngine();
    emit finished();
}

// Directs request to the desired function
std::optional<QVariant> AudioEngine::processRequest(AudioCommand::PacketPtr request)
{
    using namespace AudioCommand;

    const Command_T Command = request->commandType;
    const QVariant RequestData = request->data;

    switch (Command)
    {
        case GetMetaData:
        {
            auto metaData_opt = getAudioMetaData(RequestData.value<QString>());

            if (metaData_opt.has_value())
            {
                return QVariant::fromValue(metaData_opt.value());
            }
            break;
        }
        case RequestShutdown:
            return QVariant();
        default:
            // Wrap response QVariant to since Qt will read as uint32_t if we don't
            return QVariant::fromValue(Error::UnknownRequest);
    }
    return std::nullopt;
}

// Stops processing audio data
void AudioEngine::shutdownEngine()
{
    if (decoder->isDecoding())
    {
        decoder->stop();
    }
}

// Gets the audio meta data
std::optional<AudioData::MetaDataMap_T> AudioEngine::getAudioMetaData(const QString &FileName)
{
    const bool ReadAudio = true;
    const TagLib::AudioProperties::ReadStyle Style = TagLib::AudioProperties::Accurate;
    const char *FileName_cstr = FileName.toLocal8Bit().constData();

    AudioData::MetaDataMap_T metaData;
    TagLib::FileRef ref = TagLib::FileRef(FileName_cstr);
    const TagLib::Tag *Tag = ref.tag();

    if (ref.isNull() || !Tag)
    {
        ErrorHandler::instance().handleError
        (
            Error::ReadingFileFailed,
            QString("Failed to get meta data from file at path: %1").arg(FileName)
        );
        return std::nullopt;
    }
    const QFileInfo Info = QFileInfo(FileName);
    const TagLib::AudioProperties *Properties = ref.audioProperties();
    QList<AudioData::Keys> dataNotFound;

    metaData.insert(AudioData::FileName, QVariant::fromValue(Info.fileName()));
    qDebug() << metaData[AudioData::FileName].toString();

    // Add one to index since we already added the file name. View utils.h for enum order
    for (int i = AudioData::STRING_VALUE_BEGIN + 1; i < AudioData::STRING_VALUE_END; i++)
    {
        const AudioData::Keys CurrentKey = static_cast<AudioData::Keys>(i);

        qDebug() << CurrentKey;

        if (!insertTagData(CurrentKey, Tag, metaData))
        {
            dataNotFound.append(CurrentKey);
        }
    }
    for (int i = AudioData::INT_VALUE_BEGIN; i < AudioData::INT_VALUE_END; i++)
    {
        const AudioData::Keys CurrentKey = static_cast<AudioData::Keys>(i);

        qDebug() << CurrentKey;

        if (!insertPropertyData(CurrentKey, Properties, metaData))
        {
            dataNotFound.append(CurrentKey);
        }
    }
    return metaData;
}

// Adds the data tag associated with the key to the map, inserts NA if no tag is found
bool AudioEngine::insertTagData(const AudioData::Keys Key, const TagLib::Tag *Tag, AudioData::MetaDataMap_T &destMap)
{
    bool success = true;

    if (!Tag)
    {
        return !success;
    }
    TagLib::String buffer;
    QVariant data;

    switch (Key)
    {
        case AudioData::ReleaseYear:
            data = static_cast<int32_t>(Tag->year());
            break;
        case AudioData::TrackNumber:
            data = static_cast<int32_t>(Tag->track());
            break;
        case AudioData::Title:
            buffer = Tag->title(); 
            break;
        case AudioData::Album:
            buffer = Tag->album();
            break;
        case AudioData::Artist:
            buffer = Tag->artist();
            break;
        case AudioData::Genre:
            buffer = Tag->genre();
            break;
        default:
            break;
    }
    // Meta data using strings
    if (data.isNull())
    {
        if (buffer.isEmpty())
        {
            data = QVariant::fromValue(QString("NA"));
            success = false;
        }
        else
        {
            data = QVariant::fromValue(QString::fromStdWString(buffer.toCWString()));
        }
    }
    else
    {
        // When no tags found for int types, TagLib returns 0 
        success = (QVariant::fromValue(data).toInt() != 0);
    }
    destMap.insert(Key, data);

    return success;
}

// Adds the audio property associated with the key to the map, errors if the property is missing
bool AudioEngine::insertPropertyData(const AudioData::Keys Key, const TagLib::AudioProperties *Properties, AudioData::MetaDataMap_T &destMap)
{
    // Use this to denote an error
    const int32_t PropertyDataError = -1;
    bool success = true;

    if (!Properties)
    {
        return !success;
    }
    QVariant data;

    switch (Key)
    {
        case AudioData::Duration_ms:
            data = Properties->lengthInMilliseconds();
            break;
        case AudioData::BitRate_kbs:
            data = Properties->bitrate();
            break;
        case AudioData::SampleRate_hz:
            data = Properties->sampleRate();
            break;
        case AudioData::NumChannels:
            data = Properties->channels();
            break;
        default:
            data = PropertyDataError;
            break;
    }
    if (data == PropertyDataError)
    {
        success = false;
    }
    destMap.insert(Key, data);

    return success;
}
