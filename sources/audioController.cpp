/**********************************************************
 * Description: Implementation file for the audio player controller.
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioController.h"
#include "ui_audioController.h"

// Constructor
AudioController::AudioController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioController),
    audioPlayer(nullptr),
    audioOutput(nullptr)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor
AudioController::~AudioController()
{
    delete ui;
}

// Initializes the audio controller
void AudioController::init(QMediaPlayer *audioPlayer, QAudioOutput *audioOutput)
{
    if (!audioPlayer || !audioOutput)
    {
        // TODO: error handle instead
        return;
    }
    else
    {
        this->audioPlayer = audioPlayer;
        this->audioOutput = audioOutput;
    }
}
