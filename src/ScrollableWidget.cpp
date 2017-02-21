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
, m_isHorizontalScrollEnabled{ true }
, m_scrollbarThickness{ 16.f }
, m_isVerticalScrollNeeded{ true }
, m_scrollbarVertical{ m_scrollbarThickness, 0.f }
, m_scrollbarVerMoveActive{ false }
, m_isHorizontalScrollNeeded{ true }
, m_scrollbarHorizontal{ 0.f, m_scrollbarThickness }
, m_scrollbarHorMoveActive{ false }
, m_isVerticalScrollbarDrawn{ true }
, m_isHorizontalScrollbarDrawn{ true }
, SCROLLBAR_PAD{ 6.f }
, PAD_BETTWEEN_SCROLLBARS{ 6.f }
{
    calculateScrollbarSizes();
}

gsf::ScrollableWidget::~ScrollableWidget()
{

}

void gsf::ScrollableWidget::attachChild(Ptr child)
{
    // Remove old widgets
    m_children.clear();
    ChildWidget::attachChild(std::move(child));
}

void gsf::ScrollableWidget::calculateVerticalScrollbarSize()
{
    if (m_children.size() < 1)
    {
        return;
    }

    // Get first element
    Widget *childWidget{ m_children.at(0).get() };
    float childrenHeight{ childWidget->getHeight() };

    // Vertical Scrollbar
    // check if there is any need for scrolling 
    // (Child is higher then ScrollableWidgets height or outside)
    m_isVerticalScrollNeeded = childWidget->getTop() < 0.f || 
        childWidget->getBottom() > getHeight() ||
        childWidget->getHeight() > getHeight();
    // Only show scrollbar when there is any need to scroll and scrolling is enabled
    if (!m_isVerticalScrollEnabled || !m_isVerticalScrollNeeded) {
        m_scrollbarVertical.setHeight(0.f);
        return;
    }
    // Get proportion between the scrollable widget and its child 
    // (We need to note the scrollbar thickness so the
    // two scrollbars can not overlap
    float proportionVer{ (getHeight() - m_scrollbarThickness - PAD_BETTWEEN_SCROLLBARS
            /*- 2 * SCROLLBAR_PAD*/) / childrenHeight };
    // Calculate the scrollbar size
    float scrollbarHeight{ (getHeight() - m_scrollbarThickness - PAD_BETTWEEN_SCROLLBARS
            /*- 2 * SCROLLBAR_PAD*/) * proportionVer };
    m_scrollbarVertical.setHeight(scrollbarHeight);
    
    m_scrollbarVertical.setPosition(getWidth() - m_scrollbarVertical.getWidth() / 2.f 
            - SCROLLBAR_PAD, 0.f + m_scrollbarVertical.getHeight() / 2.f 
            + SCROLLBAR_PAD);
    
    m_scrollbarVertical.setOrigin(m_scrollbarVertical.getWidth() / 2.f, 
            m_scrollbarVertical.getHeight() / 2.f);
}

void gsf::ScrollableWidget::calculateHorizontalScrollbarSize()
{
        if (m_children.size() < 1)
        {
            return;
        }
        

        // get first element
        Widget *childWidget{ m_children.at(0).get() };
        float childrenWidth{ childWidget->getWidth() };

        // Horizontal Scrollbar
        m_isHorizontalScrollNeeded = childWidget->getLeft() < 0.f || 
            childWidget->getRight() > getWidth() ||
            childWidget->getWidth() > getWidth();
        // Only show scrollbar when there is any need to scroll and scrolling is enabled
        if (!m_isHorizontalScrollEnabled || !m_isHorizontalScrollNeeded) {
            m_scrollbarHorizontal.setWidth(0.f);
            return;
        }
        // Get proportion between the scrollable widget and its child 
        // (We need to note the scrollbar thickness so the 
        // two scrollbars can not overlap)
        float proportionHor{ (getWidth() - m_scrollbarThickness 
                - PAD_BETTWEEN_SCROLLBARS /*- 2 * SCROLLBAR_PAD*/) / childrenWidth };
        // Calculate the scrollbar size
        float scrollbarWidth{ (getWidth() - m_scrollbarThickness 
                - PAD_BETTWEEN_SCROLLBARS /*- 2 * SCROLLBAR_PAD*/) * proportionHor };
        m_scrollbarHorizontal.setWidth(scrollbarWidth);
        
        m_scrollbarHorizontal.setPosition(0.f + m_scrollbarHorizontal.getWidth() / 2.f 
                + SCROLLBAR_PAD, getHeight() - m_scrollbarHorizontal.getHeight() / 2.f 
                - SCROLLBAR_PAD);
        m_scrollbarHorizontal.setOrigin(m_scrollbarHorizontal.getWidth() / 2.f, 
                m_scrollbarHorizontal.getHeight() / 2.f);
}

