////////////////////////////////////////////////////////////////////////////////
// File:        ObjectPool.hpp
// Author:      Bohumil Homola
// Date:        07/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include "SpscQueue.h"
#include <iostream>
#include <mutex>
#include <queue>
#include <stack>

template <typename T> class ObjectPool
{
  public:
    ObjectPool(size_t size) : size(size), queue(size)
    {
        objects.reserve(size + size / 2);
        for (size_t i = 0; i < size; i++)
        {
            T *obj = new T();
            queue.push(obj);
            objects.push_back(obj);
        }
        current_size = size;
    }

    ~ObjectPool()
    {
        for (T *obj : objects)
        {
            delete obj;
        }
    }

    T *Get()
    {
        if (queue.empty())
        {
            current_size++;
            Logger::Info("ObjectPool: No free objects, creating new one");
            T *obj = new T();
            objects.push_back(obj);
            return obj;
        }

        T *obj = *queue.front();
        queue.pop();
        return obj;
    }

    void Release(T *obj)
    {
        if (!queue.try_push(obj))
        {
            Logger::Error("ObjectPool: No free space in queue");
            delete obj;
        }
    }

    u32 GetSize() const
    {
        return queue.size();
    }

  private:
    u16 current_size;
    size_t size;
    SPSCQueue<T *> queue;
    std::vector<T *> objects;
};
