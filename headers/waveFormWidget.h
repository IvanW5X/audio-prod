/**********************************************************
 * Description: Header file for the wave form widget.
 * Computes and draws the wave form of an audio file
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "commonDefines.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QUrl>
#include <vector>

namespace Ui
{
    class WaveFormWidget;
}

class WaveFormWidget : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and Destructer
        explicit WaveFormWidget(QWidget *parent = nullptr);
        ~WaveFormWidget();

        // Public APIs
        void init(QMediaPlayer *player);
        
    signals:
        
    public slots:
        void onUpdateWaveForm();
        
    private slots:
        
    private:
        // Member variables
        Ui::WaveFormWidget *ui;
        QMediaPlayer *audioPlayer;
        QAudioDecoder *decoder;
        std::vector<float_t> audioSamples;

        // Helper functions
        void updateAudioSamples();
};
