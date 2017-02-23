#include "ButtonWidget.hpp"
#include <iostream>

gsf::ButtonWidget::ButtonWidget()
: Widget{  }
, m_isHovering{ false }
, m_hoverFillColor{ sf::Color::Black }
{
    init();
}

gsf::ButtonWidget::ButtonWidget(float width, float height)
: Widget(width, height)
, m_isHovering{ false }
, m_hoverFillColor{ sf::Color::Black }
{
    init();
}

void gsf::ButtonWidget::init()
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
}

sf::Color gsf::ButtonWidget::getHoverFillColor() const
{
    return m_hoverFillColor;
}

void gsf::ButtonWidget::setHoverFillColor(sf::Color color)
{
    m_hoverFillColor = color;
}

bool gsf::ButtonWidget::handleEventCurrentAfterChildren(sf::Event &event)
{
    bool handled = Widget::handleEventCurrentAfterChildren(event);
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos{ (float) event.mouseMove.x, (float) event.mouseMove.y };
        bool intersects{ isIntersecting(mousePos) };
        bool isInShownArea{ getShownArea().contains(mousePos) };
        if (intersects && isInShownArea)
        {
            m_isHovering = true;
        }
        else if (m_isHovering)
        {
            m_isHovering = false;
        }
    }
    return handled;
}

void gsf::ButtonWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ButtonWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw hover color as background color if button is in hover mode
    // To do (maybe): Let it handle from widget class. Instead of drawing the hover
    // background over the normal background, we can set the normal background to the
    // hover fill color. But it is necessary to store the normal color inside this
    // class so it can get restored after hovering ends
    if (m_isHovering)
    {
        sf::RectangleShape shape{ { getWidth(), getHeight() } };
        shape.setFillColor(m_hoverFillColor);
        target.draw(shape, states);
    }
}
