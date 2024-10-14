////////////////////////////////////////////////////////////////////////////////
// File:        CameraHanlder.cpp
// Author:      Bohumil Homola
// Date:        09/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CameraHandler.h"
#include "GDMacros.h"
#include "Logger.h"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

void CameraHandler::_bind_methods()
{
    GD_BIND(CameraHandler, character_manager_node, godot::Variant::NODE_PATH);
    GD_BIND(CameraHandler, y_offset, godot::Variant::FLOAT);
    GD_BIND(CameraHandler, z_offset, godot::Variant::FLOAT);
    GD_BIND(CameraHandler, follow_speed, godot::Variant::FLOAT);
}

CameraHandler::CameraHandler()
{
    character_manager = nullptr;
    own_character = nullptr;
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

CameraHandler::~CameraHandler()
{
}

void CameraHandler::_ready()
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
    character_manager = get_node<NLCharacterManager>(character_manager_node);
    if (!character_manager)
    {
        Logger::Error("Character manager not found!");
        return;
    }

    character_manager->OnOwnCharacterCreated = [this](godot::Node3D *character_node) {
        OnOwnCharacterCreated(character_node);
    };
}

void CameraHandler::_process(float delta)
{
    if (engine->is_editor_hint())
    {
        return;
    }

    if (!own_character)
    {
        return;
    }

    godot::Vector3 target = own_character->get_position();
    target.y += y_offset;
    target.z += z_offset;
    godot::Vector3 new_position = get_position().lerp(target, delta * follow_speed);
    this->set_position(new_position);
}

void CameraHandler::OnOwnCharacterCreated(godot::Node3D *character_node)
{
    own_character = character_node;
}
