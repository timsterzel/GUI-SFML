#include "ScrollableWidget.hpp"
#include <iostream>

const float gsf::ScrollableWidget::SCROLLBAR_THICKNESS{ 16.f };

gsf::ScrollableWidget::Ptr gsf::ScrollableWidget::create()
{
    Ptr widget{ std::make_unique<ScrollableWidget>() };
    return std::move(widget);
}

gsf::ScrollableWidget::Ptr gsf::ScrollableWidget::create(float width, float height)
{
    Ptr widget{ std::make_unique<ScrollableWidget>(width, height) };
    return std::move(widget);
}

gsf::ScrollableWidget::ScrollableWidget()
: Widget{  }
, m_childWidget{ nullptr }
, m_scrollSpeed{ 16.0f }
, m_scrollBarColor{ sf::Color::Black }
, m_scrollBtnColor{ sf::Color{ 192, 192, 192 } }
, m_scrollBtnSymbolColor{ sf::Color::Black }
, m_isVerticalScrollEnabled{ true }
, m_isHorizontalScrollEnabled{ true }
, m_scrollbarThickness{ SCROLLBAR_THICKNESS }
, m_isVerticalScrollNeeded{ true }
, m_scrollbarVertical{ m_scrollbarThickness, 0.f }
, m_scrollbarVerMoveActive{ false }
, m_isHorizontalScrollNeeded{ true }
, m_scrollbarHorizontal{ 0.f, m_scrollbarThickness }
, m_scrollbarHorMoveActive{ false }
, m_isVerticalScrollbarDrawn{ true }
, m_isHorizontalScrollbarDrawn{ true }
{
    init();
}
gsf::ScrollableWidget::ScrollableWidget(float width, float height)
: Widget{ width, height }
, m_childWidget{ nullptr }
, m_scrollSpeed{ 16.0f }
, m_scrollBarColor{ sf::Color::Black }
, m_scrollBtnColor{ sf::Color{ 192, 192, 192 } }
, m_scrollBtnSymbolColor{ sf::Color::Black }
, m_isVerticalScrollEnabled{ true }
, m_isHorizontalScrollEnabled{ true }
, m_scrollbarThickness{ SCROLLBAR_THICKNESS }
, m_isVerticalScrollNeeded{ true }
, m_scrollbarVertical{ m_scrollbarThickness, 0.f }
, m_scrollbarVerMoveActive{ false }
, m_isHorizontalScrollNeeded{ true }
, m_scrollbarHorizontal{ 0.f, m_scrollbarThickness }
, m_scrollbarHorMoveActive{ false }
, m_isVerticalScrollbarDrawn{ true }
, m_isHorizontalScrollbarDrawn{ true }
{
    init();
}

void gsf::ScrollableWidget::init()
{
    boundsChanged();
}


void gsf::ScrollableWidget::createScrollbars()
{
    // _____________________
    // | CONTENT          |^|<- Button to Scroll up
    // |                  | |
    // |                  |S|
    // |                  |S| <- Vertical Scrollbar
    // |__________________|v|
    // <               SSS>x| <- 'x' is a buffer area where is nothing
    // ----------------------
    //                   ^
    //                   | Horizontal Scrollbar
    if (!m_childWidget)
    {
        return;
    }
    // Store actual state of the scrollNeeded members so we can later check if there
    // has changed
    bool isVerticalScrollNeededOld{ m_isVerticalScrollNeeded };
    bool isHorizontalScrollNeededOld{ m_isHorizontalScrollNeeded };
    createVerticalScrollbar();
    createHorizontalScrollbar();
    // Call listeners when scrollNeeded members have changed
    if (m_onVerticalScrollNeededChangedListener && 
            isVerticalScrollNeededOld != m_isVerticalScrollNeeded)
    {
        m_onVerticalScrollNeededChangedListener(this, m_isVerticalScrollNeeded);
    }
    if (m_onHorizontalScrollNeededChangedListener && 
            isHorizontalScrollNeededOld != m_isHorizontalScrollNeeded)
    {
        m_onHorizontalScrollNeededChangedListener(this, m_isHorizontalScrollNeeded);
    }
}

