/**********************************************************
 * Description: Implementation file for the audio data widget
 * 
 * Date: 2025-09-28
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioDataWidget.h"
#include "ui_audioDataWidget.h"

// Constructor
AudioDataWidget::AudioDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioDataWidget),
    audioPlayer(nullptr)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

AudioDataWidget::~AudioDataWidget()
{
    delete ui;
}

void AudioDataWidget::init(QMediaPlayer *player)
{
    if (!player)
    {   
        // TODO: add error handling
        return;
    }
    audioPlayer = player;
}

// Updates the audio data widget with the current media when it is ready
void AudioDataWidget::onUpdateAudioData()
{
    AudioDataMap_T audioData;
    QList<QString> audioDataList;

    ui->currentAudioView->clear();
    audioData = getAudioMetaData();
    audioDataList = audioDataToList(&audioData);

    ui->currentAudioView->addItems(audioDataList);
}

// Retrieves the audio data from the QMediaPlayer
// Assumes that player has valid media to pull meta data from
AudioDataMap_T AudioDataWidget::getAudioMetaData()
{
    AudioDataMap_T data;
    QString stringBuffer;
    QVariant variantBuffer;
    QMediaMetaData metaData = audioPlayer->metaData();

    for (const auto Key : AudioDataKeys)
    {
        stringBuffer = metaData.stringValue(Key);
        
        if (!stringBuffer.isEmpty())
        {
            data.insert(Key, stringBuffer);
        }
    }
    variantBuffer = metaData.value(QMediaMetaData::ContributingArtist);

    if (variantBuffer.isValid())
    {
        data.insert(QMediaMetaData::ContributingArtist, variantBuffer.toStringList().join(", "));
    }
    return data;
}

QList<QString> AudioDataWidget::audioDataToList(AudioDataMap_T *data)
{
    QList<QString> dataList;
    QString buffer;
    const QString FilePath = audioPlayer->source().toString();
    const QFileInfo FileInfo = QFileInfo(FilePath);

    dataList << ("CURRENT AUDIO FILE:")
             << (FileInfo.fileName())
             << ("\nTITLE:")
             << (data->value(QMediaMetaData::Title))
             << ("\nARTIST(S):")
             << (data->value(QMediaMetaData::ContributingArtist))
             << ("\nALBUM TITLE:")
             << (data->value(QMediaMetaData::AlbumTitle))
             << ("\nAUDIO CODEC:")
             << (data->value(QMediaMetaData::AudioCodec))
             << ("\nBIT RATE:")
             << (QString(data->value(QMediaMetaData::AudioBitRate) + " bits/sec"));

    return dataList;
}
