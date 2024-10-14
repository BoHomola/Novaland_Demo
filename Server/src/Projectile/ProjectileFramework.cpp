////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileFramework.cpp
// Author:      Bohumil Homola
// Date:        12/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileFramework.h"

namespace Novaland::Projectile
{

void ProjectileFramework::FixedUpdate()
{
    m_projectile_life_component.Tick();
}
} // namespace Novaland::Projectile