// To Do: Use the real bounds with the outline thickness of the child
void gsf::ScrollableWidget::createVerticalScrollbar()
{
    // Its important to use localBound, because there is the outlineThickiss in
    float childHeight{ m_childWidget->getLocalBounds().height };

    // Check if there is any need for scrolling 
    // (Child is higher then ScrollableWidgets height or outside)
    m_isVerticalScrollNeeded = m_childWidget->getRealTop() < 0.f || 
        m_childWidget->getRealBottom() > getHeight() ||
        childHeight > getHeight();
    // Only show scrollbar when there is any need to scroll and scrolling is enabled
    if (!m_isVerticalScrollEnabled || !m_isVerticalScrollNeeded) {
        m_scrollbarVertical.setHeight(0.f);
        return;
    }
    // Add vertical scroll thickness to full area
    m_fullArea.width += m_scrollbarThickness;
    // Create Buttons
    m_scrollUpBtn.setSize(m_scrollbarThickness, m_scrollbarThickness);
    // Set position x direct after the content area and y to top
    m_scrollUpBtn.setPosition(getWidth(), 0.f);
    m_scrollUpBtn.setFillColor(m_scrollBtnColor);
    // Create symbol
    m_scrollUpBtnSymbol = createBtnSymbol(sf::Vector2f{ 
            getWidth() + m_scrollbarThickness / 2.f, m_scrollbarThickness / 2.f });
    
    m_scrollDownBtn.setSize(m_scrollbarThickness, m_scrollbarThickness);
    // Set position x direct after the content area and y to top
    m_scrollDownBtn.setPosition(getWidth(), getHeight() - m_scrollbarThickness);
    m_scrollDownBtn.setFillColor(m_scrollBtnColor);
    // Create symbol
    m_scrollDownBtnSymbol = createBtnSymbol(sf::Vector2f{ 
            getWidth() + m_scrollbarThickness / 2.f, 
            getHeight() - m_scrollbarThickness / 2.f }, 180.f);
    
    // Get proportion between the scrollable widget and its child 
    // (We need to note the scrollbar thickness so the
    // two scrollbars can not overlap)
    float scrollAreaHeight{ getHeight() 
        - m_scrollUpBtn.getHeight() - m_scrollDownBtn.getHeight() };
    float prop{ scrollAreaHeight / childHeight };
    // Calculate the scrollbar height
    float scrollbarHeight{ scrollAreaHeight * prop };
    m_scrollbarVertical.setHeight(scrollbarHeight);
    m_scrollbarVertical.setWidth(m_scrollbarThickness);
    m_scrollbarVertical.setPosition(getWidth(), m_scrollUpBtn.getHeight());
    m_scrollbarVertical.setFillColor(m_scrollBarColor);
}

