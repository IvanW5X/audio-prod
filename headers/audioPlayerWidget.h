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

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui
{
    class AudioPlayerWidget;
}

class AudioPlayerWidget : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and destructer
        explicit AudioPlayerWidget(QWidget *parent = nullptr);
        ~AudioPlayerWidget();

        // Public APIs
        void init();

    signals:
        void updateAudioData();
        void updateAudioController();
        void updateWaveForm();

    public slots:
        void onUpdateAudioPlayer(const QString &FileName);

    private slots:
        void onAudioFileLoaded(const QMediaPlayer::MediaStatus Status);

    private:
        // Member variables
        Ui::AudioPlayerWidget *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;
        QString currentFile;

        // Helper functions

        // Disable copy constructor and assignment operator overload
        AudioPlayerWidget(const AudioPlayerWidget &) = delete;
        AudioPlayerWidget &operator=(const AudioPlayerWidget &) = delete;
};
