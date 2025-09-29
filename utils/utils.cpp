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
        const bool IsDoneLoading = (status == QMediaPlayer::LoadedMedia) ||
                                   (status == QMediaPlayer::InvalidMedia) ||
                                   (status == QMediaPlayer::NoMedia);
        if (IsDoneLoading)
        {
            loop.quit();
        }
    });
    loop.exec();

    tempPlayer.disconnect();
    variantData = tempPlayer.metaData()[QMediaMetaData::AudioCodec];

    const bool HasAudioCodec = variantData.isValid();
    const bool HasLoadedProperly = tempPlayer.error() == QMediaPlayer::NoError;

    return (HasLoadedProperly && HasAudioCodec);
}
