/**********************************************************
 * Description: Header file for the audio player controller.
 * Manages the audio playback controls using inputs from the user 
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "utils.h"
#include "commonDefines.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QIcon>
#include <QFileDialog>
#include <QTimer>

namespace Ui
{
    class AudioControllerWidget;
}

class AudioControllerWidget : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and Destructor
        explicit AudioControllerWidget(QWidget *parent = nullptr);
        ~AudioControllerWidget();

        // Public APIs
        void init(QMediaPlayer *audioPlayer, QAudioOutput *audioOutput);

    signals:
        void newAudioFileSelected(const QString &FileName);

    public slots:
        void onUpdateAudioController();

    private slots:
        void onPlayPauseClicked();
        void onLoadNewAudioFileClicked();
        void onUpdatePlayingAudio();
        void onDurationSliderReleased();
        void onEndOfAudio(const QMediaPlayer::MediaStatus Status);
        void onVolumeSliderReleased();
        void onMuteClicked();

    private:
        // Static vars
        static const int64_t MillisecPerSec = 1000;
        static const int64_t SecPerMin = 60;
        static const int64_t SecPerHour = 3600;
        static const int32_t MaxVolume = 100;

        // Member variables
        Ui::AudioControllerWidget *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;
        QTimer *updateTimer;

        // Helper functions
        QString getTimeFormat(const int64_t Milliseconds) const;
};
