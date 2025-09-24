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
    return;
}

//
void AudioPlayer::updateUiWithAudioFile(const QString &FileName)
{
    // TODO: Verify that the file name is a valid audio file
    // verify extension and more?
    
    audioPlayer->setAudioOutput(audioOutput);
    audioPlayer->setSource(QUrl::fromLocalFile(FileName));
    audioOutput->setVolume(50);
    audioPlayer->play();
}