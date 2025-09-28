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

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QIcon>
#include <QFileDialog>
#include "utils.h"

namespace Ui
{
    class AudioController;
}

class AudioController : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and Destructor
        explicit AudioController(QWidget *parent = nullptr);
        ~AudioController();

        // Public APIs
        void init(QMediaPlayer *audioPlayer, QAudioOutput *audioOutput);

    signals:
        void newAudioFileSelected(const QString &FileName);

    public slots:
        void updateUi(const QString &FileName, const bool Enable);

    private slots:
        void onPlayPauseClicked();
        void onLoadNewAudioFileClicked();

    private:
        // Member variables
        Ui::AudioController *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;
};
