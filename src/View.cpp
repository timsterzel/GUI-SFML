#include "View.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::View::View()
: m_width{ 0.f }
, m_height{ 0.f }
, m_bgColor{ sf::Color::Transparent }
, m_parent{ nullptr }
{

}

gsf::View::~View()
{

}

void gsf::View::attachChild(Ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

gsf::View::Ptr gsf::View::detachChild(const View& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (Ptr &p) -> bool { return p.get() == &node; });
    // There is an error when we try to detach a child which does not exists,so stop execution in debug mode
    assert(found != m_children.end());

    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

void gsf::View::setWidth(const float width)
{
    m_width = width;
}

float gsf::View::getWidth() const
{
    return m_width;
}

void gsf::View::setHeight(const float height)
{
    m_height = height;
}

float gsf::View::getHeight() const
{
    return m_height;
}

void gsf::View::setBackgroundColor(const sf::Color color)
{
    m_bgColor = color;
}

sf::Color gsf::View::getBackgroundColor() const
{
    return m_bgColor;
}

void gsf::View::centerOrigin()
{
    setOrigin(getWidth() / 2.f, getHeight() / 2.f);
}

void gsf::View::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
        states.transform *= getTransform();
        drawCurrent(target, states);
        drawChildren(target, states);
}

void gsf::View::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Do nothing by default
}

void gsf::View::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const Ptr &child : m_children)
    {
        child->draw(target, states);
    }
}

void gsf::View::update(float dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void gsf::View::updateCurrent(float dt)
{
    // Do nothing by default
}

void gsf::View::updateChildren(float dt)
{
    for (const Ptr &child : m_children)
    {
        child->update(dt);
    }
}

sf::Transform gsf::View::getWorldTransform() const
{
    sf::Transform trform = { sf::Transform::Identity };
    for (const View *node = this; node != nullptr; node = node->m_parent)
    {
        trform = node->getTransform() * trform;
    }
    return trform;
}

sf::Vector2f gsf::View::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void gsf::View::calculateSize()
{
    // Do nothing by default
}
