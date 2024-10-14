////////////////////////////////////////////////////////////////////////////////
// File:        NovalandRoot.h
// Author:      Bohumil Homola
// Date:        09/15/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "GDMacros.h"
#include "NLCharacterManager.h"
#include "NLNovalandDebug.h"
#include "NLProjectileManager.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/string.hpp>

class NLNovalandRoot : public godot::Node
{
    GDCLASS(NLNovalandRoot, godot::Node)

  public:
    static void _bind_methods();
    static void _register_methods();

    NLNovalandRoot();
    ~NLNovalandRoot() override;

    void _process(float delta);
    void _physics_process(float delta);
    void InitializeNovalandRoot(godot::String ip_address, i32 port);

    GD_EXPOSE(character_manager_node_path, godot::NodePath)
    GD_EXPOSE(projectile_manager_node_path, godot::NodePath)
    GD_EXPOSE(novaland_debug_node_path, godot::NodePath)

  protected:
  private:
    Novaland::Vec2 GetKeyMovementInput();
    Novaland::Vec2 GetJoystickMovementInput();
    Novaland::Vec2 GetSecondaryJoystickMovementInput();
    u8 GetKeyInput();

  private:
    Novaland::Client *client;
    godot::Input *input;
    godot::Engine *engine;
    NLCharacterManager *character_manager = nullptr;
    NLProjectileManager *projectile_manager = nullptr;
    NLNovalandDebug *novaland_debug = nullptr;
};
