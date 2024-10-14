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
#include "SerServer.h"
#include "zpp_bits.h"

namespace Novaland::Character
{

CharacterMessageRx::CharacterMessageRx()
{
    Dependency::Register<CharacterMessageRx>(this);
    m_character_container = Dependency::Get<CharacterContainer>();

    Initialize(Dependency::Get<MessageDispatcher>()->message_handlers);
}

void CharacterMessageRx::Initialize(MessageHandlerMap_t &message_handler)
{
    message_handler[GameTag::CHARACTER_FIRE_START] = [this](Networking::Message *message, Player::Player *_) {
        this->HandleCharacterFireStart(message, _);
    };
    message_handler[GameTag::CHARACTER_FIRE_FINISH] = [this](Networking::Message *message, Player::Player *_) {
        this->HandleCharacterFireFinish(message, _);
    };
    message_handler[GameTag::CHARACTER_HIT] = [this](Networking::Message *message, Player::Player *_) {
        this->HandleCharacterHit(message, _);
    };
}

void CharacterMessageRx::HandleCharacterFireStart(Networking::Message *message, Player::Player *_)
{
    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);
    Ser::CharacterFireStart character_fire_start;
    auto result = in(character_fire_start);

    CharacterFramework *character = m_character_container->Get(character_fire_start.character_id);
    // character->m_fire_component.HandleCharacterFireStart();
}

void CharacterMessageRx::HandleCharacterFireFinish(Networking::Message *message, Player::Player *_)
{

    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);
    Ser::CharacterFire characterFire;
    auto result = in(characterFire);

    CharacterFramework *character = m_character_container->Get(characterFire.characterId);
    if (character == nullptr)
    {
        Logger::Error("Character ID {} not found", characterFire.characterId);
        return;
    }
    character->m_fire_component.HandleCharacterFireFinish(characterFire);
}

void CharacterMessageRx::HandleCharacterHit(Networking::Message *message, Player::Player *_)
{

    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);
    Ser::CharacterHit characterHit;
    auto result = in(characterHit);

    CharacterFramework *character = m_character_container->Get(characterHit.characterId);
    if (character == nullptr)
    {
        Logger::Error("Character ID {} not found", characterHit.characterId);
        return;
    }
    character->m_hit_controller.HandleCharacterHit(characterHit);
}

CharacterMessageRx::~CharacterMessageRx()
{
}

} // namespace Novaland::Character
