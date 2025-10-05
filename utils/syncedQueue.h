/**********************************************************
 * Description: Header file for a thread safe queue.
 * Used to create a thread safe pipeline between threads
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
#include <QWaitCondition> 

template<typename T> class SyncedQueue
{
    public:
        // Use default constructor and destructor
        SyncedQueue() = default;
        ~SyncedQueue() = default;

        // Buffer APIs
        void enqueue(const T &data)
        {
            QMutexLocker lock(&mutex);
            queue.enqueue(std::move(data));
            condition.wakeOne();
        }
        // Blocking call for popping data from queue
        T waitAndTake()
        {
            QMutexLocker lock(&mutex);
            
            while (queue.isEmpty())
            {
                condition.wait(&mutex);
            }
            return queue.dequeue();
        }
        // Non blocking call for popping data from queue
        std::optional<T> tryTake()
        {
            QMutexLocker lock(&mutex);
            auto data = (queue.isEmpty()) ? std::nullopt : queue.dequeue();
            return data;
        }

        void clear()
        {
            QMutexLocker lock(&mutex);
            queue.clear();
        }

    private:
        QMutex mutex;
        QWaitCondition condition;
        QQueue<T> queue;
};
