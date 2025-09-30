/**********************************************************
 * Description: Header file for the audio data. Displays the
 * audio player meta data in a human readable form 
 * 
 * Date: 2025-09-28
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVariant>
#include <QMap>
#include <QFileInfo>

namespace Ui
{
    class AudioDataWidget;
}

using AudioDataMap_T = QMap<QMediaMetaData::Key, QString>;

class AudioDataWidget : public QWidget
{
    Q_OBJECT
    
    public:
        // Constructor and destructer
        explicit AudioDataWidget(QWidget *parent = nullptr);
        ~AudioDataWidget();

        // Public APIs
        void init(QMediaPlayer *player);

    signals:

    public slots:
        void onUpdateAudioData();

    private slots:

    private:
        // Static const variables
        const QList<QMediaMetaData::Key> AudioDataKeys =
        {
            QMediaMetaData::Key::Title,
            QMediaMetaData::Key::AlbumTitle,
            QMediaMetaData::Key::AudioCodec,
            QMediaMetaData::Key::AudioBitRate
            // NOTE: ContributingArtist is returned as a QStringLists, so we handle this case separately
        };

        // Member variables
        Ui::AudioDataWidget *ui;
        QMediaPlayer *audioPlayer;

        // Helper functions
        AudioDataMap_T getAudioMetaData();
        QList<QString> audioDataToList(AudioDataMap_T *data);
};
