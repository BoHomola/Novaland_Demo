///////////////////////////////////////////////////////////////////////////////
// File:        NLProjectileManager.h
// Author:      Bohumil Homola
// Date:        10/01/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "GDMacros.h"
#include "Projectile/ProjectileFramework.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace Novaland;

class NLProjectileManager : public godot::Node3D
{
    GDCLASS(NLProjectileManager, godot::Node3D);

  public:
    static void _bind_methods();

    NLProjectileManager();
    ~NLProjectileManager();

    GD_EXPOSE(projectile_scene, godot::Ref<godot::PackedScene>)
    GD_EXPOSE(projectile_bounce_particle_scene, godot::Ref<godot::PackedScene>)

  public:
    void OnUpdate();
    void Init(Novaland::Client *client);

  private:
    void OnProjectileCreated(Projectile::ProjectileFramework *projectile);
    void OnProjectileDestroyed(u32 projectile_id);
    void OnProjectileBounce(Projectile::ProjectileFramework *, const Physics::IContactInfo &);

  private:
    godot::Engine *engine;
    Novaland::Client *client;
    std::unordered_map<u32, Node3D *> projectiles_dict;
};