void gsf::ScrollableWidget::createHorizontalScrollbar()
{
    float childWidth{ m_childWidget->getLocalBounds().width };

    // Horizontal Scrollbar
    m_isHorizontalScrollNeeded = m_childWidget->getRealLeft() < 0.f || 
        m_childWidget->getRealRight() > getWidth() ||
        childWidth > getWidth();
    // Only show scrollbar when there is any need to scroll and 
    // scrolling is enabled
    if (!m_isHorizontalScrollEnabled || !m_isHorizontalScrollNeeded) {
        m_scrollbarHorizontal.setWidth(0.f);
        return;
    }
    // Add vertical scroll thickness to full area
    m_fullArea.height += m_scrollbarThickness;
    // Create Buttons
    m_scrollLeftBtn.setSize(m_scrollbarThickness, m_scrollbarThickness);
    m_scrollLeftBtn.setPosition(0.f, getHeight());
    m_scrollLeftBtn.setFillColor(m_scrollBtnColor);
    m_scrollLeftBtnSymbol = createBtnSymbol(sf::Vector2f{ 
            m_scrollbarThickness / 2.f, getHeight() + m_scrollbarThickness / 2.f }, 
            -90.f);
    
    m_scrollRightBtn.setSize(m_scrollbarThickness, m_scrollbarThickness);
    m_scrollRightBtn.setPosition(getWidth() - m_scrollbarThickness, 
            getHeight());
    m_scrollRightBtn.setFillColor(m_scrollBtnColor);
    m_scrollRightBtnSymbol = createBtnSymbol(sf::Vector2f{ 
            getWidth() - m_scrollbarThickness / 2.f, 
            getHeight() + m_scrollbarThickness / 2.f }, 90.f);
    
    // Get proportion between the scrollable widget and its child 
    // (We need to note the scrollbar thickness so the
    // two scrollbars can not overlap)
    float scrollAreaWidth{ getWidth() 
        - m_scrollLeftBtn.getWidth() - m_scrollRightBtn.getWidth() };
    float prop{ scrollAreaWidth / childWidth };
    // Calculate the scrollbar height
    float scrollbarWidth{ scrollAreaWidth * prop };
    m_scrollbarHorizontal.setWidth(scrollbarWidth);
    m_scrollbarHorizontal.setHeight(m_scrollbarThickness);
    m_scrollbarHorizontal.setPosition(m_scrollLeftBtn.getRight(), 
            getHeight());
    m_scrollbarHorizontal.setFillColor(m_scrollBarColor);
}

sf::ConvexShape gsf::ScrollableWidget::createBtnSymbol(sf::Vector2f pos, 
        float rotation) const
{
    float symbolSize{ m_scrollbarThickness - 4.f };
    sf::ConvexShape shape{ 3 };
    shape.setPoint(0, sf::Vector2f{ symbolSize / 2.f, 0.f });
    shape.setPoint(1, sf::Vector2f{ symbolSize, symbolSize });
    shape.setPoint(2, sf::Vector2f{ 0.f, symbolSize });
    shape.setOrigin(shape.getGlobalBounds().width / 2.f,
            shape.getGlobalBounds().height / 2.f);
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(m_scrollBtnSymbolColor);
    shape.rotate(rotation);
    return shape;
}

void gsf::ScrollableWidget::attachChild(Widget::Ptr child)
{
    // Remove old widgets
    m_children.clear();
    child->setOrigin(0.f, 0.f);
    float childOutline{ child->getOutlineThickness() };
    child->setPosition(0.f + childOutline, 0.f + childOutline);
    m_childWidget = child.get();
    Widget::attachChild(std::move(child));
}

float gsf::ScrollableWidget::getScrollbarThickness() const
{
    return m_scrollbarThickness;
}

void gsf::ScrollableWidget::setScrollBarColor(sf::Color color)
{
    m_scrollBarColor = color;
    m_scrollbarVertical.setFillColor(m_scrollBarColor);
    m_scrollbarHorizontal.setFillColor(m_scrollBarColor);
}

sf::Color gsf::ScrollableWidget::getScrollBarColor() const
{
    return m_scrollBarColor;
}

void gsf::ScrollableWidget::setScrollBtnColor(sf::Color color)
{
    m_scrollBtnColor = color;
    m_scrollUpBtn.setFillColor(color);
    m_scrollDownBtn.setFillColor(color);
    m_scrollLeftBtn.setFillColor(color);
    m_scrollRightBtn.setFillColor(color);
}

sf::Color gsf::ScrollableWidget::getScrollBtnColor() const
{
    return m_scrollBtnColor;
}

void gsf::ScrollableWidget::setScrollBtnSymbolColor(sf::Color color)
{
    m_scrollBtnSymbolColor = color;
    m_scrollUpBtnSymbol.setFillColor(color);
    m_scrollDownBtnSymbol.setFillColor(color);
    m_scrollLeftBtnSymbol.setFillColor(color);
    m_scrollRightBtnSymbol.setFillColor(color);
}

