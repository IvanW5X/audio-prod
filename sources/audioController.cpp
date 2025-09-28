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

    (void) connect(ui->playPauseButton, &QPushButton::clicked, this, &AudioController::onPlayPauseClicked);
    (void) connect(ui->loadNewAudioFileButton, &QPushButton::clicked, this, &AudioController::onLoadNewAudioFileClicked);

    // Set default state for UI
    
}

// Update UI
void AudioController::updateUi(const QString &FileName, const bool Enable)
{
    // TODO: finish up
    return;
}

// Changes the icon and plays/pauses the audio
void AudioController::onPlayPauseClicked()
{
    const bool HasNoMedia = (audioPlayer->mediaStatus() == QMediaPlayer::NoMedia);
    QIcon updatedIcon = QIcon();

    if (HasNoMedia) return;

    if (audioPlayer->isPlaying())
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

// Opens a file dialog to select a new audio file
void AudioController::onLoadNewAudioFileClicked()
{
    const QString FileName = QFileDialog::getOpenFileName(this,
                                                          tr("Select Audio File"),
                                                          QDir::homePath(),
                                                          tr("Audio Files (*.mp3 *.wav *.flac);;All Files (*.*)"));
    if (FileName.isEmpty()) return;

    if (Utils::isValidAudioFile(FileName))
    {
        emit newAudioFileSelected(FileName);
    }
    else
    {
        // TODO: error handle
    }
}