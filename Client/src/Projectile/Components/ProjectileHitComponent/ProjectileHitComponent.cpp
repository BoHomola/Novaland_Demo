////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCollisionHandeler.cpp
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileHitComponent.h"

namespace Novaland::Projectile
{

void ProjectileHitController::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_interpolator = builder.Get<ProjectileInterpolator>();
    m_projectile = builder.Get<Projectile>();
}

void ProjectileHitController::HandleProjectileAnyHit(const Physics::IContactInfo &contact_info)
{
    m_interpolator->SetMidPoint(contact_info.GetContactPoint(), m_projectile->rigidbody->GetAngle());

    if (OnProjectileCollision != nullptr)
    {
        OnProjectileCollision(contact_info);
    }
}

} // namespace Novaland::Projectile
