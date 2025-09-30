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
    audioOutput(nullptr),
    updateTimer(new QTimer(this))
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
    (void) connect(updateTimer, &QTimer::timeout, this, &AudioControllerWidget::onUpdatePlayingAudio);
    (void) connect(ui->durationSlider, &QSlider::sliderReleased, this, &AudioControllerWidget::onDurationSliderReleased);
    (void) connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, this, &AudioControllerWidget::onEndOfAudio);
    (void) connect(ui->volumeSlider, &QSlider::sliderReleased, this, &AudioControllerWidget::onVolumeSliderReleased);
    (void) connect(ui->muteButton, &QPushButton::clicked, this, &AudioControllerWidget::onMuteClicked);

    const float_t SliderToVolumeFactor = 100.0;
    updateTimer->setInterval(MillisecPerSec);
    ui->volumeSlider->setRange(0, MaxVolume);
    audioOutput->setVolume(static_cast<float_t>(MaxVolume) / SliderToVolumeFactor);
    
    ui->volumeSlider->setValue(MaxVolume);
    ui->playPauseButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
}

// Updates the audio controller widget with the new audio file
// Assumes that the audio player has a valid audio file loaded
void AudioControllerWidget::onUpdateAudioController()
{
    const int64_t Duration_ms = audioPlayer->duration();
    const QString StartTime = "00:00:00";
    const QString EndTime = " | " + getTimeFormat(Duration_ms);
    
    ui->durationSlider->setRange(0, Duration_ms);
    ui->durationSlider->setValue(0);
    
    ui->currentTimeLabel->setText(StartTime);
    ui->endTimeLabel->setText(EndTime);
    ui->playPauseButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
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
        updateTimer->stop();
    }
    else
    {
        updatedIcon = QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause);
        audioPlayer->play();
        updateTimer->start();
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
    if (Utils::isValidAudioFile(FileName))
    {
        emit newAudioFileSelected(FileName);
    }
    else
    {
        // TODO: error handle
    }
}

// Update the current time label and slider when the audio is playing
void AudioControllerWidget::onUpdatePlayingAudio()
{
    const bool CanUpdate = (audioPlayer->isPlaying()) && (!ui->durationSlider->isSliderDown());
    
    if (!CanUpdate) return;

    const int64_t CurrentPosition_ms = audioPlayer->position();
    const QString CurrentTimeFormat = getTimeFormat(CurrentPosition_ms);

    ui->durationSlider->setValue(CurrentPosition_ms);
    ui->currentTimeLabel->setText(CurrentTimeFormat);
}

// Update the audio player and current time when the slider moves
void AudioControllerWidget::onDurationSliderReleased()
{
    updateTimer->stop();

    const int64_t NewPosition = static_cast<int64_t>(ui->durationSlider->value());
    const QString CurrentTimeFormat = getTimeFormat(NewPosition);

    audioPlayer->setPosition(NewPosition);
    ui->currentTimeLabel->setText(CurrentTimeFormat);

    updateTimer->start();
}

// Resets the current time, icon, and slider when audio is done playing
void AudioControllerWidget::onEndOfAudio(const QMediaPlayer::MediaStatus Status)
{
    const bool HasEnded = (Status == QMediaPlayer::EndOfMedia);
    
    if (!HasEnded) return;

    const QString StartTime = "00:00:00";

    ui->currentTimeLabel->setText(StartTime);
    ui->durationSlider->setValue(0);
    ui->playPauseButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
}

// Adjusts the volume components using the volume slider
void AudioControllerWidget::onVolumeSliderReleased()
{
    const float_t SliderToVolumeFactor = 100.0;
    const int32_t NewVolume = ui->volumeSlider->value();
    const bool IsMuted = audioOutput->isMuted();
    const QIcon UpdatedIcon = ((NewVolume > 0) && !IsMuted) ? QIcon::fromTheme(QIcon::ThemeIcon::AudioVolumeMedium) : QIcon::fromTheme(QIcon::ThemeIcon::AudioVolumeMuted);

    audioOutput->setVolume(static_cast<float_t>(NewVolume) / SliderToVolumeFactor);
    ui->volume->setText(QString::number(NewVolume));
    ui->muteButton->setIcon(UpdatedIcon);
}

// Handles the volume components when the mute button is clicked
void AudioControllerWidget::onMuteClicked()
{
    const bool IsMuted = audioOutput->isMuted();
    const QIcon UpdatedIcon = (IsMuted) ? QIcon::fromTheme(QIcon::ThemeIcon::AudioVolumeMedium) : QIcon::fromTheme(QIcon::ThemeIcon::AudioVolumeMuted);

    ui->muteButton->setIcon(UpdatedIcon);
    audioOutput->setMuted(!IsMuted);
}

// Converts the passed in milliseconds to a formatted string
QString AudioControllerWidget::getTimeFormat(const int64_t Milliseconds) const
{
    const int32_t TotalSeconds = static_cast<int32_t>(std::ceil(Milliseconds / MillisecPerSec));

    const int32_t Hours = TotalSeconds / SecPerHour;
    const int32_t Minutes = (TotalSeconds % SecPerHour) / SecPerMin;
    const int32_t Seconds = TotalSeconds % SecPerMin;

    const int32_t Width = 2;
    const int32_t Base = 10;
    const QString TimeFormat = QString("%1:%2:%3")
                               .arg(Hours, Width, Base, QChar('0'))
                               .arg(Minutes, Width, Base, QChar('0'))
                               .arg(Seconds, Width, Base, QChar('0'));

    return TimeFormat;
}