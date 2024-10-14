////////////////////////////////////////////////////////////////////////////////
// File:        TSQueue.hpp
// Author:      Bohumil Homola
// Date:        07/05/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <queue>
namespace Novaland
{

template <typename T> class ThreadSafeQueue
{
  public:
    ThreadSafeQueue()
    {
    }
    ~ThreadSafeQueue()
    {
    }

    void Push(T *data)
    {
        std::scoped_lock<std::mutex> lock(mutex);
        queue.push(data);
    }

    T *Pop()
    {
        std::scoped_lock<std::mutex> lock(mutex);
        if (queue.empty())
        {
            return nullptr;
        }

        T *data = queue.front();
        queue.pop();
        return data;
    }
    bool Empty()
    {
        std::scoped_lock<std::mutex> lock(mutex);
        return queue.empty();
    }

    std::queue<T *> queue;
    std::mutex mutex;
};
} // namespace Novaland
