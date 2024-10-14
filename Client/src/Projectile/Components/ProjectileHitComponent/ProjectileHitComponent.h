////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCollisionHandeler.h
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Physics/CollisionListener.h"
#include "Projectile/Components/ProjectileInterpolation/ProjectileInterpolation.h"

namespace Novaland::Projectile
{

class ProjectileHitController : IComponent
{
  public:
    ProjectileHitController() = default;
    ~ProjectileHitController() override = default;

    virtual void HandleProjectileAnyHit(const Physics::IContactInfo &contact_info);

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

  public:
    std::function<void(const Physics::IContactInfo &)> OnProjectileCollision = nullptr;

  private:
    ProjectileInterpolator *m_interpolator = nullptr;
    Projectile *m_projectile = nullptr;
};

} // namespace Novaland::Projectile
