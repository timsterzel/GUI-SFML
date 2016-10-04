#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::VerticalLayout(float width, float height)
: View(width, height)
{

}

gsf::VerticalLayout::~VerticalLayout()
{

}

void gsf::VerticalLayout::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View defaultView = target.getView();
    sf::View view;
    view.setSize(getWidth(), getHeight());
    view.setCenter(getWorldPosition().x - getOrigin().x + (getWidth() / 2.f), getWorldPosition().y - getOrigin().y + (getHeight() / 2.f));

    float startX = ( getWorldPosition().x - getOrigin().x ) / target.getSize().x;
    float startY = ( getWorldPosition().y - getOrigin().y ) / target.getSize().y;
    float viewWidth = getWidth() / target.getSize().x;
    float viewHeight = getHeight() / target.getSize().y;
    sf::FloatRect viewport(startX , startY , viewWidth, viewHeight);
    view.setViewport(viewport);
    target.setView(view);
    // Draw background
    sf::RectangleShape bgShape({ getWidth(), getHeight() });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
    target.setView(defaultView);
}

void gsf::VerticalLayout::updateCurrent(float dt)
{
    // Do nothing by default
}

void gsf::VerticalLayout::calculateSize()
{
    /*
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
    */
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
