#pragma once

// SFML
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// box2d
#include <box2d/b2_draw.h>

class b2Draw_SFML : public b2Draw
{
public:

    b2Draw_SFML();

    void SetRenderTarget(sf::RenderTarget& renderTarget) noexcept;

    sf::RenderTarget const& GetRenderTarget() const noexcept;

    void SetRenderStates(sf::RenderStates const& renderStates) noexcept;

    sf::RenderStates const& GetRenderStates() const noexcept;

    void ToggleFlags(uint32 flags) noexcept;

    void SetScale(float scale) noexcept;

    float GetScale() const noexcept;

protected:

    void DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color);

    void DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color);

    void DrawCircle(b2Vec2 const& center, float radius, b2Color const& color);

    void DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& axis, b2Color const& color);

    void DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color);

    void DrawTransform(b2Transform const& xf);

    void DrawPoint(b2Vec2 const& p, float size, b2Color const& color);

private:

    float M_Convert(float f) const noexcept;

    sf::Vector2f M_Convert(b2Vec2 v) const noexcept;

    sf::Color M_Convert(b2Color c) const noexcept;

    sf::RenderTarget* m_renderTarget;
    sf::RenderStates m_renderStates;
    sf::ConvexShape m_convexShape;
    sf::CircleShape m_circleShape;
    float m_scale;
};
