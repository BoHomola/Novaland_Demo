////////////////////////////////////////////////////////////////////////////////
// File:        Connection.hpp
// Author:      Bohumil Homola
// Date:        06/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include "enet.h"

#include <string>
namespace Novaland::Networking
{

struct Connection
{
    u32 connection_id;
    ENetPeer *peer;
    void *data;
    bool connected;
    std::string ip_address;
    u16 port;
};

} // namespace Novaland::Networking
