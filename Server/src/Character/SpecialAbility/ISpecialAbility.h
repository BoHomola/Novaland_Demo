////////////////////////////////////////////////////////////////////////////////
// File:        ISpecialAbility.h
// Author:      Bohumil Homola
// Date:        12/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
namespace Novaland::Character
{

class ISpecialAbility : IComponent
{
  public:
    virtual void Proceed() = 0;
    void RegisterDependencies(const ComponentDependencyBuilder &builder) override = 0;
};
} // namespace Novaland::Character
