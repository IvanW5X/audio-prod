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
    audioOutput(new QAudioOutput(this)),
    currentFile(QString())
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
    // ui->audioDataWidget->init(audioPlayer);
    // ui->audioControllerWidget->init(audioPlayer, audioOutput);
    // ui->waveFormWidget->init(audioPlayer);

    // (void) connect(ui->audioControllerWidget, &AudioControllerWidget::newAudioFileSelected, this, &AudioPlayerWidget::onUpdateAudioPlayer);
    // (void) connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayerWidget::onAudioFileLoaded);
    // (void) connect(this, &AudioPlayerWidget::updateAudioData, ui->audioDataWidget, &AudioDataWidget::onUpdateAudioData);
    // (void) connect(this, &AudioPlayerWidget::updateAudioController, ui->audioControllerWidget, &AudioControllerWidget::onUpdateAudioController);
    // (void) connect(this, &AudioPlayerWidget::updateWaveForm, ui->waveFormWidget, &WaveFormWidget::onUpdateWaveForm);

    audioPlayer->setAudioOutput(audioOutput);
}

// Sets the audio source and setup for new audio file
// Assumes that the audio file is valid
void AudioPlayerWidget::onUpdateAudioPlayer(const QString &FileName)
{
    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
}

// Emits signals to child components when the media is loaded with a new file
void AudioPlayerWidget::onAudioFileLoaded(const QMediaPlayer::MediaStatus Status)
{
    const bool IsSameFile = currentFile == audioPlayer->source().toString();
    const bool IsLoaded = Status == QMediaPlayer::LoadedMedia;

    if (!IsLoaded || IsSameFile) return;

    currentFile = audioPlayer->source().toString();

    emit updateAudioData();
    emit updateAudioController();
    emit updateWaveForm();
}