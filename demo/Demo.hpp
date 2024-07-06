#pragma once

// C++
#include <memory>

// box2d
#include <box2d/b2_world.h>

std::unique_ptr<b2World> CreateDemoWorld(b2Vec2 size);
