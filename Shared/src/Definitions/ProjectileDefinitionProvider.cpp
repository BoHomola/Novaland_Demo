////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDefinitionProvider.cpp
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileDefinitionProvider.h"
#include "DependencyInjector.h"

namespace Novaland::Definitions
{

    ProjectileDefinitionProvider::ProjectileDefinitionProvider()
    {
        Dependency::Register<ProjectileDefinitionProvider>(this);
    }

    ProjectileDefinitionProvider::~ProjectileDefinitionProvider()
    {
        Dependency::Unregister<ProjectileDefinitionProvider>();
        for (auto it = m_projectile_definitions.begin(); it != m_projectile_definitions.end(); it++)
        {
            delete it->second;
        }
    }

    void ProjectileDefinitionProvider::Initialize(std::vector<ProjectileDefinition> &projectile_definitions)
    {
        for (auto &projectile_definition : projectile_definitions)
        {
            auto *definition = new ProjectileDefinition(projectile_definition);
            m_projectile_definitions[definition->definition_id] = definition;
        }
    }

    ProjectileDefinition *ProjectileDefinitionProvider::GetProjectileDefinition(u32 id)
    {
        auto it = m_projectile_definitions.find(id);
        if (it != m_projectile_definitions.end())
        {
            return it->second;
        }
        return nullptr;
    }

} // namespace Novaland::Definitions
