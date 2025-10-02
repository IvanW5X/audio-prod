/**********************************************************
 * Description: Implementation file for the SyncedAudioQueue
 * class
 * 
 * Date: 2025-10-01
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "syncedAudioQueue.h"

// Adds audio buffer to queue using a mutex
void SyncedAudioQueue::enqueue(const QAudioBuffer &Buffer)
{
    QMutexLocker lock(&mutex);
    audioBuffer.enqueue(Buffer);
}

// Returns the audio buffer first in queue
// Assumes the queue is non emoty
QAudioBuffer SyncedAudioQueue::dequeue()
{
    QMutexLocker lock(&mutex);
    return audioBuffer.dequeue();
}

// Clears the audio buffer with a mutex
void SyncedAudioQueue::clear()
{
    QMutexLocker lock(&mutex);
    audioBuffer.clear();
}

// Returns a bool indicating if the bool is empty
bool SyncedAudioQueue::isEmpty()
{
    QMutexLocker lock(&mutex);
    return (audioBuffer.isEmpty());
}
