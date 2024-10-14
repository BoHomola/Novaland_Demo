#include "CameraHandler.h"
#include "NLCharacter.h"
#include "NLCharacterManager.h"
#include "NLNovalandDebug.h"
#include "NLNovalandRoot.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
    ClassDB::register_class<NLNovalandRoot>();
    ClassDB::register_class<NLCharacterManager>();
    ClassDB::register_class<NLCharacter>();
    ClassDB::register_class<CameraHandler>();
    ClassDB::register_class<NLProjectileManager>();
    ClassDB::register_class<NLNovalandDebug>();
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
}

extern "C"
{
    GDExtensionBool GDE_EXPORT plugin_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                                           GDExtensionClassLibraryPtr p_library,
                                           GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
        init_obj.register_initializer(initialize_gdextension_types);
        init_obj.register_terminator(uninitialize_gdextension_types);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
