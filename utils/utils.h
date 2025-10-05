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
#include <QVariant>
#include <taglib/fileref.h>

namespace Utils
{
    void setupApp();
    bool isValidAudioFile(const QString &FileName);

    // Returns QEnum name for registered Qt enums
    template<typename QEnum> QString qEnumToString(const QEnum Value)
    {
        return QVariant::fromValue(Value).toString();
    }
}

namespace AudioData
{
    Q_NAMESPACE
    enum Keys
    {
        STRING_VALUE_BEGIN = 0,
        FileName = STRING_VALUE_BEGIN,
        Title,
        Album,
        Artist,
        Genre,
        STRING_VALUE_END,

        INT_VALUE_BEGIN = STRING_VALUE_END,
        ReleaseYear = INT_VALUE_BEGIN,
        TrackNumber,
        Duration_ms,
        BitRate_kbs,
        SampleRate_hz,
        NumChannels,
        INT_VALUE_END,

        NumKeys = INT_VALUE_END
    };
    Q_ENUM_NS(Keys)

    using MetaDataMap_T = QMap<Keys, QVariant>;
}

Q_DECLARE_METATYPE(AudioData::Keys)
Q_DECLARE_METATYPE(AudioData::MetaDataMap_T)
