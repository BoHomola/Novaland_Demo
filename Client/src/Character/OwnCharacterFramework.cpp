////////////////////////////////////////////////////////////////////////////////
// File:        OwnCharacterFramework.cpp
// Author:      Bohumil Homola
// Date:        11/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "OwnCharacterFramework.h"

namespace Novaland::Character
{
void OwnCharacterFramework::PostFixedUpdate()
{
    CharacterFramework::PostFixedUpdate();
    m_character_snapshot_queue.CaptureCharacterSnapshot();
}

void OwnCharacterFramework::FixedUpdate()
{
    CharacterFramework::FixedUpdate();
    m_input_component.ApplyInput();
}

} // namespace Novaland::Character
