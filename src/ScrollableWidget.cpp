#include "ScrollableWidget.hpp"
#include <iostream>

gsf::ScrollableWidget::ScrollableWidget(float width, float height)
: ChildWidget(width, height)
, m_totalWidth{ width }
, m_totalHeight{ height }
, m_scrollOffsetX{ 0.f }
, m_scrollOffsetY{ 0.f }
, m_scrollSpeed{ 6.0f }
, m_isVerticalScrollEnabled{ true }
, m_isHorizontalScrollEnabled{ false }
, m_isVerticalScrollNeeded{ true }
, m_scrollbarVertical{ 30.f, 0.f }
, m_scrollbarMoveActive{ false }
, SCROLLBAR_PAD_HOR{ 6.f }
{
    //m_scrollbarVertical.setPosition(getRight() - m_scrollbarVertical.getWidth() / 2.f - 3.f, m_scrollbarVertical.getHeight() / 2.f + 3.f );
    calculateScrollbarSize();
}

gsf::ScrollableWidget::~ScrollableWidget()
{

}

void gsf::ScrollableWidget::calculateScrollbarSize()
{
    if (m_children.size() > 0)
    {
        // get first element
        Widget *childWidget = { m_children.at(0).get() };
        float childrenHeight = { childWidget->getHeight() };
        // Only show scrollbar when there is any need to scroll
        m_isVerticalScrollNeeded = childWidget->getTop() < 0.f || childWidget->getBottom() > getHeight() ||
            childWidget->getHeight() > getHeight();
        if (!m_isVerticalScrollNeeded) {
            std::cout << "smaller \n";
            return;
        }
        // Get proportion between the scrollable widget and its child
        float proportion = { getHeight() / childrenHeight };
        // Calculate the scrollbar size
        float scrollbarHeight = { (getHeight() - 2 * SCROLLBAR_PAD_HOR) * proportion };
        m_scrollbarVertical.setHeight(scrollbarHeight);
        m_scrollbarVertical.setPosition(getWidth() - m_scrollbarVertical.getWidth() / 2.f - 3.f, 0.f + m_scrollbarVertical.getHeight() / 2.f + SCROLLBAR_PAD_HOR);
        m_scrollbarVertical.setOrigin(m_scrollbarVertical.getWidth() / 2.f, m_scrollbarVertical.getHeight() / 2.f);
    }
}

void gsf::ScrollableWidget::setIsVerticalScrollEnabled(bool isEnabled)
{
    m_isVerticalScrollEnabled = isEnabled;
}

bool gsf::ScrollableWidget::isVerticalScrollEnabled() const
{
    return m_isVerticalScrollEnabled;
}
void gsf::ScrollableWidget::setIsHorizontalScrollEnabled(bool isEnabled)
{
    m_isHorizontalScrollEnabled = isEnabled;
}

bool gsf::ScrollableWidget::isHorizontalScrollEnabled() const
{
    return m_isHorizontalScrollEnabled;
}

float gsf::ScrollableWidget::getTotalWidth() const
{
    return m_totalWidth;
}

float gsf::ScrollableWidget::getTotalHeight() const
{
    return m_totalHeight;
}

void gsf::ScrollableWidget::correctScrollBarPosition()
{
    // If scrollbar is out of widget, correct its position
    if (m_scrollbarVertical.getTop() < 0.f + SCROLLBAR_PAD_HOR) {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, 0.f + m_scrollbarVertical.getHeight() / 2.f + SCROLLBAR_PAD_HOR);
    }
    else if (m_scrollbarVertical.getBottom() > getHeight() - SCROLLBAR_PAD_HOR) {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, getHeight() - m_scrollbarVertical.getHeight() / 2.f - SCROLLBAR_PAD_HOR);
    }
}

void gsf::ScrollableWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
        states.transform *= getTransform();

        drawCurrent(target, states);

        // We change the view of the target, so that only the area of the widget and its child
        // which are in its shown area are drawn on the RenderTarget
        sf::View defaultView = target.getView();
        sf::View view = { getShownAreaView(target) };
        //sf::View view = defaultView;

        target.setView(view);

        drawChildren(target, states);
        //Widget::draw(target, states);

        target.setView(defaultView);

        // Draw Scroll Elements
        target.draw(m_scrollbarVertical, states);
}

void gsf::ScrollableWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw background
    sf::RectangleShape bgShape({ getWidth(), getHeight() });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
}

