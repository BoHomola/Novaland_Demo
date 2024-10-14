////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreatorC.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Export.h"

typedef void (*OnProjectileDestroyedCallback)(u32 projectile_id);

EXPORT void RegisterProjectileDestroyedCallback(Novaland::Client *client, OnProjectileDestroyedCallback callback)
{
    client->projectile_destroyer->OnProjectileDestroyed = callback;
}
