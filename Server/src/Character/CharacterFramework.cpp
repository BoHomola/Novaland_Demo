////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFramework.cpp
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterFramework.h"

namespace Novaland::Character
{
void CharacterFramework::FixedUpdate()
{
    m_state_component.UpdateState();
    m_event_dispatcher.FireEvents();
    m_input_component.ApplyInput();
}
} // namespace Novaland::Character
