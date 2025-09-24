/**********************************************************
 * Description: Header file for the audio player widget
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
    class AudioPlayer;
}

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

    public slots:
        void updateUiWithAudioFile(const QString &FileName);

    private slots:

    private:
        // Member variables
        Ui::AudioPlayer *ui;
        QMediaPlayer *audioPlayer;
        QAudioOutput *audioOutput;

        // Disable copy constructor and assignment operator overload
        AudioPlayer(const AudioPlayer &) = delete;
        AudioPlayer &operator=(const AudioPlayer &) = delete;
};
