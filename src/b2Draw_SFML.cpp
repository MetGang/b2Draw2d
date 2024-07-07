#include "b2Draw_SFML.hpp"

b2Draw_SFML::b2Draw_SFML()
    : m_renderTarget { nullptr }
    , m_renderStates { sf::RenderStates::Default }
    , m_convexShape {}
    , m_circleShape {}
    , m_scale { 1.0f }
{

}

void b2Draw_SFML::SetRenderTarget(sf::RenderTarget& renderTarget) noexcept
{
    m_renderTarget = &renderTarget;
}

sf::RenderTarget const& b2Draw_SFML::GetRenderTarget() const noexcept
{
    return *m_renderTarget;
}

void b2Draw_SFML::SetRenderStates(sf::RenderStates const& renderStates) noexcept
{
    m_renderStates = renderStates;
}

sf::RenderStates const& b2Draw_SFML::GetRenderStates() const noexcept
{
    return m_renderStates;
}

void b2Draw_SFML::ToggleFlags(uint32 flags) noexcept
{
    SetFlags(GetFlags() ^ flags);
}

void b2Draw_SFML::SetScale(float scale) noexcept
{
    m_scale = scale;
}

float b2Draw_SFML::GetScale() const noexcept
{
    return m_scale;
}

void b2Draw_SFML::DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color)
{
    m_convexShape.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        m_convexShape.setPoint(i, M_Convert(vertices[i]));
    }

    m_convexShape.setFillColor(sf::Color::Transparent);
    m_convexShape.setOutlineColor(M_Convert(color));
    m_convexShape.setOutlineThickness(-1.0f);

    m_renderTarget->draw(m_convexShape, m_renderStates);
}

void b2Draw_SFML::DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color)
{
    m_convexShape.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        m_convexShape.setPoint(i, M_Convert(vertices[i]));
    }

    m_convexShape.setFillColor(M_Convert(color));
    m_convexShape.setOutlineColor(sf::Color::Transparent);
    m_convexShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_convexShape, m_renderStates);
}

void b2Draw_SFML::DrawCircle(b2Vec2 const& center, float radius, b2Color const& color)
{
    m_circleShape.setRadius(M_Convert(radius));
    m_circleShape.setPosition(M_Convert(center));
    m_circleShape.setOrigin(M_Convert({ radius, radius }));
    m_circleShape.setFillColor(sf::Color::Transparent);
    m_circleShape.setOutlineColor(M_Convert(color));
    m_circleShape.setOutlineThickness(-1.0f);

    m_renderTarget->draw(m_circleShape, m_renderStates);
}

void b2Draw_SFML::DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& /* axis */, b2Color const& color)
{
    m_circleShape.setRadius(M_Convert(radius));
    m_circleShape.setPosition(M_Convert(center));
    m_circleShape.setOrigin(M_Convert({ radius, radius }));
    m_circleShape.setFillColor(M_Convert(color));
    m_circleShape.setOutlineColor(sf::Color::Transparent);
    m_circleShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_circleShape, m_renderStates);
}

void b2Draw_SFML::DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color)
{
    sf::Vertex const line[] = { { M_Convert(p1), M_Convert(color) }, { M_Convert(p2), M_Convert(color) } };

    m_renderTarget->draw(line, 2u, sf::Lines, m_renderStates);
}

void b2Draw_SFML::DrawTransform(b2Transform const& xf)
{
    DrawSegment(xf.p, xf.p + 1.0f * xf.q.GetXAxis(), b2Color{ 1.0f, 0.0f, 0.0f });
    DrawSegment(xf.p, xf.p + 1.0f * xf.q.GetYAxis(), b2Color{ 0.0f, 1.0f, 0.0f });
}

void b2Draw_SFML::DrawPoint(b2Vec2 const& p, float size, b2Color const& color)
{
    m_circleShape.setRadius(size);
    m_circleShape.setPosition(M_Convert(p));
    m_circleShape.setOrigin({ size, size });
    m_circleShape.setFillColor(M_Convert(color));
    m_circleShape.setOutlineColor(sf::Color::Transparent);
    m_circleShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_circleShape, m_renderStates);
}

float b2Draw_SFML::M_Convert(float f) const noexcept
{
    return m_scale * f;
}

sf::Vector2f b2Draw_SFML::M_Convert(b2Vec2 v) const noexcept
{
    return { m_scale * v.x, m_scale * v.y };
}

sf::Color b2Draw_SFML::M_Convert(b2Color c) const noexcept
{
    return {
        static_cast<unsigned char>(c.r * 255.0f),
        static_cast<unsigned char>(c.g * 255.0f),
        static_cast<unsigned char>(c.b * 255.0f),
        255,
    };
}
