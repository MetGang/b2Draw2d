#include "Demo.hpp"

// C++
#include <random>

// box2d
#include <box2d/box2d.h>

std::unique_ptr<b2World> CreateDemoWorld(b2Vec2 size)
{
    float width = size.x;
    float height = size.y;

    float left = 0.0f;
    float right = width;
    float top = 0.0f;
    float bottom = height;

    std::unique_ptr<b2World> world{ new b2World{ { 0.0f, 9.80665f } } };

    // Walls
    {
        b2BodyDef bdef;
        b2EdgeShape shape;

        // left
        shape.SetTwoSided({ left, top }, { left, bottom });
        world->CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // right
        shape.SetTwoSided({ right, top }, { right, bottom });
        world->CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // top
        shape.SetTwoSided({ left, top }, { right, top });
        world->CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // bottom
        shape.SetTwoSided({ left, bottom }, { right, bottom });
        world->CreateBody(&bdef)->CreateFixture(&shape, 0.0f);
    }

    // Cross
    {
        b2BodyDef bdef;
        b2PolygonShape shape;

        bdef.position = { width * 0.5f, height * 0.5f };
        shape.SetAsBox(width / 8.0f, height / 64.0f);

        bdef.angle = 0.0f;
        world->CreateBody(&bdef)->CreateFixture(&shape, 1.0f);

        bdef.angle = 3.14159f / 2.0f;
        world->CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }

    // Mixers
    {
        b2BodyDef bdef;
        b2PolygonShape shape;
        b2Body* body;

        bdef.type = b2_kinematicBody;
        shape.SetAsBox(width / 8.0f, height / 64.0f);

        bdef.position = { width * 0.2f, height * 0.25f };
        body = world->CreateBody(&bdef);
        body->CreateFixture(&shape, 1.0f);
        body->SetAngularVelocity(3.0f);

        bdef.position = { width * 0.2f, height * 0.75f };
        body = world->CreateBody(&bdef);
        body->CreateFixture(&shape, 1.0f);
        body->SetAngularVelocity(3.0f);

        bdef.position = { width * 0.8f, height * 0.25f };
        body = world->CreateBody(&bdef);
        body->CreateFixture(&shape, 1.0f);
        body->SetAngularVelocity(3.0f);

        bdef.position = { width * 0.8f, height * 0.75f };
        body = world->CreateBody(&bdef);
        body->CreateFixture(&shape, 1.0f);
        body->SetAngularVelocity(3.0f);
    }

    auto rng = std::mt19937{ std::random_device{}() };
    auto vposD = std::uniform_real_distribution<float>{ width * 0.1f, width * 0.9f };
    auto hposD = std::uniform_real_distribution<float>{ height * 0.1f, height * 0.9f };
    auto sizeD = std::uniform_real_distribution<float>{ width / 100.0f, width / 50.0f };

    // Falling rectangles
    for (size_t i = 0; i < 20; ++i)
    {
        b2BodyDef bdef;
        b2PolygonShape shape;

        bdef.position = { vposD(rng), hposD(rng) };
        bdef.type = b2_dynamicBody;
        shape.SetAsBox(sizeD(rng), sizeD(rng));
        world->CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }

    // Falling irregulars
    for (size_t i = 0; i < 20; ++i)
    {
        b2BodyDef bdef;
        b2PolygonShape shape;

        bdef.position = { vposD(rng), hposD(rng) };
        bdef.type = b2_dynamicBody;
        shape.m_vertices[0] = { -sizeD(rng), -sizeD(rng) };
        shape.m_vertices[1] = {  sizeD(rng), -sizeD(rng) };
        shape.m_vertices[2] = {  sizeD(rng),  sizeD(rng) };
        shape.m_vertices[3] = { -sizeD(rng),  sizeD(rng) };
        shape.m_count = 4;
        world->CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }

    // Falling circles
    for (size_t i = 0; i < 20; ++i)
    {
        b2BodyDef bdef;
        b2CircleShape shape;

        bdef.position = { vposD(rng), hposD(rng) };
        bdef.type = b2_dynamicBody;
        shape.m_radius = sizeD(rng);
        world->CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }

    return world;
}
