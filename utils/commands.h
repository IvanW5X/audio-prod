/**********************************************************
 * Description: Command structure and IDs for for Audio 
 * processing interface
 * 
 * Date: 2025-10-02
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QVariant>
#include <QMetaType>
#include <QSharedPointer>

namespace AudioCommand
{
    enum Command_T
    {
        GetMetaData = 0,
        StartDecoding,
        StopDecoding,
        PlayAudioFile,
        SeekFilePosition,
        PauseAudioFile,
    };

    struct Request
    {
        uint64_t requestId;
        Command_T commandType;
        QVariant data;
    };

    struct Response
    {
        uint64_t responseId;
        QVariant data;
    };

    using RequestPtr = QSharedPointer<Request>;
    using ResponsePtr = QSharedPointer<Response>;
}

Q_DECLARE_METATYPE(AudioCommand::Command_T)
Q_DECLARE_METATYPE(AudioCommand::RequestPtr)
Q_DECLARE_METATYPE(AudioCommand::ResponsePtr)
