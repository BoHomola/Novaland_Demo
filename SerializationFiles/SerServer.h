////////////////////////////////////////////////////////////////////////////////
// File:        SerServer.h
// Author:      Bohumil Homola
// Date:        09/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "SerShared.h"

namespace Novaland
{
namespace Ser
{
// PlayerId
struct PlayerId
{
    u32 id;
};

// Transform
struct Transform
{
    Vector2 position;
    f32 rotation;
    Vector2 velocity;
    f32 angularVelocity;
};

// InitEntityState
struct InitEntityState
{
    u32 entityId;
    Vector2 position;
    Vector2 velocity;
    f32 rotation;
};

// CharacterDefinition
struct CharacterDefinition
{
    u32 characterId;
    u32 characterDefinitionId;
    Transform transform;
    u32 health;
};

// CharacterEntity
struct CharacterEntity
{
    u32 characterId;
    Transform transform;
    u32 health;
};

// PlayerDefinition
struct PlayerDefinition
{
    u32 playerId;
    bool own;
    CharacterDefinition characterDefinition;
};

// ProjectileDefinition
struct ProjectileDefinition
{
    u32 projectileId;
    u32 projectileDefinitionId;
    Transform transform;
    u32 destroyTick;
};

// ProjectileEntity
struct ProjectileEntity
{
    u32 projectileId;
    Transform transform;
};

// GameStateSync
struct GameStateSync
{
    i64 firstTick;
    u32 ownPlayerId;
    std::vector<PlayerDefinition> playerDefinitions;
    std::vector<ProjectileDefinition> projectileDefinitions;
};

// GameStateUpdate
struct GameStateUpdate
{
    u32 tick;
    u32 clientTick;
    std::vector<CharacterEntity> characters;
    std::vector<ProjectileEntity> projectiles;
};

struct CharacterFireStart
{
    u32 character_id;
};

// CharacterFire
struct CharacterFire
{
    u32 tick;
    u32 characterId;
    u32 definitionId;
    InitEntityState projectileState;
    // Vector2 start_position;
    // f32 direction;
    u32 fireTick;
    u32 destroyTick;
};

// CharacterHit
struct CharacterHit
{
    u32 tick;
    u32 characterId;
    u32 projectileId;
    u32 damage;
    u32 health;
    f32 hitAngle;
    Vector2 hitPosition;
};

} // namespace Ser
} // namespace Novaland
