////////////////////////////////////////////////////////////////////////////////
// File:        CharacterMessageTx.cpp
// Author:      Bohumil Homola
// Date:        09/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterMessageTx.h"
#include "DependencyInjector.h"
#include "Logger.h"
#include "SerClient.h"
#include "zpp_bits.h"

namespace Novaland::Character
{

CharacterMessageTx::CharacterMessageTx()
{
    Dependency::Register<CharacterMessageTx>(this);
    tick_manager = Dependency::Get<TickManager>();
    network_manager = Dependency::Get<Networking::ClientNetworkManager>();
}

void CharacterMessageTx::SendCharacterInput(CharacterInput &input)
{
    auto [data, out] = zpp::bits::data_out();

    auto movementMessage = network_manager->GetEmptyOutcomingMessage();
    Ser::PlayerMovementInput player_movement_input;
    movementMessage->SetTag(GameTag::PLAYER_MOVEMENT_INPUT);

    player_movement_input.input.x = input.movement_input.x;
    player_movement_input.input.y = input.movement_input.y;
    player_movement_input.tick = tick_manager->GetCurrentTick();

    auto result = out(player_movement_input);
    memcpy(movementMessage->GetMessagePtr(), data.data(), data.size());
    movementMessage->length = data.size();

    auto inputKeyMessage = network_manager->GetEmptyOutcomingMessage();
    Ser::PlayerKeyInput player_key_input;
    inputKeyMessage->SetTag(GameTag::PLAYER_KEY_INPUT);
    player_key_input.keys = input.keys;
    player_key_input.tick = tick_manager->GetCurrentTick();

    auto dataPtr = static_cast<Ser::PlayerKeyInput *>(inputKeyMessage->GetMessagePtr());
    *dataPtr = player_key_input;
    inputKeyMessage->length = sizeof(player_key_input);

    network_manager->Send(movementMessage, Networking::SendMode::Unreliable);
    network_manager->Send(inputKeyMessage, Networking::SendMode::Reliable);
};

} // namespace Novaland::Character
