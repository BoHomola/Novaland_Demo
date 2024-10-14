////////////////////////////////////////////////////////////////////////////////
// File:        ClientCharacter.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Export.h"
#include "Physics/Rigidbody.h"
#include "Projectile/ProjectileFramework.h"

EXPORT Novaland::Physics::Rigidbody *GetProjectileRigidbody(Novaland::Projectile::ProjectileFramework *projectile)
{
    return projectile->m_projectile.rigidbody;
}

EXPORT Novaland::Physics::Transform GetProjectileInterpolatedTransform(
    Novaland::Projectile::ProjectileFramework *projectile)
{
    return projectile->m_interpolator.interpolated_transform;
}

EXPORT u32 GetProjectileId(Novaland::Projectile::ProjectileFramework *projectile)
{
    return projectile->id;
}
