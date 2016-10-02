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
    float height = 0.f;
    float width = 0.f;
    for (const Ptr &child : m_children)
    {
        height += child->getHeight();
        float childWidth = child->getWidth();
        if (childWidth > width)
        {
            width = childWidth;
        }
    }
    m_height = height;
    m_width = width;
}

void gsf::VerticalLayout::arrangeChildren()
{
    float distance = 0.f;
    for (const Ptr &child : m_children)
    {
        //child->centerOrigin();
        child->setPosition(0.f + child->getOrigin().x, distance + child->getOrigin().y);
        distance += child->getHeight();
    }
    calculateSize();
}
