#include "ButtonWidget.hpp"
#include <iostream>

gsf::ButtonWidget::ButtonWidget(const sf::Font &font)
: Widget()
, m_font{ font }
, m_isHovering{ false }
, m_hoverFillColor{ sf::Color::Blue }
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}

gsf::ButtonWidget::ButtonWidget(float width, float height, const sf::Font &font)
: Widget(width, height)
, m_font{ font }
, m_isHovering{ false }
, m_hoverFillColor{ sf::Color::Blue }
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}
gsf::ButtonWidget::ButtonWidget(float width,float height, 
        const std::string &text, const sf::Font &font)
: Widget(width, height)
, m_font{ font }
, m_text{ text }
, m_isHovering{ false }
, m_hoverFillColor{ sf::Color::Blue }
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}

gsf::ButtonWidget::~ButtonWidget()
{

}


const std::string& gsf::ButtonWidget::getText() const
{
    return m_text;
}

void gsf::ButtonWidget::setText(const std::string& text)
{
    m_text = text;
}

sf::Color gsf::ButtonWidget::getHoverFillColor() const
{
    return m_hoverFillColor;
}

void gsf::ButtonWidget::setHoverFillColor(sf::Color color)
{
    m_hoverFillColor = color;
}

void gsf::ButtonWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw hover color as background color is button is in hover mode
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
    // Draw text
    sf::Text text{ m_text, m_font };
    sf::FloatRect rect{ text.getLocalBounds() };
    // sf::Text has non-zero values for widh and height so we dont may ignore them
    text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    text.setPosition(getWidth() / 2.f, getHeight() / 2.f);
    target.draw(text, states);
}

void gsf::ButtonWidget::update(float dt)
{
    // Do nothing by default
}

bool gsf::ButtonWidget::handleEvent(sf::Event &event)
{
    bool handled = Widget::handleEvent(event);
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
