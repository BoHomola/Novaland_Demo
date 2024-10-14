////////////////////////////////////////////////////////////////////////////////
// File:        Categories.h
// Author:      Bohumil Homola
// Date:        11/18/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"

namespace Novaland::Categories
{
const u16 CATEGORY_NONE = 0x0000;
const u16 CATEGORY_ANY = 0xFFFF;
const u16 CATEGORY_STATIC = 0x0001;
const u16 CATEGORY_CHARACTER = 0x0002;
const u16 CATEGORY_PROJECTILE = 0x0004;
} // namespace Novaland::Categories
