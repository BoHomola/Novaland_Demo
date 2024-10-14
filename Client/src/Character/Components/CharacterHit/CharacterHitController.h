////////////////////////////////////////////////////////////////////////////////
// File:        ACharacterHitController.h
// Author:      Bohumil Homola
// Date:        11/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Character/Character.h"
#include "Character/CharacterMessageTx.h"
#include "Projectile/Lifetime/ProjectileDestroyer.h"
#include "SerServer.h"
#include <Projectile/ProjectileFramework.h>

namespace Novaland::Character
{
class CharacterHitHandler : IComponent
{
  public:
    CharacterHitHandler()
    {
        m_character_message_tx = Dependency::Get<CharacterMessageTx>();
        m_projectile_destroyer = Dependency::Get<Projectile::ProjectileDestroyer>();
    }
    ~CharacterHitHandler() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    virtual void HandleCharacterHit(const Ser::CharacterHit &message);

    std::function<void(const Vec2 &hit_point, const f32 hit_angle)> OnCharacterHit;

  private:
    CharacterMessageTx *m_character_message_tx = nullptr;
    Projectile::ProjectileDestroyer *m_projectile_destroyer = nullptr;

  private:
    Character *m_character = nullptr;
};
} // namespace Novaland::Character
