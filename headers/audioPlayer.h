/**********************************************************
 * Description: Header file for the audio player widget. Serves
 *  as the audio player page containing the supporting subwidgets
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
        void updateWaveFormUi(const QString &FileName, const bool Enable);
        void updateAudioControllerUi(const QString &FileName, const bool Enable);

    public slots:
        void updateAudioPlayer(const QString &FileName);

    private slots:

    private:
        // Static const(expr) values
        static constexpr float_t DefaultVolume = 100.0;

        // Member variables
        Ui::AudioPlayer *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;

        // Helper functions
        // void drawWaveForm();
        AudioData_T getAudioData(QMediaPlayer *player);

        // Disable copy constructor and assignment operator overload
        AudioPlayer(const AudioPlayer &) = delete;
        AudioPlayer &operator=(const AudioPlayer &) = delete;
};
