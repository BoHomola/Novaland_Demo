#pragma once

#include "Base/Component/ObjectWithId.h"
#include "NovalandCommon.h"

namespace Novaland::Entity
{

enum EntityType : u8
{
    NONE = 0,
    ANY = 1,
    CHARACTER = 2,
    PROJECTILE = 3
};

class IEntity : public ObjectWithId
{
  public:
    EntityType type = EntityType::NONE;
};

} // namespace Novaland::Entity
