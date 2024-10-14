////////////////////////////////////////////////////////////////////////////////
// File:        GDCharacter.cpp
// Author:      Bohumil Homola
// Date:        09/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NLCharacter.h"
#include <godot_cpp/classes/node3d.hpp>

NLCharacter::NLCharacter()
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

NLCharacter::~NLCharacter()
{
}

void NLCharacter::_bind_methods()
{
}

void NLCharacter::_ready()
{
    godot::Node3D::_ready();
    if (engine->is_editor_hint())
    {
        return;
    }
}

void NLCharacter::_process(float delta)
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

void NLCharacter::_physics_process(float delta)
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}
