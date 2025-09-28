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
// NOTE: connected to AudioPlayer by mediaStatusChanged signal
void AudioDataWidget::onUpdateAudioData(QMediaPlayer::MediaStatus status)
{
    const bool IsReady = (status == QMediaPlayer::LoadedMedia);
    
    if (!IsReady)
    {
        return;
    }
    AudioDataMap_T audioData;

    audioData = getAudioMetaData();
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
    // Handle the ContributingArtist case seperately since it can return multipe artists
    variantBuffer = metaData.value(QMediaMetaData::ContributingArtist);

    if (variantBuffer.isValid())
    {
        data.insert(QMediaMetaData::ContributingArtist, variantBuffer.toStringList().join(','));
    }
    return data;
}
