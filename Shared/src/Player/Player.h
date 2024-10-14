#pragma once

#include "Base/Component/ObjectWithId.h"

namespace Novaland::Player
{

struct Player : public ObjectWithId
{
  public:
    u32 character_id;
};

} // namespace Novaland::Player
