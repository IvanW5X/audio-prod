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
}

// Initializes the audio player
void AudioPlayer::init()
{
    ui->audioController->init(audioPlayer, audioOutput);
    ui->waveForm->init();

    (void) connect(ui->audioController, &AudioController::newAudioFileSelected, this, &AudioPlayer::updateAudioPlayer);
    (void) connect(this, &AudioPlayer::updateWaveFormUi, ui->waveForm, &WaveForm::updateUi);
    (void) connect(this, &AudioPlayer::updateAudioControllerUi, ui->audioController, &AudioController::updateUi);

    // Set default state for audio settings
    audioPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(DefaultVolume);
}

// Updates the audio player and emits signals to wave form and controller
// to update UI
// Assumes that the audio file is valid
void AudioPlayer::updateAudioPlayer(const QString &FileName)
{
    const bool EnableUI = true;
    AudioData_T audioData;

    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
    audioData = getAudioData(audioPlayer);

    emit updateWaveFormUi(FileName, EnableUI);
    emit updateAudioControllerUi(FileName, EnableUI);
}

// Gets the meta data from the audio file
AudioData_T AudioPlayer::getAudioData(QMediaPlayer *player)
{
    const QMediaPlayer::MediaStatus CurrentStatus = player->mediaStatus();
    const bool IsValidMedia = (CurrentStatus == QMediaPlayer::LoadedMedia);
    
    // if (!IsValidMedia) return;

    QMediaMetaData metaData = player->metaData();
    return AudioData_T();
}
