#include "Widget.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::Widget::Widget()
: m_width{ 0.f }
, m_height{ 0.f }
, m_bgColor{ sf::Color::Transparent }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_removeNext{ false }
, m_isVisible{ true }
{

}


gsf::Widget::Widget(float width, float height)
: m_width{ width }
, m_height{ height }
, m_bgColor{ sf::Color::Transparent }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_removeNext{ false }
, m_isVisible{ true }
{

}

gsf::Widget::~Widget()
{

}

void gsf::Widget::setParent(Widget *parent)
{
    m_parent = parent;
}

gsf::Widget* gsf::Widget::getParent() const
{
    return m_parent;
}

void gsf::Widget::setMoveToForground(bool moveToForeground)
{
    m_moveToForeground = moveToForeground;
}

bool gsf::Widget::isMarkedForMoveToForeground() const
{
    return m_moveToForeground;
}

void gsf::Widget::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

bool gsf::Widget::isVisible() const
{
    return m_isVisible;
}

void gsf::Widget::setOnLeftClickListener(std::function<void(Widget *widget, sf::Vector2f)> onLeftClickListener)
{
    m_onLeftClickListener = onLeftClickListener;
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

float gsf::Widget::getLeft() const
{
    return getPosition().x - getOrigin().x;
}

float gsf::Widget::getRight() const
{
    return getPosition().x - getOrigin().x + getWidth();
}

float gsf::Widget::getTop() const
{
    return getPosition().y - getOrigin().y;
}

float gsf::Widget::getBottom() const
{
    return getPosition().y - getOrigin().y + getHeight();
}

float gsf::Widget::getWorldLeft() const
{
    return getWorldPosition().x - getOrigin().x;
}

float gsf::Widget::getWorldRight() const
{
    return getWorldPosition().x - getOrigin().x + getWidth();
}

float gsf::Widget::getWorldTop() const
{
    return getWorldPosition().y - getOrigin().y;
}

float gsf::Widget::getWorldBottom() const
{
    return getWorldPosition().y - getOrigin().y + getHeight();
}

void gsf::Widget::setBackgroundColor(const sf::Color color)
{
    m_bgColor = color;
}

sf::Color gsf::Widget::getBackgroundColor() const
{
    return m_bgColor;
}

void gsf::Widget::centerOrigin()
{
    setOrigin(getWidth() / 2.f, getHeight() / 2.f);
}

void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (m_isVisible)
    {
        drawWidget(target, states);
    }
}

void gsf::Widget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing by default
}

bool gsf::Widget::handleEventWidget(sf::Event &event)
{
    if(!isVisible())
    {
        return false;
    }
    return handleEvent(event);
}

bool gsf::Widget::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && isIntersecting(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
            if (m_onLeftClickListener)
            {
                m_onLeftClickListener(this, sf::Vector2f(event.mouseButton.x , event.mouseButton.y));
            }
            return true;
        }
    }
    return false;
}

void gsf::Widget::update(float dt)
{
    // Do nothing by default
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
    // Get world position ignores the real position when the origin is set ( the position is every time the one in the upper left corner)
    // so we add the origin here.
    return ( getWorldTransform() * sf::Vector2f() ) + getOrigin();
}

bool gsf::Widget::isIntersecting(sf::Vector2f pos) const
{
    return pos.x >= getWorldLeft() && pos.x <= getWorldRight() && pos.y >= getWorldTop() && pos.y <= getWorldBottom();
}

void gsf::Widget::calculateSize()
{
    // Do nothing by default
}
