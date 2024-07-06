// b2Draw SFML
#include <b2Draw_SFML.hpp>

// box2d
#include <box2d/box2d.h>

// SFML
#include <SFML/Graphics.hpp>

//
#include "Demo.hpp"

int main()
{
    // Create SFML window for application
    sf::RenderWindow window{ { 1280u, 720u }, "b2Draw2d SFML demo" };

    // Limit framerate for sake of consistency
    window.setFramerateLimit(60u);

    // Create debug drawer for window with 10x scale
    // You can set any sf::RenderTarget as drawing target
    b2Draw_SFML drawer;
    drawer.SetRenderTarget(window);
    drawer.SetScale(10.0f);

    // Set flags for things that should be drawn
    // ALWAYS remember to set at least one flag,
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

    // Clock for calculating delta time (for physics simulation)
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                    paused = !paused;
                else if (event.key.code == sf::Keyboard::Num1)
                    drawer.ToggleFlags(b2Draw::e_shapeBit);
                else if (event.key.code == sf::Keyboard::Num2)
                    drawer.ToggleFlags(b2Draw::e_jointBit);
                else if (event.key.code == sf::Keyboard::Num3)
                    drawer.ToggleFlags(b2Draw::e_aabbBit);
                else if (event.key.code == sf::Keyboard::Num4)
                    drawer.ToggleFlags(b2Draw::e_pairBit);
                else if (event.key.code == sf::Keyboard::Num5)
                    drawer.ToggleFlags(b2Draw::e_centerOfMassBit);
                else if (event.key.code == sf::Keyboard::R)
                    for (auto b = world->GetBodyList(); b != nullptr; b = b->GetNext())
                        b->SetGravityScale(-b->GetGravityScale());
                else if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            else if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Calculate delta time as float seconds
        float dt = clock.restart().asSeconds();

        // Calculate physics
        if (!paused)
        {
            world->Step(dt, 6, 2);
        }

        // Clear window
        window.clear();

        // Draw debug shapes of all physics objects
        world->DebugDraw();

        // Display window content
        window.display();
    }

    return 0;
}
