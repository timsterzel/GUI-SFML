#include "WindowWidget.hpp"
#include <iostream>

gsf::WindowWidget::WindowWidget()
: ChildWidget()
, m_topBarHeight{ 20.f }
, m_topBar{ 0.f, m_topBarHeight }
, m_btnClose{ m_topBarHeight - 6.f, m_topBarHeight - 6.f }
, m_moveModeActive{ false }
{
    init();
}

gsf::WindowWidget::WindowWidget(float width, float height)
: ChildWidget(width, height)
, m_topBarHeight{ 20.f }
, m_topBar{ width, m_topBarHeight }
, m_btnClose{ m_topBarHeight - 6.f, m_topBarHeight - 6.f }
, m_moveModeActive{ false }
{
    init();
}

void gsf::WindowWidget::init()
{
    // The Topbar is drawn over the real area of the widget
    // So the topbar dont hide child elements
    m_topBar.setOrigin(m_topBar.getWidth() / 2.f, m_topBar.getHeight() / 2.f);
    m_topBar.setPosition(m_topBar.getWidth() / 2.f, -m_topBar.getHeight() + m_topBar.getHeight() / 2.f );
    m_topBar.setFillColor(sf::Color::Magenta);
    m_btnClose.setOrigin(m_btnClose.getWidth() / 2.f, m_btnClose.getHeight() / 2.f);
    m_btnClose.setPosition(getWidth() - (m_btnClose.getWidth() / 2.f) - 3.f, -m_topBarHeight + (m_btnClose.getHeight() / 2.f) + 3.f);
    m_btnClose.setFillColor(sf::Color::White);
}

gsf::WindowWidget::~WindowWidget()
{

}

sf::Color gsf::WindowWidget::getTopbarFillColor() const
{
    return m_topBar.getFillColor();
}

void gsf::WindowWidget::setTopBarFillColor(const sf::Color color)
{
    m_topBar.setFillColor(color);
}

sf::Color gsf::WindowWidget::getCloseButtonFillColor() const
{
    return m_btnClose.getFillColor();
}

void gsf::WindowWidget::setCloseButtonFillColor(const sf::Color color)
{
    m_btnClose.setFillColor(color);
}

sf::View gsf::WindowWidget::getShownAreaView(sf::RenderTarget &target) const
{
        sf::View view;
        // The view should have the same size as the layout, so the shown area of the widget is never bigger than the size of the widget,
        // although when the children widgets of the layout are bigger.
        view.setSize(getWidth(), getHeight());
        /*
        float scrollOffsetX = m_scrollOffsetX;
        float scrollOffsetY = m_scrollOffsetY;
        view.setCenter(getWorldPosition().x - getOrigin().x + (getWidth() / 2.f) + scrollOffsetX, getWorldPosition().y - getOrigin().y + (getHeight() / 2.f) + scrollOffsetY );
        */
        view.setCenter(getWorldPosition().x - getOrigin().x + (getWidth() / 2.f), getWorldPosition().y - getOrigin().y + (getHeight() / 2.f) );

        float startX = ( getWorldPosition().x - getOrigin().x ) / target.getSize().x;
        float startY = ( getWorldPosition().y - getOrigin().y ) / target.getSize().y;
        float viewWidth = getWidth() / target.getSize().x;
        float viewHeight = getHeight() / target.getSize().y;
        // The viewport is the area where the widget is on screen
        view.setViewport(sf::FloatRect(startX , startY , viewWidth, viewHeight));
        return view;
}

void gsf::WindowWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
        states.transform *= getTransform();

        drawCurrent(target, states);

        // We change the view of the target, so that only the area of the widget and its child
        // which are in its shown area are drawn on the RenderTarget
        sf::View defaultView = target.getView();
        sf::View view = { getShownAreaView(target) };
        target.setView(view);

        drawChildren(target, states);
        //Widget::draw(target, states);

        target.setView(defaultView);
}

void gsf::WindowWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw Topbar
    target.draw(m_topBar, states);
    // Draw close Button
    target.draw(m_btnClose, states);

    // Draw background
    sf::RectangleShape bgShape({ getWidth(), getHeight() });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
}

void gsf::WindowWidget::updateCurrent(float dt)
{
    // Do nothing by default
}

bool gsf::WindowWidget::handleSpecialEvents(sf::Event &event)
{
    sf::Vector2f localMousePoint = { event.mouseButton.x - getWorldPosition().x , event.mouseButton.y - getWorldPosition().y };
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && m_topBar.isPointIntersecting(localMousePoint))
        {
            // Check if close button was pressed. We have to map the mouse coordinate to local widget coordinates
            if (m_btnClose.isPointIntersecting(localMousePoint))
            {
                setIsRemoveable(true);
            }
            std::cout << "WindowWidget: Left mouse button clicked in topbar" << std::endl;
            m_moveModeActive = true;
            m_moveModeRelMousePos.x = event.mouseButton.x - getWorldPosition().x;
            m_moveModeRelMousePos.y = event.mouseButton.y - getWorldPosition().y;
            // Window should now be shown in the foreground
            setMoveToForground(true);
            return true;
        }
        if (event.mouseButton.button == sf::Mouse::Left && isIntersecting(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
            setMoveToForground(true);
            return false;
        }

    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left && m_topBar.isPointIntersecting(localMousePoint))
        {
            std::cout << "WindowWidget: Left mouse button released in topbar" << std::endl;
            m_moveModeActive = false;
            return true;
        }
    }
    return false;
}

bool gsf::WindowWidget::handleEventCurrent(sf::Event &event)
{
    bool handled = ChildWidget::handleEventCurrent(event);
    if (event.type == sf::Event::MouseMoved && m_moveModeActive)
    {
        setPosition(event.mouseMove.x - getOrigin().x - m_moveModeRelMousePos.x, event.mouseMove.y - getOrigin().y - m_moveModeRelMousePos.y);
        //move();
        std::cout << "MouseMoveEvent mouseMove x: " << event.mouseMove.x << " y: " << event.mouseMove.y << std::endl;
    }
    return handled;
}

void gsf::WindowWidget::calculateSize()
{

}

void gsf::WindowWidget::arrangeChildren()
{
    /*
    float distance = 0.f;
    for (const Ptr &child : m_children)
    {
        //child->centerOrigin();
        child->setPosition(0.f + child->getOrigin().x, distance + child->getOrigin().y);
        distance += child->getHeight();
    }
    calculateSize();
    */
}
