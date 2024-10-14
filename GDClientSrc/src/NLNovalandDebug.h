////////////////////////////////////////////////////////////////////////////////
// File:        NovalandDebug.h
// Author:      Bohumil Homola
// Date:        09/15/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "GDMacros.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/string.hpp>

class NLNovalandDebug : public godot::Node
{
    GDCLASS(NLNovalandDebug, godot::Node)

  public:
    static void _bind_methods();

    NLNovalandDebug();
    ~NLNovalandDebug() override;

    void _process(float delta);
    void _physics_process(float delta);
    void _ready() override;

    void Init(Novaland::Client *client);

    GD_EXPOSE(godot_menu_node_path, godot::NodePath)
    GD_EXPOSE(fps_label_node_path, godot::NodePath)
    GD_EXPOSE(rtt_label_node_path, godot::NodePath)
    GD_EXPOSE(pos_x_node_path, godot::NodePath)
    GD_EXPOSE(pos_y_node_path, godot::NodePath)
    GD_EXPOSE(angle_node_path, godot::NodePath)

  private:
    bool is_debug_menu_open = true;

  private:
    Novaland::Client *client = nullptr;
    godot::Engine *engine;
    godot::Input *input;

    godot::Label *fps_label;
    godot::Label *rtt_label;
    godot::Label *pos_x_label;
    godot::Label *pos_y_label;
    godot::Label *angle_label;
};
