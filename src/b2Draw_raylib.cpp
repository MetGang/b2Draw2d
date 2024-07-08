#include "b2Draw_raylib.hpp"

Color Convert(b2Color c) noexcept
{
    return {
        static_cast<unsigned char>(c.r * 255.0f),
        static_cast<unsigned char>(c.g * 255.0f),
        static_cast<unsigned char>(c.b * 255.0f),
        255
    };
}

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
        DrawLineV(M_Convert(vertices[i]), M_Convert(vertices[i + 1]), Convert(color));
    }
    DrawLineV(M_Convert(vertices[vertexCount - 1]), M_Convert(vertices[0]), Convert(color));
}

void b2Draw_raylib::DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept
{
    b2Color const fillColor = { 0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f };

    for (int i = 1; i < vertexCount - 1; ++i)
    {
        DrawTriangle(M_Convert(vertices[0]), M_Convert(vertices[i + 1]), M_Convert(vertices[i]), Convert(fillColor));
    }

    DrawPolygon(vertices, vertexCount, color);
}

void b2Draw_raylib::DrawCircle(b2Vec2 const& center, float radius, b2Color const& color) noexcept
{
    DrawCircleLinesV(M_Convert(center), M_Convert(radius), Convert(color));
}

void b2Draw_raylib::DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& axis, b2Color const& color) noexcept
{
    b2Color const fillColor = { 0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f };

    DrawCircleV(M_Convert(center), M_Convert(radius), Convert(fillColor));

    DrawCircle(center, radius, color);

    DrawSegment(center, center + radius * axis, color);
}

void b2Draw_raylib::DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color) noexcept
{
    DrawLineV(M_Convert(p1), M_Convert(p2), Convert(color));
}

void b2Draw_raylib::DrawTransform(b2Transform const& xf) noexcept
{
    DrawLineV(M_Convert(xf.p), M_Convert(xf.p + xf.q.GetXAxis()), RED);
    DrawLineV(M_Convert(xf.p), M_Convert(xf.p + xf.q.GetYAxis()), GREEN);
}

void b2Draw_raylib::DrawPoint(b2Vec2 const& p, float size, b2Color const& color) noexcept
{
    DrawCircleV(M_Convert(p), size, Convert(color));
}

float b2Draw_raylib::M_Convert(float f) const noexcept
{
    return m_scale * f;
}

Vector2 b2Draw_raylib::M_Convert(b2Vec2 v) const noexcept
{
    return { m_scale * v.x, m_scale * v.y };
}
