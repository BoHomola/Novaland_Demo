////////////////////////////////////////////////////////////////////////////////
// File:        GDCharacter.h
// Author:      Bohumil Homola
// Date:        09/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/godot.hpp>

class NLCharacter : public godot::Node3D
{
    GDCLASS(NLCharacter, godot::Node3D)
  public:
    static void _bind_methods();

    NLCharacter();
    ~NLCharacter();

    void _process(float delta);
    void _physics_process(float delta);
    void _ready() override;

  private:
    godot::Engine *engine;
};