void gsf::ScrollableWidget::calculateScrollbarSizes()
{
    if (m_children.size() < 1)
    {
        return;
    }
    calculateVerticalScrollbarSize();
    calculateHorizontalScrollbarSize();
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

void gsf::ScrollableWidget::setIsVerticalScrollbarDrawn(bool isDrawn)
{
    m_isVerticalScrollbarDrawn = isDrawn;
}

void gsf::ScrollableWidget::setIsHorizontalScrollbarDrawn(bool isDrawn)
{
    m_isHorizontalScrollbarDrawn = isDrawn;
}

float gsf::ScrollableWidget::getTotalWidth() const
{
    return m_totalWidth;
}

float gsf::ScrollableWidget::getTotalHeight() const
{
    return m_totalHeight;
}

void gsf::ScrollableWidget::recalculateScroll()
{
    calculateScrollbarSizes();
}

void gsf::ScrollableWidget::scrollToLeft()
{
    if (!m_isHorizontalScrollNeeded || m_children.size() < 1)
        return;
    Widget* child = m_children.at(0).get();
    m_scrollOffsetX = getLeft() - child->getLeft();
    // Move scrollbar by widgets width, because its always more then the scrollbar
    // can get, so the correctScrollBarPosition() method correct its postion then
    m_scrollbarHorizontal.move(-getWidth() , 0);
    correctScrollBarPosition();
    handleChildScroll();
}

void gsf::ScrollableWidget::scrollToRight()
{
    if (!m_isHorizontalScrollNeeded || !m_isHorizontalScrollEnabled
            || m_children.size() < 1)
        return;
    Widget* child = m_children.at(0).get();
    m_scrollOffsetX = -getRight() - child->getRight();
    // Move scrollbar by widgets width, because its always more then the scrollbar
    // can get, so the correctScrollBarPosition() method correct its postion then
    m_scrollbarHorizontal.move(getWidth() , 0);
    correctScrollBarPosition();
    handleChildScroll();
}

void gsf::ScrollableWidget::scrollToTop()
{

    if (!m_isVerticalScrollNeeded || !m_isVerticalScrollEnabled 
            || m_children.size() < 1)
        return;
    Widget* child = m_children.at(0).get();
    m_scrollOffsetY = getTop() - child->getTop();
    // Move scrollbar by widgets height, because its always more then the scrollbar
    // can get, so the correctScrollBarPosition() method correct its postion then
    m_scrollbarVertical.move(-0.f , -getHeight());
    correctScrollBarPosition();
    handleChildScroll();
}

void gsf::ScrollableWidget::scrollToBottom()
{
    if (!m_isVerticalScrollNeeded || !m_isVerticalScrollEnabled 
            || m_children.size() < 1)
        return;
    Widget* child = m_children.at(0).get();
    m_scrollOffsetY = -getBottom() - child->getBottom();
    // Move scrollbar by widgets height, because its always more then the scrollbar
    // can get, so the correctScrollBarPosition() method correct its postion then
    m_scrollbarVertical.move(0.f , getHeight());
    correctScrollBarPosition();
    handleChildScroll();
}

void gsf::ScrollableWidget::correctScrollBarPosition()
{
    // If scrollbar is out of widget, correct its position
    // Vertical
    if (m_scrollbarVertical.getTop() < 0.f + SCROLLBAR_PAD)
    {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, 
                0.f + m_scrollbarVertical.getHeight() / 2.f + SCROLLBAR_PAD);
    }
    else if (m_scrollbarVertical.getBottom() > getHeight() - SCROLLBAR_PAD 
            - m_scrollbarThickness - PAD_BETTWEEN_SCROLLBARS)
    {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, 
            getHeight() - m_scrollbarVertical.getHeight() / 2.f - m_scrollbarThickness
            - SCROLLBAR_PAD - PAD_BETTWEEN_SCROLLBARS);
    }
    // Horizontal
    if (m_scrollbarHorizontal.getLeft() < 0.f + SCROLLBAR_PAD)
    {
        m_scrollbarHorizontal.setPosition(0.f + m_scrollbarHorizontal.getWidth() / 2.f 
                + SCROLLBAR_PAD, m_scrollbarHorizontal.getPosition().y);
    }
    else if (m_scrollbarHorizontal.getRight() > getWidth() - SCROLLBAR_PAD 
            - m_scrollbarThickness - PAD_BETTWEEN_SCROLLBARS)
    {
        m_scrollbarHorizontal.setPosition(getWidth() - m_scrollbarHorizontal.getWidth() 
                / 2.f - m_scrollbarThickness - SCROLLBAR_PAD - PAD_BETTWEEN_SCROLLBARS,
                m_scrollbarHorizontal.getPosition().y);
    }
}

