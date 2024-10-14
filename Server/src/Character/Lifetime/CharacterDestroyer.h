////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDestroyer.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/CharacterFramework.h"
#include "Physics/PhysicsWorld.h"
namespace Novaland::Character
{

class CharacterDestroyer
{
  public:
    CharacterDestroyer()
    {
        Dependency::Register<CharacterDestroyer>(this);

        character_container = Dependency::Get<Container<CharacterFramework>>();
        physics_world = Dependency::Get<Physics::PhysicsWorld>();
    };

    void DestroyCharacter(u32 character);

  private:
    Container<CharacterFramework> *character_container;
    Physics::PhysicsWorld *physics_world;
};

} // namespace Novaland::Character
