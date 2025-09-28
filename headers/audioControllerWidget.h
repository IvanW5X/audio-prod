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
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QIcon>
#include <QFileDialog>

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
        void onUpdateAudioController(const QString &FileName);

    private slots:
        void onPlayPauseClicked();
        void onLoadNewAudioFileClicked();

    private:
        // Member variables
        Ui::AudioControllerWidget *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;
};
