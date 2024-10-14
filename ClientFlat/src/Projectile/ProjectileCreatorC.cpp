////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCreatorC.cpp
// Author:      Bohumil Homola
// Date:        10/15/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Export.h"
#include "Projectile/ProjectileFramework.h"

typedef void (*OnProjectileCreatedCallback)(Novaland::Projectile::ProjectileFramework *);

EXPORT void RegisterProjectileCreatedCallback(Novaland::Client *client, OnProjectileCreatedCallback callback)
{
    client->projectile_creator->OnNewProjectileCreated = callback;
}
