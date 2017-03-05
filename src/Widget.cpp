#include "Widget.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

gsf::Widget::Ptr gsf::Widget::create(bool isWindowWidget)
{
    gsf::Widget::Ptr widget{ std::make_unique<gsf::Widget>(isWindowWidget) };
    return std::move(widget);
}

gsf::Widget::Ptr gsf::Widget::create(float width, float height, 
        bool isWindowWidget)
{
    gsf::Widget::Ptr widget{ std::make_unique<gsf::Widget>(width, height, 
            isWindowWidget) };
    return std::move(widget);
}

gsf::Widget::Widget(bool isWindowWidget)
//, m_width{ 0.f }
//, m_height{ 0.f }
: m_contentArea{ 0.f, 0.f, 0.f, 0.f }
, m_fullArea{ 0.f, 0.f, 0.f, 0.f }
, m_outlineColor{ sf::Color::Black }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::White }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
, m_isWindowWidget{ isWindowWidget }
{

}


gsf::Widget::Widget(float width, float height, bool isWindowWidget)
//, m_width{ width }
//, m_height{ height }
: m_contentArea{ 0.f, 0.f, width, height }
, m_fullArea{ 0.f, 0.f, width, height }
, m_outlineColor{ sf::Color::Black }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::White }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
, m_isWindowWidget{ isWindowWidget }
{

}

void gsf::Widget::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x, y);
}

void gsf::Widget::setPosition(const sf::Vector2f &position)
{
    sf::Transformable::setPosition(position);
}

const sf::Vector2f& gsf::Widget::getPosition() const
{
    return sf::Transformable::getPosition();
}

void gsf::Widget::setOrigin(float x, float y)
{
    sf::Transformable::setOrigin(x, y);
}

void gsf::Widget::setOrigin(const sf::Vector2f &origin)
{
    sf::Transformable::setOrigin(origin);
}

const sf::Vector2f& gsf::Widget::getOrigin() const
{
    return sf::Transformable::getOrigin();
}

void gsf::Widget::move(float offsetX, float offsetY)
{
    sf::Transformable::move(offsetX, offsetY);
}

void gsf::Widget::move(const sf::Vector2f &offset)
{
    sf::Transformable::move(offset);
}

void gsf::Widget::attachChild(Ptr child)
{    
    child->setParent(this);
    Widget &childRef{ *child.get() };
    m_children.push_back(std::move(child));
   
    childAdded(childRef);
    arrangeChildren();
    calculateSize();
}

gsf::Widget::Ptr gsf::Widget::detachChild(const Widget& node)
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
    boundsChanged();
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

bool gsf::Widget::isWindowWidget() const
{
    return m_isWindowWidget;
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
    m_contentArea.width = width;
    //m_width = width;
    boundsChanged();
}

float gsf::Widget::getWidth() const
{
    return m_contentArea.width;
    //return m_width;
}

void gsf::Widget::setHeight(const float height)
{
    m_contentArea.height = height;
    //m_height = height;
    boundsChanged();
}

float gsf::Widget::getHeight() const
{
    return m_contentArea.height;
    //return m_height;
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
    //return getWorldPosition().x - getOrigin().x + getWidth();
    return getWorldPosition().x - getOrigin().x + m_fullArea.width;
}

float gsf::Widget::getWorldTop() const
{
    return getWorldPosition().y - getOrigin().y;
}

float gsf::Widget::getWorldBottom() const
{
    //return getWorldPosition().y - getOrigin().y + getHeight();
    return getWorldPosition().y - getOrigin().y + m_fullArea.height;
}

float gsf::Widget::getRealLeft() const
{
    return getLocalBounds().left;
}

float gsf::Widget::getRealRight() const
{
    sf::FloatRect bounds{ getLocalBounds() };
    return bounds.left + bounds.width;
}

float gsf::Widget::getRealTop() const
{
    return getLocalBounds().top;
}

float gsf::Widget::getRealBottom() const
{
    sf::FloatRect bounds{ getLocalBounds() };
    return bounds.top + bounds.height;
}

float gsf::Widget::getWorldRealLeft() const
{
    return getGlobalBounds().left;
}

float gsf::Widget::getWorldRealRight() const
{
    sf::FloatRect bounds{ getGlobalBounds() };
    return bounds.left + bounds.width;
}

float gsf::Widget::getWorldRealTop() const
{
    return getGlobalBounds().top;
}

