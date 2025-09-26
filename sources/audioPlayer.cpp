/**********************************************************
 * Description: Implementation file for the audio player widget
 * 
 * Date: 2025-09-23
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioPlayer.h"
#include "ui_audioPlayer.h"

// Constructor, initializes UI
AudioPlayer::AudioPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPlayer),
    audioPlayer(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor, frees memory
AudioPlayer::~AudioPlayer()
{
    delete ui;
    delete audioPlayer;
    delete audioOutput;
}

// Initializes the audio player
void AudioPlayer::init()
{
    // TODO: intialize audio player, default UI, and connect signals
    ui->audioController->init(audioPlayer, audioOutput);
    ui->waveForm->init();
    return;
}

// Returns a bool if the file can be loaded without any issues
bool AudioPlayer::isValidAudioFile(const QString &FileName)
{
    // Use temporary media player incase user uploads an incompatible audio file 
    QMediaPlayer tempPlayer;
    QVariant variantData;
    QEventLoop loop;

    tempPlayer.setSource(QUrl::fromLocalFile(FileName));

    // Wait until the media has been loaded
    (void) connect(&tempPlayer, &QMediaPlayer::mediaStatusChanged, [&loop](QMediaPlayer::MediaStatus status)
    {
        const bool CanExit = (status == QMediaPlayer::LoadedMedia) ||
                             (status == QMediaPlayer::InvalidMedia) ||
                             (status == QMediaPlayer::NoMedia);
        if (CanExit)
        {
            loop.quit();
        }
    });
    loop.exec();

    tempPlayer.disconnect();
    variantData = tempPlayer.metaData()[QMediaMetaData::AudioCodec];

    const bool HasLoadedProperly = tempPlayer.error() == QMediaPlayer::NoError;
    const bool HasAudioCodec = variantData.isValid();

    return (HasLoadedProperly && HasAudioCodec);
}

// Updates the audio player and UI with the meta data of the audio file
void AudioPlayer::updateAudioPlayer(const QString &FileName)
{
    AudioData_T audioData;

    // Setup audio
    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
    audioPlayer->setAudioOutput(audioOutput);

    // TODO: Get meta data from audio file and emit signals to update 
    // audio controller and wave form
    audioData = getAudioData(audioPlayer);
}

/// Gets the meta data from the audio file
AudioData_T AudioPlayer::getAudioData(QMediaPlayer *player)
{
    return AudioData_T();
}
