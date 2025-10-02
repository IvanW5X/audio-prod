/**********************************************************
 * Description: Header file for a thread safe audio queue.
 * Used to store decoded audio data and is shared between
 * the audio engine and controller
 * 
 * Date: 2025-10-01
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QAudioBuffer>

class SyncedAudioQueue
{
    public:
        // Use default constructor and destructor
        SyncedAudioQueue() = default;
        ~SyncedAudioQueue() = default;

        // Buffer APIs
        void enqueue(const QAudioBuffer &Buffer);
        QAudioBuffer dequeue();
        bool isEmpty();
        void clear();

    private:
        QMutex mutex;
        QQueue<QAudioBuffer> audioBuffer;
};
