#include "ButtonWidget.hpp"
#include <iostream>

gsf::ButtonWidget::ButtonWidget(const sf::Font &font)
: Widget()
, m_outlineColor{ sf::Color::White }
, m_outlineThickness{ 2.f }
, m_font{ font }  
{
    m_bgColor = sf::Color::Red;
}

gsf::ButtonWidget::ButtonWidget(float width, float height, const sf::Font &font)
: Widget(width, height)
, m_outlineColor{ sf::Color::White }
, m_outlineThickness{ 2.f }
, m_font{ font }
{
    m_bgColor = sf::Color::Red;
}
gsf::ButtonWidget::ButtonWidget(float width,float height, const std::string &text, const sf::Font &font)
: Widget(width, height)
, m_outlineColor{ sf::Color::White }
, m_outlineThickness{ 2.f }
, m_font{ font }
, m_text{ text }
{
    m_bgColor = sf::Color::Red;
}

gsf::ButtonWidget::~ButtonWidget()
{

}

sf::Color gsf::ButtonWidget::getOutlineColor() const
{
    return m_outlineColor;
}

void gsf::ButtonWidget::setOutlineColor(sf::Color color)
{
    m_outlineColor = color;
}

float gsf::ButtonWidget::getOutlineThickness() const
{
    return m_outlineThickness;
}

void gsf::ButtonWidget::setOutlineThickness(float outline)
{
    m_outlineThickness = outline;
}

const std::string& gsf::ButtonWidget::getText() const
{
    return m_text;
}

void gsf::ButtonWidget::setText(const std::string& text)
{
    m_text = text;
}

void gsf::ButtonWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // Draw background and outline
    sf::RectangleShape bgShape({ m_width, m_height });
    bgShape.setFillColor(m_bgColor);
    bgShape.setOutlineThickness(m_outlineThickness);
    bgShape.setOutlineColor(m_outlineColor);
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
    sf::Text text = { m_text, m_font };
    // Draw text
    text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
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
    return handled;
}
