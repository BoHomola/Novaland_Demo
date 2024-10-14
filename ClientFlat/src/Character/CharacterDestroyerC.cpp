////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreatorC.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Export.h"

typedef void (*OnCharacterDestroyedCallback)(u32 character_id);

EXPORT void RegisterCharacterDestroyedCallback(Novaland::Client *client, OnCharacterDestroyedCallback callback)
{
    client->character_destroyer->OnCharacterDestroyed = callback;
}
