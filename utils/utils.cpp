/**********************************************************
 * Description: Implementation file for utilities
 * 
 * Date: 2025-09-26
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "utils.h"

// Returns a bool if the selected file can be loaded without any issues
bool Utils::isValidAudioFile(const QString &FileName)
{
    QMediaPlayer tempPlayer;
    QVariant variantData;
    QEventLoop loop;

    tempPlayer.setSource(QUrl::fromLocalFile(FileName));

    // Wait until the media has been loaded
    (void) QObject::connect(&tempPlayer, &QMediaPlayer::mediaStatusChanged, [&loop](QMediaPlayer::MediaStatus status)
    {
        const bool CanExit = (status == QMediaPlayer::LoadedMedia) ||
                             (status == QMediaPlayer::InvalidMedia) ||
                             (status == QMediaPlayer::NoMedia);
        if (CanExit)
        {
            loop.quit();
        }
    });
    loop.exec();

    tempPlayer.disconnect();
    variantData = tempPlayer.metaData()[QMediaMetaData::AudioCodec];

    const bool HasLoadedProperly = tempPlayer.error() == QMediaPlayer::NoError;
    const bool HasAudioCodec = variantData.isValid();

    return (HasLoadedProperly && HasAudioCodec);
}
