////////////////////////////////////////////////////////////////////////////////
// File:        FlashData.cpp
// Author:      Bohumil Homola
// Date:        12/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Flash.h"
#include "Math/Vec2.h"

namespace Novaland::Character
{

void Flash::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_character = builder.Get<Character>();
    m_input_component = builder.Get<CharacterInputComponent>();
    m_state = builder.Get<CharacterStateComponent>();
}

void Flash::Proceed()
{
    if (!m_state->IsImmobile())
    {
        Vec2 direction = Vec2::FromRadian(m_character->rigidbody->GetAngle() + M_PI / 2.0f);
        direction = direction.Normalized();
        direction = direction * 5.0f;
        m_character->rigidbody->SetPosition(m_character->rigidbody->GetPosition() + direction);
    }
}
} // namespace Novaland::Character
