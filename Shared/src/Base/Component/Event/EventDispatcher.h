////////////////////////////////////////////////////////////////////////////////
// File:        EventDispatcher.h
// Author:      Bohumil Homola
// Date:        10/22/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Event/Event.h"
#include "Base/Component/IComponent.h"
#include "DependencyInjector.h"
#include "Tick/TickManger.h"
#include <queue>

namespace Novaland::Event
{
class EventDispatcher : IComponent
{
  public:
    EventDispatcher()
    {
        tick_manager = Dependency::Get<TickManager>();
    };

    ~EventDispatcher() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override{};

    void QueueEvent(u32 delay, std::function<void()> callback)
    {
        Event event;
        event.fire_tick = tick_manager->GetCurrentTick() + delay;
        event.callback = callback;
        events.push(event);
    }

    void FireEvents()
    {
        while (!events.empty() && events.top().fire_tick <= tick_manager->GetCurrentTick())
        {
            auto event = events.top();
            event.callback();
            events.pop();
        }
    }

  private:
    std::priority_queue<Event> events;
    TickManager *tick_manager;
};
} // namespace Novaland::Event
