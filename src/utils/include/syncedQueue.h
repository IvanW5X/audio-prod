/************************************************************
 * FILE: syncedQueue.h
 * 
 * DESCRIPTION: The SyncedQueue class provides a thread safe
 *  queue with a fixed size. The use of memory order and
 *  atomics are meant to provide efficiency, but will be
 *  reviewed at a later time
 * 
 * DATE: 2025-10-08
 *
 * AUTHOR: Ivan Wong
 *
 ************************************************************/

#pragma once

#include <array>
#include <atomic>
#include <optional>

template<typename T, size_t Capacity>
class SyncedQueue
{
    public:
        //--------------------------------------------------
        // Constructor
        SyncedQueue() :
            front(0u),
            back(0u)
        {}

        //--------------------------------------------------
        // Destructor
        ~SyncedQueue() = default;

        //--------------------------------------------------
        // Adds an item to the queue, returns false if it is full
        bool enqueue(const T &value)
        {
            const size_t NextFront = (front + 1) % Capacity;

            if (NextFront == back.load(std::memory_order_acquire))
            {
                return false;                
            }
            buffer[NextFront] = std::move(value);
            front.store(NextFront, std::memory_order_release);
            
            return true;
        }

        //--------------------------------------------------
        // Pops and item from the back of the queue, returns null if empty
        std::optional<T>dequeue()
        {
            const size_t CurBack = back.load(std::memory_order_acquire);
            const size_t CurFront = front.load(std::memory_order_acquire);

            if (CurBack == CurFront)
            {
                return std::nullopt;
            }
            const T item = std::move(buffer[front]);
            back.store((back + 1) % Capacity, std::memory_order_release);
            
            return item;
        }

        //--------------------------------------------------
        // Returns true or false if the queue is empty
        bool isEmpty() const
        {
            const size_t CurFront = front.load(std::memory_order_acquire);
            const size_t CurBack = back.load(std::memory_order_acquire);
        
            return (CurFront == CurBack);
        }

    private:
        // Member variables
        std::array<T, Capacity> buffer;
        std::atomic<size_t> front;
        std::atomic<size_t> back;
};
