////////////////////////////////////////////////////////////////////////////////
// File:        Container.h
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "DependencyInjector.h"
#include "Dictionary.h"
#include "NovalandCommon.h"
#include "ObjectWithId.h"
#include <vector>

namespace Novaland
{
template <typename T> class Container
{
  public:
    Container()
    {
        static_assert(std::is_base_of<ObjectWithId, T>::value, "T must be derived from ObjectWithId");
        Dependency::Register<Container<T>>(this);
    }

    virtual ~Container()
    {
        RemoveAll();
    }

    void Add(T *item)
    {
        container[item->id] = item;
        vector_container.push_back(item);
    }

    void Remove(u32 id)
    {
        vector_container.erase(
            std::remove_if(vector_container.begin(), vector_container.end(), [id](T *item) { return item->id == id; }),
            vector_container.end());
        container.erase(id);
    }

    void RemoveAll()
    {
        container.clear();
        vector_container.clear();
    }

    T *Get(u32 id)
    {
        auto it = container.find(id);
        if (it == container.end())
        {
            return nullptr;
        }
        return it->second;
    }

    const std::vector<T *> &GetAll()
    {
        return vector_container;
    }

  private:
    robin_hood::unordered_map<u32, T *> container;
    std::vector<T *> vector_container;
};

} // namespace Novaland
