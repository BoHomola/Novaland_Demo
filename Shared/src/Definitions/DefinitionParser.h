////////////////////////////////////////////////////////////////////////////////
// File:        NovalandDefinitions.h
// Author:      Bohumil Homola
// Date:        10/20/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Definitions/CharacterDefinition.h"
#include "Definitions/CharacterDefinitionProvider.h"
#include "Definitions/ProjectileDefinitionProvider.h"
#include "DependencyInjector.h"
#include "Misc/HttpRequest.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Novaland::Definitions
{
class DefinitionParser
{
  private:

  public:
    DefinitionParser()
    {
        m_character_definition_provider = Dependency::Get<CharacterDefinitionProvider>();
        m_projectile_definition_provider = Dependency::Get<ProjectileDefinitionProvider>();
    }

    ~DefinitionParser(){};

  public:
    void Parse(std::string url)
    {
        auto definitions = Http::MakeHttpRequest(url);
        if (!definitions.empty())
        {
            Logger::Info("Successfully loaded definitions: " + url);
        }
        auto json = nlohmann::json::parse(definitions);
        std::vector<CharacterDefinition> characters = ParseCharacters(json);
        m_character_definition_provider->Initialize(characters);
        std::vector<ProjectileDefinition> projectiles = ParseProjectiles(json);
        m_projectile_definition_provider->Initialize(projectiles);
    }

  private:
    std::vector<CharacterDefinition> ParseCharacters(nlohmann::json &json)
    {
        std::vector<CharacterDefinition> characters;
        for (auto &character : json["definitions"]["character_definitions"])
        {
            CharacterDefinition character_definition;
            character_definition.definition_id = character["definition_id"];
            character_definition.base_health = character["base_health"];
            character_definition.base_fire_delay = character["base_fire_delay"];
            character_definition.base_fire_cooldown = character["base_fire_cooldown"];
            character_definition.projectile_definition_id = character["projectile_definition_id"];
            character_definition.base_movement_speed = character["base_movement_speed"];
            character_definition.base_angular_speed = character["base_angular_speed"];
            character_definition.projectile_spawn_offet =
                Vec2(character["projectile_spawn_offet"]["x"], character["projectile_spawn_offet"]["y"]);
            character_definition.collider_definition.radius = character["collider_definition"]["radius"];
            ParseRigidbodyProperties(character["rigidbody_properties"], character_definition.rigidbody_properties);

            characters.push_back(character_definition);
        }
        return std::move(characters);
    }

    std::vector<ProjectileDefinition> ParseProjectiles(nlohmann::json &json)
    {
        std::vector<ProjectileDefinition> projectiles;
        for (auto &projectile : json["definitions"]["projectile_definitions"])
        {
            ProjectileDefinition projectile_definition{};
            projectile_definition.definition_id = projectile["definition_id"];
            projectile_definition.speed = projectile["speed"];
            projectile_definition.damage = projectile["damage"];
            projectile_definition.tick_duration = projectile["tick_duration"];
            projectile_definition.collider_definition.radius = projectile["collider_definition"]["radius"];
            ParseRigidbodyProperties(projectile["rigidbody_properties"], projectile_definition.rigidbody_properties);
            projectiles.push_back(projectile_definition);
        }
        return std::move(projectiles);
    }

    void ParseRigidbodyProperties(nlohmann::json &json, Physics::RigidbodyParameters &rigidbody_properties)
    {
        rigidbody_properties.linear_damping = json["linear_damping"];
        rigidbody_properties.angular_damping = json["angular_damping"];
        rigidbody_properties.density = json["density"];
        rigidbody_properties.friction = json["friction"];
        rigidbody_properties.restitution = json["restitution"];
        rigidbody_properties.group_index = json["group_index"];
        rigidbody_properties.mask_bits = json["mask_bits"];
        rigidbody_properties.category_bits = json["category_bits"];
    }

  private:
    CharacterDefinitionProvider *m_character_definition_provider;
    ProjectileDefinitionProvider *m_projectile_definition_provider;
};
} // namespace Novaland::Definitions
