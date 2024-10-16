////////////////////////////////////////////////////////////////////////////////
// File:        IComponent.h
// Author:      Bohumil Homola
// Date:        12/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/ComponentDependencyBuilder.h"

namespace Novaland
{
class IComponent
{
  public:
    virtual ~IComponent() = default;
    virtual void RegisterDependencies(const ComponentDependencyBuilder &builder) = 0;
};
} // namespace Novaland
