#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::VerticalLayout()
: m_bgColor{ sf::Color::Transparent }
{

}

gsf::VerticalLayout::~VerticalLayout()
{

}
/*
sf::Text& gsf::VerticalLayout::getText()
{
    return m_text;
}
*/

void gsf::VerticalLayout::setBackgroundColor(const sf::Color color)
{
    m_bgColor = color;
}

sf::Color gsf::VerticalLayout::getBackgroundColor() const
{
    return m_bgColor;
}

void gsf::VerticalLayout::centerOrigin()
{
    setOrigin(getWidth() / 2.f, getHeight() / 2.f);
}

void gsf::VerticalLayout::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw background
    sf::RectangleShape bgShape({ m_width, m_height });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
}

void gsf::VerticalLayout::updateCurrent(float dt)
{
    // Do nothing by default
}

void gsf::VerticalLayout::calculateSize()
{

}
