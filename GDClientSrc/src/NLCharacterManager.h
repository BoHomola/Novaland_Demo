////////////////////////////////////////////////////////////////////////////////
// File:        GDCharacterManager.h
// Author:      Bohumil Homola
// Date:        09/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "GDMacros.h"
#include <functional>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/godot.hpp>

class NLCharacterManager : public godot::Node3D
{
    GDCLASS(NLCharacterManager, godot::Node3D)
  public:
    static void _bind_methods();

    NLCharacterManager();
    ~NLCharacterManager() override;

    GD_EXPOSE(character_scene, godot::Ref<godot::PackedScene>)
    GD_EXPOSE(character_hit_particles, godot::Ref<godot::PackedScene>)

  public:
    void Init(Novaland::Client *client);
    std::function<void(godot::Node3D *)> OnOwnCharacterCreated;
    void OnUpdate();

  private:
    void OnCharacterCreated(Novaland::Character::CharacterFramework *character_framework, bool is_own);
    void OnCharacterDestroyed(u32 character_id);
    void OnCharacterHit(Novaland::Vec2 hit_point, f32 angle);

  private:
    godot::Engine *engine;
    Novaland::Client *client;
    std::unordered_map<u32, Node3D *> charactersDict;
};
