////////////////////////////////////////////////////////////////////////////////
// File:        CameraHandler.h
// Author:      Bohumil Homola
// Date:        09/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "GDMacros.h"
#include "NLCharacterManager.h"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/node_path.hpp>

class CameraHandler : public godot::Camera3D
{
    GDCLASS(CameraHandler, godot::Camera3D)

  public:
    static void _bind_methods();

    CameraHandler();
    ~CameraHandler();

    void _ready() override;
    void _process(float delta);

    GD_EXPOSE(character_manager_node, godot::NodePath)
    GD_EXPOSE(y_offset, f32)
    GD_EXPOSE(z_offset, f32)
    GD_EXPOSE(follow_speed, f32)

  private:
    void OnOwnCharacterCreated(godot::Node3D *character_node);

  private:
    NLCharacterManager *character_manager;
    godot::Engine *engine;
    Node3D *own_character;
};
