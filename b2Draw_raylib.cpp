#include "b2Draw_raylib.hpp"

#define CONV(...) M_Convert(__VA_ARGS__)

b2Draw_raylib::b2Draw_raylib() noexcept
    : m_scale { 1.0f }
{

}

void b2Draw_raylib::ToggleFlags(uint32 flags) noexcept
{
    SetFlags(GetFlags() ^ flags);
}

void b2Draw_raylib::SetScale(float scale) noexcept
{
    m_scale = scale;
}

float b2Draw_raylib::GetScale() noexcept
{
    return m_scale;
}

void b2Draw_raylib::DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept
{
    for (int i = 0; i < vertexCount - 1; ++i)
    {
        DrawLineV(CONV(vertices[i]), CONV(vertices[i + 1]), CONV(color));
    }
    DrawLineV(CONV(vertices[vertexCount - 1]), CONV(vertices[0]), CONV(color));
}

void b2Draw_raylib::DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept
{
    for (int i = 1; i < vertexCount - 1; ++i)
    {
        DrawTriangle(CONV(vertices[0]), CONV(vertices[i + 1]), CONV(vertices[i]), CONV(color));
    }
}

void b2Draw_raylib::DrawCircle(b2Vec2 const& center, float radius, b2Color const& color) noexcept
{
    DrawCircleLinesV(CONV(center), CONV(radius), CONV(color));
}

void b2Draw_raylib::DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& /* axis */, b2Color const& color) noexcept
{
    DrawCircleV(CONV(center), CONV(radius), CONV(color));
}

void b2Draw_raylib::DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color) noexcept
{
    DrawLineV(CONV(p1), CONV(p2), CONV(color));
}

void b2Draw_raylib::DrawTransform(b2Transform const& xf) noexcept
{
    DrawSegment(xf.p, xf.p + 1.0f * xf.q.GetXAxis(), b2Color{ 1.0f, 0.0f, 0.0f });
    DrawSegment(xf.p, xf.p + 1.0f * xf.q.GetYAxis(), b2Color{ 0.0f, 1.0f, 0.0f });
}

void b2Draw_raylib::DrawPoint(b2Vec2 const& p, float size, b2Color const& color) noexcept
{
    DrawCircleV(CONV(p), size, CONV(color));
}

float b2Draw_raylib::M_Convert(float f) const noexcept
{
    return m_scale * f;
}

Vector2 b2Draw_raylib::M_Convert(b2Vec2 v) const noexcept
{
    return { m_scale * v.x, m_scale * v.y };
}

Color b2Draw_raylib::M_Convert(b2Color c) const noexcept
{
    return {
        static_cast<unsigned char>(c.r * 255.0f),
        static_cast<unsigned char>(c.g * 255.0f),
        static_cast<unsigned char>(c.b * 255.0f),
        255
    };
}
