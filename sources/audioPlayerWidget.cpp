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
    ui->audioControllerWidget->init(audioPlayer, audioOutput);
    ui->waveFormWidget->init();

    (void) connect(ui->audioControllerWidget, &AudioControllerWidget::newAudioFileSelected, this, &AudioPlayerWidget::onUpdateAudioPlayer);
    (void) connect(this, &AudioPlayerWidget::updateAudioController, ui->audioControllerWidget, &AudioControllerWidget::onUpdateAudioController);
    (void) connect(this, &AudioPlayerWidget::updateWaveForm, ui->waveFormWidget, &WaveFormWidget::onUpdateWaveForm);

    // Set default state for audio settings
    audioPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(DefaultVolume);
}

// Updates the audio player and emits signals to wave form and controller
// to update UI
// Assumes that the audio file is valid
void AudioPlayerWidget::onUpdateAudioPlayer(const QString &FileName)
{
    const bool EnableUI = true;

    audioPlayer->setSource(QUrl::fromLocalFile(FileName));

    // emit update wave form and update audio controller
    emit updateAudioController(FileName);
    emit updateWaveForm(FileName);
}