bool gsf::ScrollableWidget::handleSpecialEvents(sf::Event &event)
{
    // Is the mouse in the shown area of the widget
    bool isMouseInShownArea = { getShownArea().contains(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)) };
    if (event.type == sf::Event::MouseWheelMoved &&
        isMouseInShownArea &&
        m_isVerticalScrollNeeded &&
        m_isVerticalScrollEnabled)
    {
        m_scrollOffsetY = { event.mouseWheel.delta * m_scrollSpeed };
        // We have to move the scrollbar too when we scroll with the scroll wheel
        if (m_children.size() > 0)
        {
            // get first element
            Widget *widget = m_children.at(0).get();
            float childHeight = widget->getHeight();
            // Calculate the offset
            float moveScr = -(m_scrollOffsetY * getHeight()) / childHeight;
            m_scrollbarVertical.moveAndStoreOldPos(0.f, moveScr);
            correctScrollBarPosition();
        }
        return true;
    }
    else if (event.type == sf::Event::MouseButtonPressed && isMouseInShownArea)
    {
        // We need the mouse pos as local position in the ScrollWidget
        sf::Vector2f localMousePos = { event.mouseButton.x - getWorldLeft() , event.mouseButton.y - getWorldTop() };
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollbarVertical.isPointIntersecting({ localMousePos.x , localMousePos.y }) &&
            m_isVerticalScrollNeeded &&
            m_isVerticalScrollEnabled)
        {
            m_scrollbarMoveActive = true;
            m_scrollbarMoveModeRelPos.x = localMousePos.x - m_scrollbarVertical.getPosition().x;
            m_scrollbarMoveModeRelPos.y = localMousePos.y - m_scrollbarVertical.getPosition().y;
            return true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_scrollbarMoveActive = false;
            return true;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (m_scrollbarMoveActive) {
            sf::Vector2f localMousePos = { event.mouseMove.x - getWorldLeft() , event.mouseMove.y - getWorldTop() };
            m_scrollbarVertical.setPositionAndStoreOld(m_scrollbarVertical.getPosition().x, localMousePos.y - m_scrollbarMoveModeRelPos.y);
            correctScrollBarPosition();
            // Only ste a offset when there is a child to move
            if (m_children.size() > 0)
            {
                // get first element
                Widget *widget = m_children.at(0).get();
                float childrenHeight = widget->getHeight();
                // Calculate the offset
                m_scrollOffsetY = ( (m_scrollbarVertical.getLastPosition().y - m_scrollbarVertical.getPosition().y) / (getHeight() - 2 * SCROLLBAR_PAD_HOR ) ) * childrenHeight;
                return true;
            }
        }

    }
    return false;
}
/*
bool gsf::ScrollableWidget::handleEvent(sf::Event &event)
{
    bool handled = Widget::handleEvent(event);
    if (!handleSpecialEvents(event) && !handleEventChildren(event))
    {
        return handleEventCurrent(event);
    }
    return handled;
}
*/
bool gsf::ScrollableWidget::handleEventCurrent(sf::Event &event)
{
    return false;
}

bool gsf::ScrollableWidget::handleEventChildren(sf::Event &event)
{
    // Only handle child Events if the event is in the are of the
    // shown area (Not the real area)
    if (!isIntersecting(sf::Vector2f(event.mouseButton.x , event.mouseButton.y))) {
        return false;
    }
    for (const Ptr &child : m_children)
    {
        if (child->handleEventWidget(event))
        {
            return true;
        }
    }
    return false;
}

void gsf::ScrollableWidget::updateCurrent(float dt)
{
    // Do to: a scrollwidgit should only have one child
    for (const Ptr &child : m_children)
    {
        child->move(0.f, m_scrollOffsetY);
        // Correct the position of the childs when there are out of the bounds and scrolling is needed
        if (child->getBottom() <= getHeight() && m_isVerticalScrollNeeded)
        {
            child->move(0.f, getHeight() - child->getBottom() );
        }
        else if (child->getTop() > 0.f && m_isVerticalScrollNeeded)
        {
            child->move(0.f, 0.f - child->getTop() );
        }
    }
    // Scrolling handled
    m_scrollOffsetY = 0.f;
}

void gsf::ScrollableWidget::childAdded()
{
    calculateScrollbarSize();
}

void gsf::ScrollableWidget::childRemoved()
{
    calculateScrollbarSize();
}
