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
    struct Packet
    {
        uint32_t id;
        Command_T commandType;
        QVariant data;
    };
    using PacketPtr = QSharedPointer<Packet>;
}

Q_DECLARE_METATYPE(AudioCommand::Command_T)
Q_DECLARE_METATYPE(AudioCommand::PacketPtr)
