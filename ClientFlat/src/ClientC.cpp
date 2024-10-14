////////////////////////////////////////////////////////////////////////////////
// File:        ClientC.h
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Export.h"

EXPORT Novaland::Client *CreateClient()
{
    return new Novaland::Client();
}

EXPORT void DestroyClient(Novaland::Client *client)
{
    delete client;
}

EXPORT void ClientConnect(Novaland::Client *client, const char *address, u32 port)
{
    client->Connect(address, port);
}

EXPORT void ClientUpdate(Novaland::Client *client, f32 deltaTime)
{
    client->Update(deltaTime);
}

EXPORT void ClientFixedUpdate(Novaland::Client *client)
{
    client->FixedUpdate();
}

EXPORT long Add(int a, int b)
{
    return a + b;
}
