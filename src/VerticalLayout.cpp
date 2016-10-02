#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::VerticalLayout()
{

}

gsf::VerticalLayout::~VerticalLayout()
{

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
