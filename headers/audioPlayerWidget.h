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

    public slots:

    private slots:

    private:
        // Member variables
        Ui::AudioPlayerWidget *ui;
        QString currentFile;

        // Disable copy constructor and assignment operator overload
        AudioPlayerWidget(const AudioPlayerWidget &) = delete;
        AudioPlayerWidget &operator=(const AudioPlayerWidget &) = delete;
};
