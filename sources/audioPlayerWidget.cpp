/**********************************************************
 * Description: Implementation file for the audio player widget
 * 
 * Date: 2025-09-23
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioPlayerWidget.h"
#include "ui_audioPlayerWidget.h"

// Constructor, initializes UI
AudioPlayerWidget::AudioPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPlayerWidget),
    audioPlayer(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor, frees memory
AudioPlayerWidget::~AudioPlayerWidget()
{
    delete ui;
}

// Initializes the audio player
void AudioPlayerWidget::init()
{
    ui->audioDataWidget->init(audioPlayer);
    ui->audioControllerWidget->init(audioPlayer, audioOutput);
    ui->waveFormWidget->init(audioPlayer);

    (void) connect(ui->audioControllerWidget, &AudioControllerWidget::newAudioFileSelected, this, &AudioPlayerWidget::onUpdateAudioPlayer);
    (void) connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, ui->audioDataWidget, &AudioDataWidget::onUpdateAudioData);
    (void) connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, ui->audioControllerWidget, &AudioControllerWidget::onUpdateAudioController);
    (void) connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, ui->waveFormWidget, &WaveFormWidget::onUpdateWaveForm);

    // Set default state for audio settings
    audioPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(DefaultVolume);
}

// Sets the audio source and setup for new audio file
// Assumes that the audio file is valid
void AudioPlayerWidget::onUpdateAudioPlayer(const QString &FileName)
{
    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
}