void gsf::ScrollableWidget::handleChildScroll()
{    
    Widget *child{ m_children.at(0).get() };
    
    child->move(m_scrollOffsetX, m_scrollOffsetY);
    // Correct the position of the childs when there are out of the bounds 
    // and scrolling is needed
    if (child->getBottom() <= getHeight() && m_isVerticalScrollNeeded)
    {
        child->move(0.f, getHeight() - child->getBottom() );
    }
    if (child->getTop() > 0.f && m_isVerticalScrollNeeded)
    {
        child->move(0.f, 0.f - child->getTop() );
    }
    if (child->getRight() <= getWidth() && m_isHorizontalScrollNeeded)
    {
        child->move(getWidth() - child->getRight(), 0.f);
    }
    if (child->getLeft() > 0.f && m_isHorizontalScrollNeeded)
    {
        child->move(0.f - child->getLeft(), 0.f);
    }
    // Scrolling handled
    m_scrollOffsetY = 0.f;
    m_scrollOffsetX = 0.f;
}

void gsf::ScrollableWidget::drawWidget(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
        drawCurrent(target, states);

        // We change the view of the target, 
        // so that only the area of the widget and its child
        // which are in its shown area are drawn on the RenderTarget
        sf::View defaultView{ target.getView() };
        sf::View view{ getShownAreaView(target) };

        target.setView(view);
        drawChildren(target, states);
        target.setView(defaultView);
        
        // Draw Scroll Elements
        if (m_isVerticalScrollbarDrawn)
        {
            target.draw(m_scrollbarVertical, states);
        }
        if (m_isHorizontalScrollbarDrawn)
        {
            target.draw(m_scrollbarHorizontal, states);
        }
}

void gsf::ScrollableWidget::drawCurrent(sf::RenderTarget &target, 
        sf::RenderStates states) const
{

}

