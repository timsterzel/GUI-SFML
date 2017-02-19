#include "ChildWidget.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::ChildWidget::ChildWidget()
: Widget()
{

}


gsf::ChildWidget::ChildWidget(float width, float height)
: Widget(width, height)
{

}

gsf::ChildWidget::~ChildWidget()
{

}

void gsf::ChildWidget::attachChild(Ptr child)
{
    child->setParent(this);
    m_children.push_back(std::move(child));

    childAdded();
    arrangeChildren();
    calculateSize();
}

gsf::Widget::Ptr gsf::ChildWidget::detachChild(const Widget& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), 
            [&] (Ptr &p) -> bool { return p.get() == &node; });
    // There is an error when we try to detach a child which does not exists, 
    // so stop execution in debug mode
    assert(found != m_children.end());

    Ptr result{ std::move(*found) };
    result->setParent(nullptr);
    m_children.erase(found);

    childRemoved();
    arrangeChildren();
    calculateSize();

    return result;
}

void gsf::ChildWidget::drawWidget(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
        drawCurrent(target, states);
        drawChildren(target, states);
        drawCurrentAfterChildren(target, states);
}

void gsf::ChildWidget::drawCurrent(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    // Do nothing by default
}

void gsf::ChildWidget::drawChildren(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    for (const Ptr &child : m_children)
    {
        child->draw(target, states);
    }
}

void gsf::ChildWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
    sf::RenderStates states) const
{
    // Do nothing by default
}
bool gsf::ChildWidget::handleSpecialEvents(sf::Event &event)
{
    return false;
}

bool gsf::ChildWidget::handleEvent(sf::Event &event)
{
    bool handled{ Widget::handleEvent(event) };
    // Special Events have the highest priorety, so handle them first
    if (handleSpecialEvents(event))
    {
        return true;
    }
    if (!handleEventChildren(event))
    {
        return handleEventCurrent(event);
    }
    return handled;
}

bool gsf::ChildWidget::handleEventChildren(sf::Event &event)
{
    for (const Ptr &child : m_children)
    {
        if (child->handleEventWidget(event))
        {
            return true;
        }
    }
    return false;
}

bool gsf::ChildWidget::handleEventCurrent(sf::Event &event)
{
    bool handled{ Widget::handleEvent(event) };
    return handled;
}

void gsf::ChildWidget::update(float dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void gsf::ChildWidget::updateCurrent(float dt)
{
    // Do nothing by default
}

void gsf::ChildWidget::updateChildren(float dt)
{
    for (const Ptr &child : m_children)
    {
        child->update(dt);
    }
}

void gsf::ChildWidget::calculateSize()
{
    // Do nothing by default
}

void gsf::ChildWidget::arrangeChildren()
{
    // Do nothing by default
}

void gsf::ChildWidget::childAdded()
{
    // Do nothing by default
}

void gsf::ChildWidget::childRemoved()
{
    // Do nothing by default
}
