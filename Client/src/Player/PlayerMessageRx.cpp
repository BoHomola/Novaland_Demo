////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.cpp
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Player/PlayerMessageRx.h"
#include "DependencyInjector.h"
#include "GameTags.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Player/PlayerCreator.h"
#include "SerServer.h"

namespace Novaland::Player
{
    PlayerMessageRx::PlayerMessageRx()
    {
        Dependency::Register<PlayerMessageRx>(this);
        player_creator = Dependency::Get<PlayerCreator>();

        Initialize(Dependency::Get<MessageDispatcher>()->message_handlers);
    }

    PlayerMessageRx::~PlayerMessageRx()
    {
        Dependency::Unregister<PlayerMessageRx>();
    }

    void PlayerMessageRx::Initialize(MessageHandlerMap_t &message_handler)
    {
        message_handler.emplace(GameTag::NEW_PLAYER, [this](Networking::Message *message, Player *player) {
            this->OnNewPlayer(message, player);
        });
    }

    void PlayerMessageRx::OnNewPlayer(Networking::Message *message, Player *player)
    {

        auto [data, in] = zpp::bits::data_in();
        data.resize(message->length);
        memcpy(data.data(), message->GetMessagePtr(), message->length);
        Ser::PlayerDefinition playerDefinition;
        auto result = in(playerDefinition);

        PlayerInitilizationData player_init_data;
        player_init_data.player_id = playerDefinition.playerId;
        player_init_data.character_definition_id = playerDefinition.characterDefinition.characterDefinitionId;
        player_init_data.character_id = playerDefinition.characterDefinition.characterId;
        auto transform = playerDefinition.characterDefinition.transform;

        Vec2 position = {transform.position.x, transform.position.y};
        Vec2 linear_velocity = {transform.velocity.x, transform.velocity.y};

        player_init_data.transform = {position, transform.rotation};
        player_init_data.velocity = {linear_velocity, transform.angularVelocity};

        player_creator->CreatePlayer(player_init_data);
    }

} // namespace Novaland::Player
