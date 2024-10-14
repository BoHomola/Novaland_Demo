////////////////////////////////////////////////////////////////////////////////
// File:        main.cpp
// Author:      Bohumil Homola
// Date:        10/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Logger.h"
#include "NovalandCommon.h"
#include <CLI/CLI.hpp>
#include <iostream>

using namespace Novaland;

int main(int argc, char *argv[])
{
    CLI::App app{"Novaland Client Mock"};

    std::string ip_address = "127.0.0.1";
    app.add_option("-a,--ip_address", ip_address, "IP address (e.g., 192.168.0.1)");

    u16 port = 5600;
    app.add_option("-p,--port", port, "port (e.g., 80) default = 5600");

    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        Logger::Error(e.what());
        return app.exit(e);
    }

    Novaland::Client *client = new Novaland::Client();

    client->Connect(ip_address, port);
    bool is_running = true;

    auto next_tick_time = std::chrono::steady_clock::now();
    auto tick_duration = std::chrono::milliseconds(1000 / 20);
    client->tick_manager->SetDeltaTime(1.0f / (f32)20);

    client->input_handler->SetKeyboardInput({1, 1});

    while (is_running)
    {
        bool is_shooting = client->tick_manager->GetCurrentTick() % 100 == 0;
        u8 keys = 0;
        if (is_shooting)
        {
            keys |= (1 << 0);
        }

        client->input_handler->SetKeys(keys);
        client->FixedUpdate();
        std::this_thread::sleep_until(next_tick_time += tick_duration);
    }
    return 0;
}
