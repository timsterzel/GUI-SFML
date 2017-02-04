#include "Widget.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::Widget::Widget()
: m_width{ 0.f }
, m_height{ 0.f }
, m_outlineColor{ sf::Color::Transparent }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::Transparent }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
{

}


gsf::Widget::Widget(float width, float height)
: m_width{ width }
, m_height{ height }
, m_outlineColor{ sf::Color::Transparent }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::Transparent }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
{

}

gsf::Widget::~Widget()
{

}

sf::Color gsf::Widget::getOutlineColor() const
{
    return m_outlineColor;
}

void gsf::Widget::setOutlineColor(sf::Color color)
{
    m_outlineColor = color;
}

float gsf::Widget::getOutlineThickness() const
{
    return m_outlineThickness;
}

void gsf::Widget::setOutlineThickness(float outline)
{
    m_outlineThickness = outline;
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

void gsf::Widget::setIsRemoveable(bool isRemoveable)
{
    m_isRemoveable = isRemoveable;
}

bool gsf::Widget::isRemoveable() const
{
    return m_isRemoveable;
}

void gsf::Widget::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

bool gsf::Widget::isVisible() const
{
    return m_isVisible;
}

void gsf::Widget::setOnLeftClickListener(std::function
        <void(Widget *widget, sf::Vector2f)> listener)
{
    m_onLeftClickListener = listener;
}

void gsf::Widget::setOnRightClickListener(std::function
        <void(Widget *widget, sf::Vector2f)> listener)
{
    m_onRightClickListener = listener;
}

void gsf::Widget::setOnMiddleClickListener(std::function
        <void(Widget *widget, sf::Vector2f)> listener)
{
    m_onMiddleClickListener = listener;
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
        states.transform *= getTransform();
        // Draw basic shape (background and outline)
        sf::RectangleShape basicShape{ sf::Vector2f(m_width, m_height) };
        basicShape.setFillColor(m_bgColor);
        basicShape.setOutlineThickness(m_outlineThickness);
        basicShape.setOutlineColor(m_outlineColor);
        target.draw(basicShape, states);

        // Set the targets to the view which is only the area of the widget, 
        // based on its with, height and position
        sf::View defaultView{ target.getView() };
        sf::View view{ getShownAreaView(target) };
        target.setView(view);

        drawWidget(target, states);
        target.setView(defaultView);
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
    // Is the mouse in the shown area of the widget
    sf::Vector2f mousePos{ (float) event.mouseButton.x , (float) event.mouseButton.y };
    bool isMouseInShownArea{ getShownArea().contains(mousePos) };
    bool intersecting{ isIntersecting(mousePos) };
    if (isMouseInShownArea)
    {
        if (event.type == sf::Event::MouseButtonPressed && intersecting)
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left: 
                    if (m_onLeftClickListener) 
                    { 
                        m_onLeftClickListener(this, mousePos);
                        return true;
                    }
                    break;
                case sf::Mouse::Right: 
                    if (m_onRightClickListener)
                    {
                        m_onRightClickListener(this, mousePos); 
                        return true;
                    }
                    break;
                case sf::Mouse::Middle:
                    if (m_onMiddleClickListener)
                    {
                        m_onMiddleClickListener(this, mousePos);
                        return true;
                    }
                    break;
                default: break;
            }
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
    sf::Transform trform{ sf::Transform::Identity };
    for (const Widget *node{ this }; node != nullptr; node = node->m_parent)
    {
        trform = node->getTransform() * trform;
    }
    return trform;
}

sf::Vector2f gsf::Widget::getWorldPosition() const
{
    // Get world position ignores the real position when the origin is set 
    // (the position is every time the one in the upper left corner)
    // so we add the origin here.
    return (getWorldTransform() * sf::Vector2f()) + getOrigin();
}

sf::View gsf::Widget::getShownAreaView(sf::RenderTarget &target) const
{
    sf::FloatRect shownAreaRect{ getShownArea() };
    float left{ shownAreaRect.left };
    float top{ shownAreaRect.top };
    float width{ shownAreaRect.width };
    float height{ shownAreaRect.height };

    sf::View view;
    // The view should have the same size as the widgets shown area,
    // so the shown area of the widget is never bigger than the size of the widget,
    // although when containing widgets of the widget are bigger.
    view.setSize(width , height);

    view.setCenter(left + (width / 2.f), top + (height / 2.f) );

    // The viewport is the area where the widget is on screen
    view.setViewport(sf::FloatRect(left / target.getSize().x , top / target.getSize().y,
                width / target.getSize().x, height / target.getSize().y));
    return view;
}

sf::FloatRect gsf::Widget::getShownArea() const
{
    sf::FloatRect rectThis{ getWorldLeft(), getWorldTop(), getWidth(), getHeight() };

    if (m_parent)
    {
         // We have to get the parents shown screen area to calculate 
         // the overlapping rect
        sf::FloatRect rectParent{ m_parent->getShownArea() };

        // Data of this widget
        float leftA{ rectThis.left };
        float rightA{ rectThis.left + rectThis.width };
        float topA{ rectThis.top };
        float bottomA{ rectThis.top + rectThis.height };
        // Data of parent widgets shown area
        float leftB{ rectParent.left };
        float rightB{ rectParent.left + rectParent.width };
        float topB{ rectParent.top };
        float bottomB{ rectParent.top + rectParent.height };

        // Calculate where the shown area starts. 
        // (The startpoint should be right of the left side of its parent and
        // under the top side of its parent. Is the startpoint right of the right 
        // side of its parent or
        // under the bottom side of its parent the overlapping area is zero.
        float leftAB{ std::max(leftA, leftB) };
        float topAB{ std::max(topA, topB) };
        // The shown size should only have the size of the area of the widget 
        // which is on the parent widget
        // For this we need the intersecting area of the this widget with its parent
        float overlapX{ std::max(0.f, std::min(rightA, rightB) 
                - std::max(leftA, leftB)) };
        float overlapY{ std::max(0.f, std::min(bottomA, bottomB) 
                - std::max(topA, topB)) };
        return sf::FloatRect{ leftAB, topAB, overlapX, overlapY };
    }
    return rectThis;
}

bool gsf::Widget::isIntersecting(sf::Vector2f pos) const
{
    return pos.x >= getWorldLeft() && pos.x <= getWorldRight() && 
        pos.y >= getWorldTop() && pos.y <= getWorldBottom();
}

void gsf::Widget::calculateSize()
{
    // Do nothing by default
}
