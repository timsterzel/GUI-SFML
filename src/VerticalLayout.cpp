#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::Ptr gsf::VerticalLayout::create()
{
    Ptr widget{ std::make_unique<VerticalLayout>() };
    return widget;
}

gsf::VerticalLayout::Ptr gsf::VerticalLayout::create(float width, float height)
{
    Ptr widget{ std::make_unique<VerticalLayout>(width, height) };
    return widget;
}

gsf::VerticalLayout::VerticalLayout()
: Widget{  }
{

}

gsf::VerticalLayout::VerticalLayout(float width, float height)
: Widget{ width, height }
{

}

void gsf::VerticalLayout::attachChild(Widget::Ptr child)
{
    Widget::attachChild(std::move(child));
}

gsf::Widget::Ptr gsf::VerticalLayout::detachChild(const Widget& node)
{
    return Widget::detachChild(node);
}

void gsf::VerticalLayout::calculateSize()
{
    float height{ 0.f };
    float width{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        height += child->getLocalBounds().height;
        float childWidth{ child->getLocalBounds().width };
        if (childWidth > width)
        {
            width = childWidth;
        }
    }
    setHeight(height);
    setWidth(width);
}

void gsf::VerticalLayout::arrangeChildren()
{
    float distance{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        // Its important to add the outline thickness to the position so the whole
        // widget is visible
        child->setPosition(0.f + child->getOrigin().x + child->getOutlineThickness(), 
                distance + child->getOrigin().y + child->getOutlineThickness());
        distance += child->getLocalBounds().height;
    }
    calculateSize();
}

bool gsf::VerticalLayout::handleEventCurrentAfterChildren(sf::Event &event,
        const sf::RenderTarget &target)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event, target) };
    // Is the mouse in the shown area of the widget
    bool isMouseInShownArea{ getShownArea().contains(
            sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) };
    if (event.type == sf::Event::MouseButtonPressed && isMouseInShownArea)
    {
        if (event.mouseButton.button == sf::Mouse::Left && 
                isIntersecting(
                    sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
            return true;
        }
    }
    return handled;
}

void gsf::VerticalLayout::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::VerticalLayout::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}
