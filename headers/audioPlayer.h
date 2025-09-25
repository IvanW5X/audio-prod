/**********************************************************
 * Description: Header file for the audio player widget
 * 
 * Date: 2025-09-23
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "audioController.h"
#include "waveForm.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

namespace Ui
{
    class AudioPlayer;
}

typedef struct
{
    QString title;
    QString artist;
    QString album;
    QString Genre;


} AudioData_T;

class AudioPlayer : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and destructor
        explicit AudioPlayer(QWidget *parent = nullptr);
        ~AudioPlayer();

        // Public APIs
        void init();

    signals:
        void playTrack();
        void pauseTrack();
        void adjustVolume(const float NewVolume);

    public slots:
        void updateUiWithAudioFile(const QString &FileName);

    private slots:
        // void onPlayTrack();
        // void onPauseTrack();
        // void onAdjustVolume();

    private:
        // Member variables
        Ui::AudioPlayer *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;

        // Helper functions
        // void drawWaveForm();
        AudioData_T getAudioData();

        // Disable copy constructor and assignment operator overload
        AudioPlayer(const AudioPlayer &) = delete;
        AudioPlayer &operator=(const AudioPlayer &) = delete;
};
