/**********************************************************
 * Description: Implementation file for the audio engine
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioEngine.h"

// Constructor
AudioEngine::AudioEngine(SyncedAudioQueue *inBuffer, SyncedAudioQueue *outBuffer, QObject *parent) :
    QObject(parent),
    decoder(nullptr),
    format(nullptr),
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

// Directs request to the desired function
void AudioEngine::processRequest(AudioCommand::PacketPtr request)
{
    using namespace AudioCommand;

    const Command_T Command = request->commandType;
    const QVariant RequestData = request->data;
    QVariant responseData;

    switch (Command)
    {
        case GetMetaData:
        {
            responseData = QVariant::fromValue(getAudioMetaData(RequestData.toString()));
            break;
        }
        default:
        {
            // Wrap response QVariant to since Qt will read as uint32_t if not
            responseData = QVariant::fromValue(Error::UnknownRequest);
            break;
        }
    }
    if (responseData.isValid())
    {
        qDebug() << responseData;
        sendResponse(request, responseData);
    }
}

// Stops processing audio data
void AudioEngine::shutdown()
{
    if (decoder->isDecoding())
    {
        decoder->stop();
    }
}

// Modifies the payload in the packet and sends signal indicating that processing is done
inline void AudioEngine::sendResponse(AudioCommand::PacketPtr &packet, const QVariant &Payload)
{
    packet->data = Payload;
    emit requestFinished(packet);
}

// Gets the audio meta data
AudioData::MetaDataMap_T AudioEngine::getAudioMetaData(const QString &FileName)
{
    AudioData::MetaDataMap_T metaData;

    // Lamda to convert TagLib string to QString
    const auto ToQString = ([]()
    {

    });
    const char *FileName_cstr = FileName.toStdString().c_str();
    TagLib::FileRef ref;
    TagLib::Tag *tag;



    return metaData;
}
