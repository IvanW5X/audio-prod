/**********************************************************
 * Description: Implementation file for the audio player controller.
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioControllerWidget.h"
#include "ui_audioControllerWidget.h"

// Constructor
AudioControllerWidget::AudioControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioControllerWidget),
    audioPlayer(nullptr),
    audioOutput(nullptr)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor
AudioControllerWidget::~AudioControllerWidget()
{
    delete ui;
}

// Initializes the audio controller
void AudioControllerWidget::init(QMediaPlayer *audioPlayer, QAudioOutput *audioOutput)
{
    if (!audioPlayer || !audioOutput)
    {
        // TODO: error handle instead
        return;
    }
    this->audioPlayer = audioPlayer;
    this->audioOutput = audioOutput;

    (void) connect(ui->playPauseButton, &QPushButton::clicked, this, &AudioControllerWidget::onPlayPauseClicked);
    (void) connect(ui->loadNewAudioFileButton, &QPushButton::clicked, this, &AudioControllerWidget::onLoadNewAudioFileClicked);

    // TODO: Set default state for UI
    
}

// Updates the audio controller widget with the new audio file
// Assumes that the audio player has a valid audio file loaded
void AudioControllerWidget::onUpdateAudioController(QMediaPlayer::MediaStatus status)
{
    // get the duration and 
    // update the duration slider and label
}

// Changes the icon and plays/pauses the audio
void AudioControllerWidget::onPlayPauseClicked()
{
    const bool HasNoMedia = (audioPlayer->mediaStatus() == QMediaPlayer::NoMedia);
    QIcon updatedIcon;

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
void AudioControllerWidget::onLoadNewAudioFileClicked()
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