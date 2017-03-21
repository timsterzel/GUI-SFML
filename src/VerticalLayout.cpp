#include "VerticalLayout.hpp"
#include <iostream>

gsf::VerticalLayout::Ptr gsf::VerticalLayout::create()
{
    Ptr widget{ std::make_unique<VerticalLayout>() };
    widget->applyTheme();
    return widget;
}

gsf::VerticalLayout::Ptr gsf::VerticalLayout::create(float width, float height)
{
    Ptr widget{ std::make_unique<VerticalLayout>(width, height) };
    widget->applyTheme();
    return widget;
}

gsf::VerticalLayout::VerticalLayout()
: Widget{  }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

gsf::VerticalLayout::VerticalLayout(float width, float height)
: Widget{ width, height }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

void gsf::VerticalLayout::init()
{
    loadAttributes("VerticalLayout");
}

void gsf::VerticalLayout::attachChild(Widget::Ptr child)
{
    Widget::attachChild(std::move(child));
}

gsf::Widget::Ptr gsf::VerticalLayout::detachChild(const Widget& node)
{
    return Widget::detachChild(node);
}

void gsf::VerticalLayout::enableAutoDetermineWidth()
{
    m_autoDetermineWidth = true;
}

void gsf::VerticalLayout::disableAutoDetermineWidth()
{
    m_autoDetermineWidth = false;
}

void gsf::VerticalLayout::enableAutoDetermineHeight()
{
    m_autoDetermineHeight = true;
}

void gsf::VerticalLayout::disableAutoDetermineHeight()
{
    m_autoDetermineHeight = false;
}

void gsf::VerticalLayout::calculateSize()
{
    if (!m_autoDetermineHeight && !m_autoDetermineWidth)
    {
        return;
    }
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
    if (m_autoDetermineHeight)
    {
        setHeight(height);
    }
    if (m_autoDetermineWidth)
    {
        setWidth(width);
    }   
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
