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

// Verifies the audio file and updates the UI with the meta data of the audio file
void AudioPlayer::updateUiWithAudioFile(const QString &FileName)
{
    // TODO: Verify that the file name is a valid audio file
        // verify extension and more?
    // get meta data from file
    // draw wave form
    // update info in UI with meta data
    audioPlayer->setAudioOutput(audioOutput);
    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
}

/// Gets the meta data from the audio file
AudioData_T AudioPlayer::getAudioData()
{
    return AudioData_T();
}
