#pragma once

// raylib
#include <raylib.h>

// box2d
#include <box2d/b2_draw.h>

class b2Draw_raylib : public b2Draw
{
public:

    b2Draw_raylib() noexcept;

    void ToggleFlags(uint32 flags) noexcept;

    void SetScale(float scale) noexcept;

    float GetScale() noexcept;

protected:

    void DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept;

    void DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept;

    void DrawCircle(b2Vec2 const& center, float radius, b2Color const& color) noexcept;

    void DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& axis, b2Color const& color) noexcept;

    void DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color) noexcept;

    void DrawTransform(b2Transform const& xf) noexcept;

    void DrawPoint(b2Vec2 const& p, float size, b2Color const& color) noexcept;

private:

    float M_Convert(float f) const noexcept;

    Vector2 M_Convert(b2Vec2 v) const noexcept;

    Color M_Convert(b2Color c) const noexcept;

    float m_scale;
};
