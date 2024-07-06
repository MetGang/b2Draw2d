// b2Draw raylib
#include <b2Draw_raylib.hpp>

// box2d
#include <box2d/box2d.h>

// raylib
#include <raylib.h>

//
#include "Demo.hpp"

int main()
{
    // Create raylib window for application
    InitWindow(1280, 720, "b2Draw2d raylib demo");

    // Limit framerate for sake of consistency
    SetTargetFPS(60);

    // Create debug drawer for window with 10x scale
    b2Draw_raylib drawer;
    drawer.SetScale(10.0f);

    // Set flags for things that should be drawn
    // ALWAYS rememeber to set at least one flag
    // otherwise nothing will be drawn
    drawer.SetFlags(
        b2Draw::e_shapeBit |
        b2Draw::e_centerOfMassBit
    );

    // Create box2d demo world
    auto world = CreateDemoWorld({ 128.0f, 72.0f });

    // Set our drawer as world's drawer
    world->SetDebugDraw(&drawer);

    // Variable for holding pause state (obviously)
    bool paused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
            paused = !paused;
        else if (IsKeyPressed(KEY_ONE))
            drawer.ToggleFlags(b2Draw::e_shapeBit);
        else if (IsKeyPressed(KEY_TWO))
            drawer.ToggleFlags(b2Draw::e_jointBit);
        else if (IsKeyPressed(KEY_THREE))
            drawer.ToggleFlags(b2Draw::e_aabbBit);
        else if (IsKeyPressed(KEY_FOUR))
            drawer.ToggleFlags(b2Draw::e_pairBit);
        else if (IsKeyPressed(KEY_FIVE))
            drawer.ToggleFlags(b2Draw::e_centerOfMassBit);
        else if (IsKeyPressed(KEY_R))
            for (auto b = world->GetBodyList(); b != nullptr; b = b->GetNext())
                b->SetGravityScale(-b->GetGravityScale());

        // Calculate delta time as float seconds
        float dt = GetFrameTime();

        // Calculate physics
        if (!paused)
        {
            world->Step(dt, 6, 2);
        }

        // Begin drawing
        BeginDrawing();

        // Clear window
        ClearBackground(BLACK);

        // Draw debug shapes of all physics objects
        world->DebugDraw();

        // End drawing (display window content)
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