sf::Color gsf::ScrollableWidget::getScrollBtnSymbolColor() const
{
    return m_scrollBtnSymbolColor;
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
void gsf::ScrollableWidget::setOnVerticalScrollNeededChangedListener(std::function
    <void(Widget*, bool)> listener)
{
    m_onVerticalScrollNeededChangedListener = listener;
}

void gsf::ScrollableWidget::setOnHorizontalScrollNeededChangedListener(std::function
    <void(Widget*, bool)> listener)
{
    m_onHorizontalScrollNeededChangedListener = listener;
}

void gsf::ScrollableWidget::recalculateScroll()
{
    //calculateScrollbarSizes();
    createScrollbars();
}

void gsf::ScrollableWidget::scrollToLeft()
{
    if (!m_isHorizontalScrollNeeded || !m_childWidget)
        return;
    m_childWidget->setPosition(getLeft(), m_childWidget->getPosition().y);
    adjustHorizontalScrollbarPosToChildWidgetPos();
}

void gsf::ScrollableWidget::scrollToRight()
{
    if (!m_isHorizontalScrollNeeded || !m_isHorizontalScrollEnabled
            || !m_childWidget)
        return;
    m_childWidget->setPosition(getRight() - m_childWidget->getWidth(), 
            m_childWidget->getPosition().y);
    adjustHorizontalScrollbarPosToChildWidgetPos();
}

void gsf::ScrollableWidget::scrollToTop()
{

    if (!m_isVerticalScrollNeeded || !m_isVerticalScrollEnabled 
            || !m_childWidget)
        return;
    m_childWidget->setPosition(m_childWidget->getPosition().x, 
            getTop());
    adjustVerticalScrollbarPosToChildWidgetPos();
}

void gsf::ScrollableWidget::scrollToBottom()
{
    if (!m_isVerticalScrollNeeded || !m_isVerticalScrollEnabled 
            || !m_childWidget)
        return;
    m_childWidget->setPosition(m_childWidget->getPosition().x, 
            getBottom() - m_childWidget->getHeight());
    adjustVerticalScrollbarPosToChildWidgetPos();
}

void gsf::ScrollableWidget::correctScrollBarPosition()
{
    // If scrollbar is out of widget, correct its position
    // Vertical
    if (m_scrollbarVertical.getTop() < m_scrollUpBtn.getBottom())
    {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, 
                m_scrollUpBtn.getBottom());
    }
    else if (m_scrollbarVertical.getBottom() > m_scrollDownBtn.getTop())
    {
        m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x, 
            m_scrollDownBtn.getTop() - m_scrollbarVertical.getHeight());
    }
    // Horizontal
    if (m_scrollbarHorizontal.getLeft() < m_scrollLeftBtn.getRight())
    {
        m_scrollbarHorizontal.setPosition(m_scrollLeftBtn.getRight(), 
                m_scrollbarHorizontal.getPosition().y);
    }
    else if (m_scrollbarHorizontal.getRight() > m_scrollRightBtn.getLeft())
    {
        m_scrollbarHorizontal.setPosition(m_scrollRightBtn.getLeft() 
                - m_scrollbarHorizontal.getWidth(),
                m_scrollbarHorizontal.getPosition().y);
    }
}

void gsf::ScrollableWidget::childAdded(Widget &child)
{
    createScrollbars();
}

void gsf::ScrollableWidget::childRemoved()
{
    m_childWidget = nullptr;
    createScrollbars();
}

void gsf::ScrollableWidget::boundsChanged()
{
    createScrollbars();
}

void gsf::ScrollableWidget::correctChildWidgetPosition()
{
    if (!m_childWidget)
    {
        return;
    }
    // Get child element
    Widget *child{ m_childWidget };
    // Correct the position of the childs when there are out of the bounds 
    // and scrolling is needed
    if (child->getRealBottom() <= getHeight() && m_isVerticalScrollNeeded)
    {
        child->setPosition(child->getPosition().x, 
                getHeight() - m_childWidget->getLocalBounds().height 
                + m_childWidget->getOutlineThickness());  
    }
    if (child->getRealTop() > 0.f && m_isVerticalScrollNeeded)
    {
        child->setPosition(child->getPosition().x, 0.f 
                + m_childWidget->getOutlineThickness());
    }
    if (child->getRealRight() <= getWidth() && m_isHorizontalScrollNeeded)
    {
        child->setPosition(getWidth() - m_childWidget->getLocalBounds().width
                + m_childWidget->getOutlineThickness(), 
                m_childWidget->getPosition().y);
    }
    if (child->getRealLeft() > 0.f && m_isHorizontalScrollNeeded)
    {
        child->setPosition(0.f + m_childWidget->getOutlineThickness(), 
                m_childWidget->getOutlineThickness());
    }
}

