////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFramework.cpp
// Author:      Bohumil Homola
// Date:        11/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterFramework.h"

namespace Novaland::Character
{
void CharacterFramework::Update(f32 delta_time)
{
    m_interpolator.Interpolate(delta_time);
}

void CharacterFramework::FixedUpdate()
{
    m_state_component.UpdateState();
    m_interpolator.PreUpdate();
}

void CharacterFramework::PostFixedUpdate()
{
    m_interpolator.PostUpdate();
}
} // namespace Novaland::Character
