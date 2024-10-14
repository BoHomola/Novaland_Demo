////////////////////////////////////////////////////////////////////////////////
// File:        CharacterContainer.h
// Author:      Bohumil Homola
// Date:        09/07/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/CharacterFramework.h"
#include "Character/OwnCharacterFramework.h"

namespace Novaland::Character
{

class CharacterContainer : public Container<CharacterFramework>
{
  public:
    CharacterContainer() : Container<CharacterFramework>()
    {
        Dependency::Register<CharacterContainer>(this);
        own_character = nullptr;
    }
    ~CharacterContainer() override = default;


  public:
    OwnCharacterFramework *own_character;

  private:
    friend class CharacterDestroyer;
    friend class CharacterCreator;
};
} // namespace Novaland::Character
