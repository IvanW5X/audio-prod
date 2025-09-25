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
    this->audioPlayer = audioPlayer;
    this->audioOutput = audioOutput;

    // Connect signals and slots
    (void) connect(ui->playPauseButton, &QPushButton::clicked, this, &AudioController::onPlayPauseClicked);
}

// Changes the icon and plays/pauses the audio
void AudioController::onPlayPauseClicked()
{
    const bool IsAudioPlaying = audioPlayer->isPlaying();
    QIcon updatedIcon = QIcon();

    if (IsAudioPlaying)
    {
        updatedIcon = QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart);
        audioPlayer->pause();
    }
    else
    {
        updatedIcon = QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause);
        audioPlayer->play();
    }
    ui->playPauseButton->setIcon(updatedIcon);
}