#include "ScrollableWidget.hpp"
#include <iostream>

gsf::ScrollableWidget::ScrollableWidget(float width, float height)
: Widget(width, height)
, m_totalWidth{ width }
, m_totalHeight{ height }
, m_scrollOffsetX{ 0.f }
, m_scrollOffsetY{ 0.f }
, m_scrollSpeed{ 6.0f }
, m_isVerticalScrollEnabled{ true }
, m_isHorizontalScrollEnabled{ false }
{

}

gsf::ScrollableWidget::~ScrollableWidget()
{

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

sf::View gsf::ScrollableWidget::getShownAreaView(sf::RenderTarget &target) const
{
        sf::View view;
        // The view should have the same size as the layout, so the shown area of the widget is never bigger than the size of the widget,
        // although when the children widgets of the layout are bigger.
        view.setSize(getWidth(), getHeight());
        float scrollOffsetX = m_scrollOffsetX;
        float scrollOffsetY = m_scrollOffsetY;
        view.setCenter(getWorldPosition().x - getOrigin().x + (getWidth() / 2.f) + scrollOffsetX, getWorldPosition().y - getOrigin().y + (getHeight() / 2.f) + scrollOffsetY );

        float startX = ( getWorldPosition().x - getOrigin().x ) / target.getSize().x;
        float startY = ( getWorldPosition().y - getOrigin().y ) / target.getSize().y;
        float viewWidth = getWidth() / target.getSize().x;
        float viewHeight = getHeight() / target.getSize().y;
        // The viewport is the area where the widget is on screen
        view.setViewport(sf::FloatRect(startX , startY , viewWidth, viewHeight));
        return view;
}

void gsf::ScrollableWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
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

bool gsf::ScrollableWidget::handleEventCurrent(sf::Event &event)
{

    Widget::handleEventCurrent(event);
    if (event.type == sf::Event::MouseWheelMoved)
    {
        std::cout << "MouseWheel moved, delta: " << event.mouseWheel.delta << std::endl;
        std::cout << "m_scrollOffsetY: " << m_scrollOffsetY << std::endl;
        m_scrollOffsetY -= event.mouseWheel.delta * m_scrollSpeed;
        if (m_scrollOffsetY < 0)
        {
            m_scrollOffsetY = 0.f;
        }
    }

    return false;
}