bool gsf::ScrollableWidget::handleSpecialEvents(sf::Event &event)
{
    // Is the mouse in the shown area of the widget
    bool isMouseInShownArea{ getShownArea().contains(
            sf::Vector2f{ (float) event.mouseButton.x , (float) event.mouseButton.y }) };
    if (event.type == sf::Event::MouseWheelMoved && 
        isMouseInShownArea &&
        m_isVerticalScrollNeeded &&
        m_isVerticalScrollEnabled)
    {
        m_scrollOffsetY = event.mouseWheel.delta * m_scrollSpeed;
        // We have to move the scrollbar too when we scroll with the scroll wheel
        if (m_children.size() > 0)
        {
            // get first element
            Widget *widget{ m_children.at(0).get() };
            float childHeight{ widget->getHeight() };
            // Calculate the offset
            float moveScr{ -(m_scrollOffsetY * getHeight()) / childHeight };
            m_scrollbarVertical.moveAndStoreOldPos(0.f, moveScr);
            correctScrollBarPosition();
        }
        return true;
    }
    else if (event.type == sf::Event::MouseButtonPressed && isMouseInShownArea)
    {
        // We need the mouse pos as local position in the ScrollWidget
        sf::Vector2f localMousePos{ event.mouseButton.x - getWorldLeft(), 
            event.mouseButton.y - getWorldTop() };
        // Vertical scrollbar
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollbarVertical.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isVerticalScrollNeeded &&
            m_isVerticalScrollEnabled)
        {
            m_scrollbarVerMoveActive = true;
            m_scrollbarVerMoveModeRelPos.x = localMousePos.x 
                - m_scrollbarVertical.getPosition().x;
            m_scrollbarVerMoveModeRelPos.y = localMousePos.y 
                - m_scrollbarVertical.getPosition().y;
            return true;
        }
        // Horizontal scrollbar
        else if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollbarHorizontal.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isHorizontalScrollNeeded &&
            m_isHorizontalScrollEnabled)
        {
            m_scrollbarHorMoveActive = true;
            m_scrollbarHorMoveModeRelPos.x = localMousePos.x 
                - m_scrollbarHorizontal.getPosition().x;
            m_scrollbarHorMoveModeRelPos.y = localMousePos.y 
                - m_scrollbarHorizontal.getPosition().y;
            return true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_scrollbarVerMoveActive = false;
            m_scrollbarHorMoveActive = false;
            return true;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f localMousePos{ event.mouseMove.x - getWorldLeft(), 
            event.mouseMove.y - getWorldTop() };
        if (m_scrollbarVerMoveActive)
        {
            // Move vertical scollbar by mouse movement
            m_scrollbarVertical.setPositionAndStoreOld(
                    m_scrollbarVertical.getPosition().x, 
                    localMousePos.y - m_scrollbarVerMoveModeRelPos.y);
            correctScrollBarPosition();
            // Only ste a offset when there is a child to move
            if (m_children.size() > 0)
            {
                // get first element
                Widget *widget{ m_children.at(0).get() };
                float childrenHeight{ widget->getHeight() };
                // Calculate the offset
                m_scrollOffsetY = ( (m_scrollbarVertical.getLastPosition().y 
                        - m_scrollbarVertical.getPosition().y)
                        / (getHeight() - 2 * SCROLLBAR_PAD - m_scrollbarThickness) ) 
                        * childrenHeight;
                return true;
            }
        }
        if (m_scrollbarHorMoveActive)
        {
            // Move horizontal scollbar by mouse movement
            m_scrollbarHorizontal.setPositionAndStoreOld(localMousePos.x 
                    - m_scrollbarHorMoveModeRelPos.x, 
                    m_scrollbarHorizontal.getPosition().y);
            correctScrollBarPosition();
            // Only ste a offset when there is a child to move
            if (m_children.size() > 0)
            {
                // get first element
                Widget *widget{ m_children.at(0).get() };
                float childrenWidth{ widget->getWidth() };
                // Calculate the offset
                m_scrollOffsetX = ( (m_scrollbarHorizontal.getLastPosition().x 
                        - m_scrollbarHorizontal.getPosition().x) 
                        / (getWidth() - 2 * SCROLLBAR_PAD - m_scrollbarThickness) ) 
                        * childrenWidth;
                return true;
            }
        }
    }
    return false;
}

bool gsf::ScrollableWidget::handleEventCurrent(sf::Event &event)
{
    return false;
}
/*
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
*/
void gsf::ScrollableWidget::updateCurrent(float dt)
{
    handleChildScroll();
}

void gsf::ScrollableWidget::childAdded()
{
    calculateScrollbarSizes();
}

void gsf::ScrollableWidget::childRemoved()
{
    calculateScrollbarSizes();
}
