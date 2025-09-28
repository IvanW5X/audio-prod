/**********************************************************
 * Description: Header file for the audio player widget. Serves
 *              as the audio player page containing the supporting
 *              subwidgets and handling high level audio data
 * 
 * Date: 2025-09-23
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "audioControllerWidget.h"
#include "audioDataWidget.h"
#include "waveFormWidget.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

namespace Ui
{
    class AudioPlayerWidget;
}

// typedef struct
// {
//     QString title;
//     QString artist;
//     QString album;
//     QString Genre;
// } AudioData_T;

class AudioPlayerWidget : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and destructor
        explicit AudioPlayerWidget(QWidget *parent = nullptr);
        ~AudioPlayerWidget();

        // Public APIs
        void init();

    signals:
        void updateWaveForm(const QString &FileName);
        void updateAudioController(const QString &FileName);

    public slots:
        void onUpdateAudioPlayer(const QString &FileName);

    private slots:

    private:
        // Static const(expr) values
        static constexpr float_t DefaultVolume = 100.0;

        // Member variables
        Ui::AudioPlayerWidget *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;

        // Helper functions

        // Disable copy constructor and assignment operator overload
        AudioPlayerWidget(const AudioPlayerWidget &) = delete;
        AudioPlayerWidget &operator=(const AudioPlayerWidget &) = delete;
};
