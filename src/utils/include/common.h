/************************************************************
 * File: common.h
 * 
 * Description: 
 * 
 * Date: 2025-10-08
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#pragma once

#include <vector>
#include <stdint.h>

#define TaskQueueCapacity 64u

// TODO: might change later
struct AudioFileData_T
{
    std::vector<float_t> samples;
    int32_t sampleRate_hz;
    uint32_t channels;
    size_t readIndex;
};
