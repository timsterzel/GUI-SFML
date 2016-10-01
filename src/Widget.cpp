#include "Widget.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::Widget::Widget()
: m_width{ 0.f }
, m_height{ 0.f }
, m_parent{ nullptr }
{

}

gsf::Widget::~Widget()
{

}

void gsf::Widget::attachChild(Ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

gsf::Widget::Ptr gsf::Widget::detachChild(const Widget& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (Ptr &p) -> bool { return p.get() == &node; });
    // There is an error when we try to detach a child which does not exists,so stop execution in debug mode
    assert(found != m_children.end());

    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

void gsf::Widget::setWidth(const float width)
{
    m_width = width;
}

float gsf::Widget::getWidth() const
{
    return m_width;
}

void gsf::Widget::setHeight(const float height)
{
    m_height = height;
}

float gsf::Widget::getHeight() const
{
    return m_height;
}

void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
        states.transform *= getTransform();
        drawCurrent(target, states);
        drawChildren(target, states);
}

void gsf::Widget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Do nothing by default
}

void gsf::Widget::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const Ptr &child : m_children)
    {
        child->draw(target, states);
    }
}

void gsf::Widget::update(float dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void gsf::Widget::updateCurrent(float dt)
{
    // Do nothing by default
}

void gsf::Widget::updateChildren(float dt)
{
    for (const Ptr &child : m_children)
    {
        child->update(dt);
    }
}

sf::Transform gsf::Widget::getWorldTransform() const
{
    sf::Transform trform = { sf::Transform::Identity };
    for (const Widget *node = this; node != nullptr; node = node->m_parent)
    {
        trform = node->getTransform() * trform;
    }
    return trform;
}

sf::Vector2f gsf::Widget::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void gsf::Widget::calculateSize()
{
    // Do nothing by default
}
