////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDestroyer.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterContainer.h"

namespace Novaland::Character
{
class CharacterDestroyer
{
  public:
    CharacterDestroyer()
    {
        Dependency::Register<CharacterDestroyer>(this);
        character_container = Dependency::Get<CharacterContainer>();
        physics_world = Dependency::Get<Physics::PhysicsWorld>();
    }
    ~CharacterDestroyer()
    {
        Dependency::Unregister<CharacterDestroyer>();
    }

    void DestroyCharacter(u32 character_id);

  public:
    std::function<void(u32 character_id)> OnCharacterDestroyed = nullptr;

  private:
    CharacterContainer *character_container;
    Physics::PhysicsWorld *physics_world;
};

} // namespace Novaland::Character
