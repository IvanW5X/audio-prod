/**********************************************************
 * Description: Common data and functions for the audio production tool
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "commands.h"
#include "errorHandler.h"
#include <QString>
#include <QFileInfo>
#include <taglib/fileref.h>

namespace Utils
{
    void setupApp();
    bool isValidAudioFile(const QString &FileName);

    // Returns QEnum name for registered Qt enums
    template<typename QEnum> QString qEnumToString(const QEnum Value)
    {
        return QString( QMetaType::fromType<QEnum>(Value).toValueKey(Value) );
    }
}

namespace AudioData
{
    Q_NAMESPACE
    enum Keys
    {
        Title = 0,
        Album,
        Artist,
        Duration,
        Genre,
        ReleaseYear,
        TrackNumber,
        Duration_ms,
        BitRate_kbs,
        SampleRate_hz,
        NumChannels,
        FileName,
        NumKeys
    };
    Q_ENUM_NS(Keys)

    using MetaDataMap_T = QMap<Keys, QVariant>;
}

Q_DECLARE_METATYPE(AudioData::Keys)
Q_DECLARE_METATYPE(AudioData::MetaDataMap_T)
