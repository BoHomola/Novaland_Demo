////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileController.h
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Projectile/Projectile.h"
#include "Tick/TickManger.h"
namespace Novaland::Projectile
{

class ProjectileController
{
  public:
    ProjectileController();
    ~ProjectileController();

  protected:
    virtual void DestroyProjectile(Projectile *projectile) = 0;

    void UpdateProjectile(Projectile *projectile);

  protected:
    TickManager *m_tick_manager;
};

} // namespace Novaland::Projectile
