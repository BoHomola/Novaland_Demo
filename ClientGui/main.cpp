////////////////////////////////////////////////////////////////////////////////
// File:        main.cpp
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include <NovalandCommon.h>
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <thread>

const float m_target_framerate = 1.0f / 60.0f; // 60Hz => ~16.67ms per frame
const float m_target_fixed_update = TimeUtils::GetStepRate();

int main()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
    auto initialUpdateTime = std::chrono::steady_clock::now();
    auto initialFixedUpdateTime = std::chrono::steady_clock::now();

    auto nextFixedUpdate = initialFixedUpdateTime;
    auto nextUpdate = initialUpdateTime;

    f32 delta_time = 0.0f;
    auto lastTime = std::chrono::steady_clock::now();

    Novaland::Application *app = new Novaland::Application();
    app->Init(1200, 800);

    while (!WindowShouldClose())
    {
        auto now = std::chrono::steady_clock::now();

        if (now >= nextFixedUpdate)
        {
            app->FixedUpdate();
            nextFixedUpdate += std::chrono::milliseconds((int)(m_target_fixed_update * 1000));
        }
        if (now >= nextUpdate)
        {
            delta_time = std::chrono::duration<f32>(now - lastTime).count();
            lastTime = now;
            app->Update(delta_time);

            nextUpdate += std::chrono::milliseconds((int)(m_target_framerate * 1000));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    delete app;
    rl_CloseWindow();
    return 0;
}
