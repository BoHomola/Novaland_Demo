////////////////////////////////////////////////////////////////////////////////
// File:        OverwriteBuffer.h
// Author:      Bohumil Homola
// Date:        09/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "SpscQueue.h"
#include <NovalandCommon.h>

namespace Novaland
{

template <typename T> class OverwriteBuffer
{
  public:
    OverwriteBuffer(size_t size) : m_queue(size)
    {
    }

    ~OverwriteBuffer()
    {
    }

    void Push(T &item)
    {
        while (!m_queue.try_push(item))
        {
            m_queue.pop();
        }
    }

    T &Front()
    {
        return *m_queue.front();
    }

    T Pop()
    {
        T item = *m_queue.front();
        m_queue.pop();
        return item;
    }

    bool Empty() const
    {
        return m_queue.empty();
    }

  private:
    SPSCQueue<T> m_queue;
};

} // namespace Novaland
