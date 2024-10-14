////////////////////////////////////////////////////////////////////////////////
// File:        CommonLocator.h
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "DebugStackTrace.h"
#include "Logger.h"
#include <map>
#include <typeindex>

class Dependency
{
  private:
    static std::map<std::type_index, void *> references;

  public:
    template <typename TObject> static void Register(TObject *reference)
    {
        std::type_index typeIndex(typeid(TObject));

        if (references.find(typeIndex) != references.end())
        {

            Logger::Error("Locator already contains type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return;
        }

        references[typeIndex] = static_cast<void *>(reference);
    }

    template <typename TObject> static void Unregister()
    {
        std::type_index typeIndex(typeid(TObject));

        if (references.find(typeIndex) == references.end())
        {
            Logger::Error("Locator does not contain type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return;
        }

        references.erase(typeIndex);
    }

    template <typename TObject> static TObject *Get()
    {
        std::type_index typeIndex(typeid(TObject));

        auto it = references.find(typeIndex);
        if (it == references.end())
        {
            Logger::Error("Locator does not contain type {}", typeIndex.name());
            Backtrace::PrintBacktrace(2);
            return nullptr;
        }

        return static_cast<TObject *>(it->second);
    }
};

inline std::map<std::type_index, void *> Dependency::references;
