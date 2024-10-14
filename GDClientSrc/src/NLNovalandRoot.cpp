////////////////////////////////////////////////////////////////////////////////
// File:        NovalandRoot.cpp
// Author:      Bohumil Homola
// Date:        09/15/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NLNovalandRoot.h"
#include "GDMacros.h"
#include "Input/Input.h"
#include "NovalandCommon.h"
#include "godot_cpp/classes/engine.hpp"
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <string>

NLNovalandRoot::NLNovalandRoot()
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }

    input = godot::Input::get_singleton();

    client = new Novaland::Client();
}

void NLNovalandRoot::InitializeNovalandRoot(godot::String ip_address, i32 port)
{
    character_manager = get_node<NLCharacterManager>(character_manager_node_path);
    character_manager->Init(client);

    projectile_manager = get_node<NLProjectileManager>(projectile_manager_node_path);
    projectile_manager->Init(client);

    novaland_debug = get_node<NLNovalandDebug>(novaland_debug_node_path);
    novaland_debug->Init(client);

    const char *ip = ip_address.utf8().get_data();
    std::string ip_str(ip);
    client->Connect(ip_str, port);
}

NLNovalandRoot::~NLNovalandRoot()
{
    if (engine->is_editor_hint())
    {
        return;
    }
    delete client;
}

void NLNovalandRoot::_bind_methods()
{
    GD_BIND(NLNovalandRoot, character_manager_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandRoot, projectile_manager_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandRoot, novaland_debug_node_path, godot::Variant::NODE_PATH);

    godot::ClassDB::bind_method(godot::D_METHOD("InitializeNovalandRoot"), &NLNovalandRoot::InitializeNovalandRoot,
                                "ip_address", "port");
}

Novaland::Vec2 NLNovalandRoot::GetKeyMovementInput()
{
    Novaland::Vec2 input_vec = {0, 0};
    if (input->is_action_pressed("forward"))
    {
        input_vec.y = 1;
    }
    if (input->is_action_pressed("left"))
    {
        input_vec.x = 1;
    }
    if (input->is_action_pressed("right"))
    {
        input_vec.x = -1;
    }
    return input_vec;
}

Novaland::Vec2 NLNovalandRoot::GetJoystickMovementInput()
{
    Novaland::Vec2 joystick_input_vec = {0, 0};

    joystick_input_vec.x = input->get_axis("js_left", "js_right");
    joystick_input_vec.y = input->get_axis("js_down", "js_up");

    return joystick_input_vec;
}

Novaland::Vec2 NLNovalandRoot::GetSecondaryJoystickMovementInput()
{
    Novaland::Vec2 secondary_joystick_input_vec = {0, 0};

    secondary_joystick_input_vec.x = input->get_axis("s_js_left", "s_js_right");
    secondary_joystick_input_vec.y = input->get_axis("s_js_down", "s_js_up");

    return secondary_joystick_input_vec;
}

u8 NLNovalandRoot::GetKeyInput()
{
    u8 keys = 0;
    if (input->is_action_just_pressed("fire"))
    {
        keys |= Novaland::Input::InputKey::ATTACK;
    }

    if (input->is_action_just_pressed("special_ability_1"))
    {
        keys |= Novaland::Input::InputKey::SPECIAL_ABILITY_1;
    }

    if (input->is_action_just_pressed("special_ability_2"))
    {
        keys |= Novaland::Input::InputKey::SPECIAL_ABILITY_2;
    }

    return keys;
}

void NLNovalandRoot::_process(float delta)
{
    if (engine->is_editor_hint())
    {
        return;
    }

    client->Update(delta);

    character_manager->OnUpdate();
    projectile_manager->OnUpdate();
}

void NLNovalandRoot::_physics_process(float delta)
{
    if (engine->is_editor_hint())
    {
        return;
    }

    client->input_handler->SetKeyboardInput(GetKeyMovementInput());
    client->input_handler->SetJoystickInput(GetJoystickMovementInput());
    client->input_handler->SetSecondaryJoystickInput(GetSecondaryJoystickMovementInput());
    client->input_handler->SetKeys(GetKeyInput());

    client->FixedUpdate();
}
