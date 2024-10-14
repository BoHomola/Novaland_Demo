///////////////////////////////////////////////////////////////////////////////
// File:        GDCharacterManager.cpp
// Author:      Bohumil Homola
// Date:        09/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NLCharacterManager.h"
#include "Character/Character.h"
#include "Client.h"
#include "GDMacros.h"
#include "Logger.h"
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace Novaland;

NLCharacterManager::NLCharacterManager()
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

NLCharacterManager::~NLCharacterManager()
{
}

void NLCharacterManager::_bind_methods()
{
    GD_BIND_OBJECT(NLCharacterManager, character_scene, godot::PROPERTY_HINT_RESOURCE_TYPE, PackedScene)
    GD_BIND_OBJECT(NLCharacterManager, character_hit_particles, godot::PROPERTY_HINT_RESOURCE_TYPE, PackedScene)
}

void NLCharacterManager::OnUpdate()
{
    for (Novaland::Character::CharacterFramework *character_framework : client->character_container->GetAll())
    {
        auto transform = character_framework->m_interpolator.interpolated_transform;
        auto characterNode = charactersDict[character_framework->id];
        characterNode->set_position({transform.position.x, 0, transform.position.y});
        characterNode->set_rotation({0, -transform.angle, 0});
    }
}

void NLCharacterManager::OnCharacterCreated(Novaland::Character::CharacterFramework *character_framework, bool is_own)
{
    if (character_scene.is_valid())
    {
        godot::PackedScene *character_packed_asset = *character_scene;
        Node *instance = character_packed_asset->instantiate();
        auto character_node = Object::cast_to<godot::Node3D>(instance);
        character_node->set_name("Character_" + godot::String(std::to_string(character_framework->id).c_str())); // WTF
        add_child(instance);
        Logger::Info("Character created: {}", character_framework->id);
        charactersDict[character_framework->id] = character_node;
        if (is_own)
        {
            OnOwnCharacterCreated(character_node);
        }

        character_framework->m_hit_controller.OnCharacterHit = [this](Vec2 hit_point, f32 angle) {
            this->OnCharacterHit(hit_point, angle);
        };
    }
}

void NLCharacterManager::OnCharacterDestroyed(u32 character_id)
{
    Logger::Info("Character destroyed: {}", character_id);
    if (charactersDict.find(character_id) != charactersDict.end())
    {
        auto characterNode = charactersDict[character_id];
        charactersDict.erase(character_id);
        characterNode->queue_free();
    }
}

void NLCharacterManager::OnCharacterHit(Novaland::Vec2 hit_point, f32 angle)
{
    if (character_hit_particles.is_valid())
    {
        godot::PackedScene *character_hit_packed_asset = *character_hit_particles;
        Node *instance = character_hit_packed_asset->instantiate();
        godot::Node3D *projectileBounceParticleNode = Object::cast_to<godot::Node3D>(instance);
        projectileBounceParticleNode->set_position({hit_point.x, 0, hit_point.y});
        add_child(instance);
    }
}

void NLCharacterManager::Init(Novaland::Client *client)
{
    this->client = client;
    client->character_creator->OnCharacterCreated = [this](Character::CharacterFramework *character_framework,
                                                           bool is_own) {
        this->OnCharacterCreated(character_framework, is_own);
    };
    client->character_destroyer->OnCharacterDestroyed = [this](u32 character_id) {
        this->OnCharacterDestroyed(character_id);
    };
}
