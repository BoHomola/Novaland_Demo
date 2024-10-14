////////////////////////////////////////////////////////////////////////////////
// File:        ComponentDependencyBuilder.h
// Author:      Bohumil Homola
// Date:        12/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "DebugStackTrace.h"
#include "Logger.h"
#include <map>
#include <typeindex>

namespace Novaland
{
class ComponentDependencyBuilder
{
  private:
    std::map<std::type_index, void *> references;

  public:
    template <typename TObject> void Register(TObject *reference)
    {
        std::type_index typeIndex(typeid(TObject));

        if (references.find(typeIndex) != references.end())
        {

            Logger::Error("ComponentDependencyBuilder already contains type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return;
        }

        references[typeIndex] = static_cast<void *>(reference);
    }

    template <typename TObject> void Unregister()
    {
        std::type_index typeIndex(typeid(TObject));

        if (references.find(typeIndex) == references.end())
        {
            Logger::Error("ComponentDependencyBuilder does not contain type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return;
        }

        references.erase(typeIndex);
    }

    template <typename TObject> TObject *Get() const
    {
        std::type_index typeIndex(typeid(TObject));

        auto it = references.find(typeIndex);
        if (it == references.end())
        {
            Logger::Error("ComponentDependencyBuilder does not contain type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return nullptr;
        }

        return static_cast<TObject *>(it->second);
    }
};
} // namespace Novaland
