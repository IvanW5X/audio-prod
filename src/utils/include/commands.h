/************************************************************
 * FILE: commands.h
 * 
 * DESCRIPTION: Defines the audio commands and task struct
 *  used for communication between audio controller and engine  
 * 
 * DATE: 2025-10-08
 * 
 * AUTHOR: Ivan Wong
 * 
 ************************************************************/

#pragma once

namespace AudioCmd
{
    enum Command_T
    {
        GetMetaData = 0,
        StartDecoding,
        PlayAudioFile,
        RequestShutdown
    };
    
    template<typename T> 
    struct Task_T
    {
        Command_T command;
        T data;
    };
}
