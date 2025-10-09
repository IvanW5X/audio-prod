/************************************************************
 * File: commands.h
 * 
 * Description: 
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include <variant>

namespace AudioCmd
{
    enum Command_T
    {
        GetMetaData = 0,
        StartDecoding,
        PlayAudioFile,
        RequestShutdown
    };
    template<typename T> struct Task_T
    {
        Command_T command;
        std::variant<T> data
    };
}