void gsf::ScrollableWidget::adjustVerticalScrollbarPosToChildWidgetPos()
{    
    if (!m_childWidget)
    {
        return;
    }
    // Get child element
    Widget *child{ m_childWidget };
    // The height which is moveable
    float scrollableAreaWidget{ child->getLocalBounds().height - getHeight() };
    float moved{ child->getRealTop() };
    float prop{ moved / scrollableAreaWidget };
    
    float scrollArea{ getHeight() 
        - m_scrollUpBtn.getHeight() - m_scrollDownBtn.getHeight() };
    float realScrollableArea{ scrollArea - m_scrollbarVertical.getHeight() };

    m_scrollbarVertical.setPosition(m_scrollbarVertical.getPosition().x,
            m_scrollUpBtn.getBottom() + (-realScrollableArea * prop));
}

void gsf::ScrollableWidget::adjustVerticalChildWidgetPosToScrollbarPos()
{
    if (!m_childWidget)
    {
        return;
    }

    // Get child element
    Widget *child{ m_childWidget };

    float scrollArea{ getHeight() 
        - m_scrollUpBtn.getHeight() - m_scrollDownBtn.getHeight() };
    float realScrollableArea{ scrollArea - m_scrollbarVertical.getHeight() };
    float moved{ m_scrollbarVertical.getTop() - m_scrollUpBtn.getBottom() };
    float prop{ moved / realScrollableArea };
    //float prop{ scrollableArea / moved };

    float scrollableAreaWidget{ child->getLocalBounds().height - getHeight() };
    child->setPosition(child->getPosition().x, -scrollableAreaWidget * prop 
            + m_childWidget->getOutlineThickness());
}
void gsf::ScrollableWidget::adjustHorizontalScrollbarPosToChildWidgetPos()
{    
    if (!m_childWidget)
    {
        return;
    }
    // Get child element
    Widget *child{ m_childWidget };
    // The height which is moveable
    float scrollableAreaWidget{ child->getLocalBounds().width - getWidth() };
    float moved{ child->getRealLeft() };
    float prop{ moved / scrollableAreaWidget };
    
    float scrollArea{ getWidth() 
        - m_scrollLeftBtn.getWidth() - m_scrollRightBtn.getWidth() };
    float realScrollableArea{ scrollArea - m_scrollbarHorizontal.getWidth() };

    m_scrollbarHorizontal.setPosition(m_scrollLeftBtn.getRight() 
            + (-realScrollableArea * prop),
            m_scrollbarHorizontal.getPosition().y);
}

void gsf::ScrollableWidget::adjustHorizontalChildWidgetPosToScrollbarPos()
{
    if (!m_childWidget)
    {
        return;
    }

    // Get child element
    Widget *child{ m_childWidget };

    float scrollArea{ getWidth() 
        - m_scrollLeftBtn.getWidth() - m_scrollRightBtn.getWidth() };
    float realScrollableArea{ scrollArea - m_scrollbarHorizontal.getWidth() };
    float moved{ m_scrollbarHorizontal.getLeft() - m_scrollLeftBtn.getRight() };
    float prop{ moved / realScrollableArea };

    float scrollableAreaWidget{ child->getLocalBounds().width - getWidth() };
    child->setPosition(-scrollableAreaWidget * prop 
            + m_childWidget->getOutlineThickness(), child->getPosition().y);
}


