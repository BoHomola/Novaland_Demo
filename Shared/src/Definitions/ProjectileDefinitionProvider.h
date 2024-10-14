////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDefinitionProvider.h
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include "ProjectileDefinition.h"
#include <unordered_map>

namespace Novaland::Definitions
{

class ProjectileDefinitionProvider
{
  public:
    ProjectileDefinitionProvider();
    ~ProjectileDefinitionProvider();

    void Initialize(std::vector<ProjectileDefinition> &projectile_definitions);
    ProjectileDefinition *GetProjectileDefinition(u32 id);

  private:
    std::unordered_map<u32, ProjectileDefinition *> m_projectile_definitions;
};

} // namespace Novaland::Definitions
