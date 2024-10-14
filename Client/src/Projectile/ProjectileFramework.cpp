////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileFramework.cpp
// Author:      Bohumil Homola
// Date:        12/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileFramework.h"

namespace Novaland::Projectile
{

void ProjectileFramework::Update(f32 delta_time)
{
    m_interpolator.Interpolate(delta_time);
}

void ProjectileFramework::FixedUpdate()
{
    m_life_component.Tick();
    m_interpolator.PreUpdate();
}

void ProjectileFramework::PostFixedUpdate()
{
    m_interpolator.PostUpdate();
}

} // namespace Novaland::Projectile