bool gsf::ScrollableWidget::handleEventCurrentBeforeChildren(sf::Event &event)
{
    // Is the mouse in the shown area of the widget
    bool isMouseInShownArea{ getShownArea().contains(
            sf::Vector2f{ (float) event.mouseButton.x, 
            (float) event.mouseButton.y }) };
    if (event.type == sf::Event::MouseWheelMoved && 
        isMouseInShownArea &&
        m_isVerticalScrollNeeded &&
        m_isVerticalScrollEnabled)
    {
        float scrollOffsetY{ event.mouseWheel.delta * m_scrollSpeed };
        // We have to move the scrollbar too when we scroll with the scroll wheel
        if (m_childWidget)
        {
            m_childWidget->move(0.f, scrollOffsetY);
            correctChildWidgetPosition();
            adjustVerticalScrollbarPosToChildWidgetPos();
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
        // Up Scroll Btn
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollUpBtn.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isVerticalScrollNeeded &&
            m_isVerticalScrollEnabled)
        {
            m_childWidget->move(0.f, m_scrollSpeed);
            correctChildWidgetPosition();
            adjustVerticalScrollbarPosToChildWidgetPos();
            return true;
        }
        // Down Scroll Btn
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollDownBtn.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isVerticalScrollNeeded &&
            m_isVerticalScrollEnabled)
        {
            m_childWidget->move(0.f, -m_scrollSpeed);
            correctChildWidgetPosition();
            adjustVerticalScrollbarPosToChildWidgetPos();
            return true;
        }
        // Left Scroll Btn
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollLeftBtn.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isHorizontalScrollNeeded &&
            m_isHorizontalScrollEnabled)
        {
            m_childWidget->move(m_scrollSpeed, 0.f);
            correctChildWidgetPosition();
            adjustHorizontalScrollbarPosToChildWidgetPos();
            return true;
        }
        // Right Scroll Btn
        if (event.mouseButton.button == sf::Mouse::Left &&
            m_scrollRightBtn.isPointIntersecting(
                { localMousePos.x , localMousePos.y }) &&
            m_isHorizontalScrollNeeded &&
            m_isHorizontalScrollEnabled)
        {
            m_childWidget->move(-m_scrollSpeed, 0.f);
            correctChildWidgetPosition();
            adjustHorizontalScrollbarPosToChildWidgetPos();
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
            adjustVerticalChildWidgetPosToScrollbarPos();
            return true;
        }
        if (m_scrollbarHorMoveActive)
        {

            // Move horizontal scollbar by mouse movement
            m_scrollbarHorizontal.setPositionAndStoreOld(localMousePos.x 
                    - m_scrollbarHorMoveModeRelPos.x, 
                    m_scrollbarHorizontal.getPosition().y);
            correctScrollBarPosition();
            adjustHorizontalChildWidgetPosToScrollbarPos();
            return true;
        }
    }
    return false;
}

bool gsf::ScrollableWidget::handleEventCurrentAfterChildren(sf::Event &event)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event) };
    return handled;
}

void gsf::ScrollableWidget::updateCurrentAfterChildren(float dt)
{

}

void gsf::ScrollableWidget::drawCurrentBeforeChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{        
    // Draw Scroll Elements
    if (m_isVerticalScrollbarDrawn && m_isVerticalScrollEnabled && 
            m_isVerticalScrollNeeded)
    {
        target.draw(m_scrollUpBtn, states);
        target.draw(m_scrollUpBtnSymbol, states);
        target.draw(m_scrollDownBtn, states);
        target.draw(m_scrollDownBtnSymbol, states);
        target.draw(m_scrollbarVertical, states);
    }
    if (m_isHorizontalScrollbarDrawn && m_isHorizontalScrollEnabled &&
            m_isHorizontalScrollNeeded)
    {
        target.draw(m_scrollLeftBtn, states);
        target.draw(m_scrollLeftBtnSymbol, states);
        target.draw(m_scrollRightBtn, states);
        target.draw(m_scrollRightBtnSymbol, states);
        target.draw(m_scrollbarHorizontal, states);
    }
}
void gsf::ScrollableWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{

}
