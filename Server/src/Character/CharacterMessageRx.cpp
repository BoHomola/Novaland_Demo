////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.cpp
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterMessageRx.h"
#include "DependencyInjector.h"
#include "GameTags.h"
#include "Logger.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "SerClient.h"
#include "zpp_bits.h"

namespace Novaland::Character
{

CharacterMessageRx::CharacterMessageRx()
{
    Dependency::Register<CharacterMessageRx>(this);
    m_character_container = Dependency::Get<Container<CharacterFramework>>();

    Initialize(Dependency::Get<MessageDispatcher>()->message_handlers);
}

void CharacterMessageRx::Initialize(MessageHandlerMap_t &message_handler)
{
    message_handler.emplace(GameTag::PLAYER_MOVEMENT_INPUT,
                            [this](Networking::Message *message, Player::Player *player) {
                                this->HandlePlayerMovementInput(message, player);
                            });

    message_handler.emplace(GameTag::PLAYER_KEY_INPUT, [this](Networking::Message *message, Player::Player *player) {
        this->HandlePlayerKeyInput(message, player);
    });
}

void CharacterMessageRx::HandlePlayerMovementInput(Networking::Message *message, Player::Player *player)
{
    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);

    Ser::PlayerMovementInput player_input;
    auto result = in(player_input);

    // PlayerInput input = PlayerInput{{player_input.input.x, player_input.input.y}, player_input.tick};
    // static_cast<ServerCharacter *>(player->character)->input_buffer.Push(input);
    CharacterFramework *character_framework = m_character_container->Get(player->character_id);
    if (character_framework == nullptr)
    {
        return;
    }

    character_framework->m_input_component.ProcessMovementInput({player_input.input.x, player_input.input.y},
                                                                player_input.tick);
}

void CharacterMessageRx::HandlePlayerKeyInput(Networking::Message *message, Player::Player *player)
{
    Ser::PlayerKeyInput *input = static_cast<Ser::PlayerKeyInput *>(message->GetMessagePtr());

    CharacterFramework *character_framework = m_character_container->Get(player->character_id);
    if (character_framework == nullptr)
    {
        return;
    }

    character_framework->m_input_component.ProcessInputKeys(input->keys, input->tick);
}

CharacterMessageRx::~CharacterMessageRx()
{
}
} // namespace Novaland::Character
