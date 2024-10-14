////////////////////////////////////////////////////////////////////////////////
// File:        GDMacros.h
// Author:      Bohumil Homola
// Date:        09/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#define GD_EXPOSE(variable_name, type)                                                                                 \
  public:                                                                                                              \
    void set_##variable_name(type variable_name)                                                                       \
    {                                                                                                                  \
        this->variable_name = variable_name;                                                                           \
    }                                                                                                                  \
    type get_##variable_name() const                                                                                   \
    {                                                                                                                  \
        return variable_name;                                                                                          \
    }                                                                                                                  \
                                                                                                                       \
  private:                                                                                                             \
    type variable_name;

#define GD_BIND(class_name, variable_name, godot_variant_type)                                                         \
    godot::ClassDB::bind_method(godot::D_METHOD("set_" #variable_name, #variable_name),                                \
                                &class_name::set_##variable_name);                                                     \
    godot::ClassDB::bind_method(godot::D_METHOD("get_" #variable_name), &class_name::get_##variable_name);             \
    godot::ClassDB::add_property(get_class_static(), godot::PropertyInfo(godot_variant_type, #variable_name),          \
                                 "set_" #variable_name, "get_" #variable_name);

#define GD_BIND_OBJECT(class_name, variable_name, godot_property_hint_type, resource_class_name)                       \
    godot::ClassDB::bind_method(godot::D_METHOD("set_" #variable_name, #variable_name),                                \
                                &class_name::set_##variable_name);                                                     \
    godot::ClassDB::bind_method(godot::D_METHOD("get_" #variable_name), &class_name::get_##variable_name);             \
    godot::ClassDB::add_property(                                                                                      \
        get_class_static(),                                                                                            \
        godot::PropertyInfo(godot::Variant::OBJECT, #variable_name, godot_property_hint_type, #resource_class_name),   \
        "set_" #variable_name, "get_" #variable_name);
