#include "DebugStackTrace.h"
#include "Logger.h"
#include "NovalandCommon.h"
#include "NovalandServer.h"
#include "TimeUtils.h"
#include <CLI/CLI.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#ifndef DISABLE_SERVER_GUI
#include "Renderer/EnvironmentRenderer.h"
#else
#include <future>
#endif

int main(int argc, char *argv[])
{
    Backtrace::SetupBacktrace();
    PROFILE_SCOPE;
    CLI::App app{"Novaland Server"};

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

    Logger::SetPrefix("Server");
    Novaland::NovalandServer *server = new Novaland::NovalandServer(ip_address, port, TimeUtils::timestamp);

    std::thread serverThread([&server]() { server->StartServer(); });

#ifdef DISABLE_SERVER_GUI
    Logger::Info("Press any key to stop the server...");
    std::atomic<bool> stopFlag{false};
    auto input = std::async(std::launch::async, [&stopFlag]() {
        std::cin.get();
        stopFlag.store(true);
    });

    while (!stopFlag.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#else
    Novaland::Renderer::RenderWorld(server, server->p_world->m_map);
#endif

    server->StopServer();
    serverThread.join();
    delete server;
}
