////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreatorC.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterFramework.h"
#include "Client.h"
#include "Export.h"

typedef void (*OnCharacterCreatedCallback)(Novaland::Character::CharacterFramework *, bool);

EXPORT void RegisterCharacterCreatedCallback(Novaland::Client *client, OnCharacterCreatedCallback callback)
{
    client->character_creator->OnCharacterCreated = callback;
}
