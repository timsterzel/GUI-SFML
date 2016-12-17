#include "WindowWidget.hpp"
#include <iostream>

gsf::WindowWidget::WindowWidget()
: ChildWidget()
, m_topbarHeight{ 20.f }
, m_moveModeActive{ false }
{

}

gsf::WindowWidget::WindowWidget(float width, float height)
: ChildWidget(width, height)
, m_topbarHeight{ 20.f }
, m_moveModeActive{ false }
{

}

gsf::WindowWidget::~WindowWidget()
{

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

void gsf::WindowWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
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
    sf::RectangleShape topBar({ getWidth(), m_topbarHeight });
    topBar.setFillColor(sf::Color::Magenta);
    // The Topbar is drawn over the real area of the widget
    // So the topbar dont hide child elements
    topBar.setPosition( 0.f, -m_topbarHeight );
    target.draw(topBar, states);

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
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && isPointInTopBar(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
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
        if (event.mouseButton.button == sf::Mouse::Left && isPointInTopBar(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
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

bool gsf::WindowWidget::isPointInTopBar(sf::Vector2f point)
{
    return point.x >= getWorldLeft() && point.x <= getWorldRight() && point.y >= getWorldTop() - m_topbarHeight && point.y <= getWorldTop();
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
