////////////////////////////////////////////////////////////////////////////////
// File:        NovalandDebug.cpp
// Author:      Bohumil Homola
// Date:        09/15/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NLNovalandDebug.h"
#include "Math/Math.h"
#include "godot_cpp/classes/engine.hpp"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

NLNovalandDebug::NLNovalandDebug()
{
    engine = godot::Engine::get_singleton();
    input = godot::Input::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

void NLNovalandDebug::_ready()
{
    if (engine->is_editor_hint())
    {
        return;
    }

    fps_label = get_node<godot::Label>(fps_label_node_path);
    rtt_label = get_node<godot::Label>(rtt_label_node_path);
    pos_x_label = get_node<godot::Label>(pos_x_node_path);
    pos_y_label = get_node<godot::Label>(pos_y_node_path);
    angle_label = get_node<godot::Label>(angle_node_path);
}

NLNovalandDebug::~NLNovalandDebug()
{
    if (engine->is_editor_hint())
    {
        return;
    }
}

void NLNovalandDebug::Init(Novaland::Client *client)
{
    this->client = client;
}

void NLNovalandDebug::_bind_methods()
{
    GD_BIND(NLNovalandDebug, godot_menu_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandDebug, fps_label_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandDebug, rtt_label_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandDebug, pos_x_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandDebug, pos_y_node_path, godot::Variant::NODE_PATH);
    GD_BIND(NLNovalandDebug, angle_node_path, godot::Variant::NODE_PATH);
}

void NLNovalandDebug::_process(float delta)
{
    if (engine->is_editor_hint())
    {
        return;
    }

    if (input->is_action_just_pressed("debug_menu"))
    {

        if (!is_debug_menu_open)
        {
            godot::NodePath path = godot_menu_node_path;
            godot::Control *node = get_node<godot::Control>(path);
            node->set_visible(true);
            is_debug_menu_open = true;
        }
        else
        {
            godot::NodePath path = godot_menu_node_path;
            godot::Control *node = get_node<godot::Control>(path);
            node->set_visible(false);
            is_debug_menu_open = false;
        }
    }

    if (is_debug_menu_open && client->game_initialized)
    {
        const i64 decimals = 5;
        fps_label->set_text("FPS: " + godot::String::num(engine->get_frames_per_second()));
        rtt_label->set_text("RTT: " + godot::String::num(client->m_connection->peer->roundTripTime));
        auto char_transform = client->character_container->own_character->m_character.rigidbody->GetTransform();
        pos_x_label->set_text("pos_x: " + godot::String::num(char_transform.position.x, decimals));
        pos_y_label->set_text("pos_y: " + godot::String::num(char_transform.position.y, decimals));
        angle_label->set_text("angle: " + godot::String::num(char_transform.angle, decimals) +
                              " deg: " + godot::String::num(Novaland::Math::Rad2Deg(char_transform.angle), decimals));
    }
}

void NLNovalandDebug::_physics_process(float delta)
{
    if (engine->is_editor_hint())
    {
        return;
    }
}
