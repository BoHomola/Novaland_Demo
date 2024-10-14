////////////////////////////////////////////////////////////////////////////////
// File:        NetworkMessage.cpp
// Author:      Bohumil Homola
// Date:        07/04/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NetworkMessage.h"
#include "GameTags.h"
#include <cstring>

namespace Novaland::Networking
{

    Message::Message()
    {
        length = 0;
        channel = 0;
    }

    void Message::SetTag(GameTag tag)
    {
        memcpy(data, &tag, sizeof(GameTag));
    }

    const GameTag Message::GetTag()
    {
        GameTag tag;
        memcpy(&tag, data, sizeof(GameTag));
        return tag;
    }

    void *Message::GetMessagePtr()
    {
        return data + sizeof(GameTag);
    }

    void *Message::GetRawData()
    {
        return data;
    }

} // namespace Novaland::Networking
