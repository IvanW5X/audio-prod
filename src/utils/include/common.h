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

typedef float float32_t;
typedef double float64_t;

// TODO: might change later
struct AudioData_T
{
    std::vector<float32_t> samples;
    uint32_t sampleRate_hz;
    uint32_t channels;
};