float gsf::Widget::getWorldRealBottom() const
{
    sf::FloatRect bounds{ getGlobalBounds() };
    return bounds.top + bounds.height;
}
sf::FloatRect gsf::Widget::getGlobalBounds() const
{
    /*
    sf::FloatRect rect{ getGlobalBoundsWithoutOutline() };
    rect.left -= m_outlineThickness;
    rect.top -= m_outlineThickness;
    rect.width += 2 * m_outlineThickness;
    rect.height += 2 * m_outlineThickness;
    return rect;
    */

    /*
    sf::FloatRect rect{ getLocalBounds() };
    rect.left += getWorldPosition().x;
    rect.top += getWorldPosition().y;
    return rect;
    */

    float left{ getWorldLeft() - m_outlineThickness };
    float top{ getWorldTop() - m_outlineThickness };
    float width{ m_fullArea.width + 2 * m_outlineThickness };
    float height{ m_fullArea.height + 2 * m_outlineThickness };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalBounds() const
{
    float left{ getLeft() - m_outlineThickness };
    float top{ getTop() - m_outlineThickness };
    float width{ m_fullArea.width + 2 * m_outlineThickness };
    float height{ m_fullArea.height + 2 * m_outlineThickness };
    return sf::FloatRect{ left, top, width, height };
}


sf::FloatRect gsf::Widget::getGlobalBoundsWithoutOutline() const
{
    float left{ getWorldLeft() };
    float top{ getWorldTop() };
    float width{ m_fullArea.width };
    float height{ m_fullArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalBoundsWithoutOutline() const
{
    float left{ getLeft() };
    float top{ getTop() };
    float width{ m_fullArea.width };
    float height{ m_fullArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getGlobalContentBounds() const
{
    float left{ m_contentArea.left + getWorldLeft() };
    float top{ m_contentArea.top + getWorldTop() };
    float width{ m_contentArea.width };
    float height{ m_contentArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalContentBounds() const
{
    float left{ m_contentArea.left };
    float top{ m_contentArea.top };
    float width{ m_contentArea.width };
    float height{ m_contentArea.height };
    return sf::FloatRect{ left, top, width, height };
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

sf::Vector2f gsf::Widget::convertToLocalPoint(sf::Vector2f globalPoint) const
{
    return sf::Vector2f{ globalPoint.x - getWorldPosition().x, 
        globalPoint.y - getWorldPosition().y };
}

sf::FloatRect gsf::Widget::getFullAreaRect() const
{
    return m_fullArea;
}

sf::FloatRect gsf::Widget::getOverlappingArea(sf::FloatRect rectThis, 
    sf::FloatRect rectParent) const
{
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

sf::View gsf::Widget::createViewFromRect(sf::FloatRect rect, 
        sf::RenderTarget &target, sf::View defaultView) const
{
    float left{ rect.left };
    float top{ rect.top };
    float width{ rect.width };
    float height{ rect.height };
    sf::View view;
    // The view should have the same size as the widgets shown area,
    // so the shown area of the widget is never bigger than the size of the widget,
    // although when containing widgets of the widget are bigger.
    view.setSize(width , height);

    view.setCenter(left + (width / 2.f), top + (height / 2.f) );
    
    // The viewport is the area where the widget is on screen    
    sf::Vector2f defaultViewSize{ defaultView.getSize() };
    view.setViewport(sf::FloatRect(left / defaultViewSize.x, 
                top / defaultViewSize.y,
                width / defaultViewSize.x, 
                height / defaultViewSize.y));
    
    /*
    view.setViewport(sf::FloatRect(left / target.getSize().x, 
                top / target.getSize().y,
                width / target.getSize().x, 
                height / target.getSize().y));
    */
    return view;
}

sf::FloatRect gsf::Widget::getShownArea() const
{
    //sf::FloatRect rectThis{ getGlobalBoundsWithoutOutline() };
    sf::FloatRect rectThis{ getGlobalBounds() };
    if (m_parent)
    {
         // We have to get the parents shown screen area to calculate 
         // the overlapping rect
        sf::FloatRect rectParent{ m_parent->getContentShownArea() };
        return getOverlappingArea(rectThis, rectParent);
    }
    return rectThis;
}

sf::FloatRect gsf::Widget::getContentShownArea() const
{
    sf::FloatRect rectThis{ getGlobalContentBounds() };
    if (m_parent)
    {
         // We have to get the parents shown screen area to calculate 
         // the overlapping rect
        sf::FloatRect rectParent{ m_parent->getContentShownArea() };
        return getOverlappingArea(rectThis, rectParent);
    }
    return rectThis;
}

sf::View gsf::Widget::getShownAreaView(sf::RenderTarget &target, sf::View defaultView) const
{
    sf::FloatRect shownAreaRect{ getShownArea() };
    return createViewFromRect(shownAreaRect, target,defaultView);
}
/*
sf::View gsf::Widget::getShownAreaViewWithoutOutline(sf::RenderTarget &target) const
{
    sf::FloatRect shownAreaRect{ getShownAreaWithoutOutline() };
    return createViewFromRect(shownAreaRect, target);
}
*/
sf::View gsf::Widget::getContentShownAreaView(sf::RenderTarget &target, 
        sf::View defaultView) const
{
    sf::FloatRect shownAreaRect{ getContentShownArea() };
    return createViewFromRect(shownAreaRect, target, defaultView);
}

void gsf::Widget::boundsChanged()
{
    m_fullArea.width = getWidth();
    m_fullArea.height = getHeight();
}

bool gsf::Widget::isIntersecting(sf::Vector2f pos) const
{
    return getGlobalBounds().contains(pos);
    //return pos.x >= getWorldLeft() && pos.x <= getWorldRight() && 
    //    pos.y >= getWorldTop() && pos.y <= getWorldBottom();
}

void gsf::Widget::calculateSize()
{
    // Do nothing by default
}

void gsf::Widget::arrangeChildren()
{
    // Do nothing by default
}

void gsf::Widget::childAdded(Widget &widget)
{
    // Do nothing by default
}

void gsf::Widget::childRemoved()
{
    // Do nothing by default
}
bool gsf::Widget::handleEvent(sf::Event &event, const sf::RenderTarget &target)
{
    bool handled{ false };
    if(!isVisible())
    {
        return false;
    }

    if (handleEventCurrentBeforeChildren(event, target))
    {
        return true;
    }
    if (!handleEventChildren(event, target))
    {
        return handleEventCurrentAfterChildren(event, target);
    }
    return handled;
}

bool gsf::Widget::handleEventCurrentBeforeChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    return false;
}

bool gsf::Widget::handleEventChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    for (const Ptr &child : m_children)
    {
        if (child->handleEvent(event, target))
        {
            return true;
        }
    }
    return false;
}

bool gsf::Widget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    // Is the mouse in the shown area of the widget
    sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseButton.x, 
            event.mouseButton.y }) };
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
    updateCurrentBeforeChildren(dt);
    updateChildren(dt);
    updateCurrentAfterChildren(dt);
}

void gsf::Widget::updateCurrentBeforeChildren(float dt)
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

void gsf::Widget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}
/*
void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing
}
*/
//void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states, 
        sf::View defaultView) const
{
    if (m_isVisible)
    {
        states.transform *= getTransform();
        // Draw basic shape (background and outline)
        sf::RectangleShape basicShape{ sf::Vector2f(m_fullArea.width, 
                m_fullArea.height) };
        basicShape.setFillColor(m_bgColor);
        basicShape.setOutlineThickness(m_outlineThickness);
        basicShape.setOutlineColor(m_outlineColor);
        target.draw(basicShape, states);

        // Set the target to the view which is only the area of the widget, 
        // based on its with, height and position
        sf::View oldView{ target.getView() };
        sf::View view{ getShownAreaView(target, defaultView) };
        target.setView(view);

        drawCurrentBeforeChildren(target, states, defaultView);
        drawChildren(target, states, defaultView);
        drawCurrentAfterChildren(target, states, defaultView);

        target.setView(oldView);
    }
}

void gsf::Widget::drawCurrentBeforeChildren(sf::RenderTarget &target, 
    sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}

void gsf::Widget::drawChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    // Children are only drawn in content view
    sf::View oldView{ target.getView() };
    sf::View view{ getContentShownAreaView(target, defaultView) };
    target.setView(view);
    for (const Ptr &child : m_children)
    {
        child->draw(target, states, defaultView);
    }
    target.setView(oldView);
}

void gsf::Widget::drawCurrentAfterChildren(sf::RenderTarget &target, 
    sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}
