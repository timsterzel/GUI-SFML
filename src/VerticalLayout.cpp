#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::VerticalLayout()
: ChildWidget()
{

}

gsf::VerticalLayout::VerticalLayout(float width, float height)
: ChildWidget(width, height)
{

}

gsf::VerticalLayout::~VerticalLayout()
{

}


void gsf::VerticalLayout::drawCurrent(sf::RenderTarget &target, 
        sf::RenderStates states) const
{

}

void gsf::VerticalLayout::updateCurrent(float dt)
{
    // Do nothing by default
}

bool gsf::VerticalLayout::handleEventCurrent(sf::Event &event)
{
    bool handled{ ChildWidget::handleEventCurrent(event) };
    // Is the mouse in the shown area of the widget
    bool isMouseInShownArea{ getShownArea().contains(sf::Vector2f(event.mouseButton.x, 
                event.mouseButton.y)) };
    if (event.type == sf::Event::MouseButtonPressed && isMouseInShownArea)
    {
        if (event.mouseButton.button == sf::Mouse::Left && 
                isIntersecting(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
            return true;
        }
    }
    return handled;
}

void gsf::VerticalLayout::calculateSize()
{
    float height{ 0.f };
    float width{ 0.f };
    for (const Ptr &child : m_children)
    {
        height += child->getHeight();
        float childWidth{ child->getWidth() };
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
    float distance{ 0.f };
    for (const Ptr &child : m_children)
    {
        //child->centerOrigin();
        child->setPosition(0.f + child->getOrigin().x, distance + child->getOrigin().y);
        distance += child->getHeight();
    }
    calculateSize();
}
