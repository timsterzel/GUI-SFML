#include "WindowWidget.hpp"
#include <iostream>
/*
gsf::WindowWidget::WindowWidget()
: ChildWidget()
, m_topBar{ 0.f, 20.f }
, m_btnClose{ m_topBar.getHeight() - 6.f, m_topBar.getHeight() - 6.f }
, m_moveModeActive{ false }
, m_windowTextFont{ nullptr }
{
    init();
}
*/
gsf::WindowWidget::WindowWidget(float width, float height, std::string title, sf::Font &font)
: ChildWidget(width, height)
, m_topBar{ width, 20.f }
, m_btnClose{ m_topBar.getHeight() - 6.f, m_topBar.getHeight() - 6.f }
, m_windowTitle{ title }
, m_windowTitleFont{ font }
, m_windowTitleColor{ sf::Color::White }
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
    m_btnClose.setPosition(getWidth() - (m_btnClose.getWidth() / 2.f) - 3.f, -m_topBar.getHeight() + (m_btnClose.getHeight() / 2.f) + 3.f);
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

std::string gsf::WindowWidget::getWindowTitle() const
{
    return m_windowTitle;
}

void gsf::WindowWidget::setWindowTitle(std::string text)
{
    m_windowTitle = text;
}

sf::Font gsf::WindowWidget::getWindowTitleFont() const
{
    return m_windowTitleFont;
}

void gsf::WindowWidget::setWindowTitleFont(sf::Font &font)
{
    m_windowTitleFont = font;
}

sf::Color gsf::WindowWidget::getWindowTitleColor() const
{
    return m_windowTitleColor;
}

void gsf::WindowWidget::setWindowTitleColor(sf::Color color)
{
    m_windowTitleColor = color;
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
    // Draw window title
    sf::Text title;
    title.setFont(m_windowTitleFont);
    title.setString(m_windowTitle);
    title.setCharacterSize(m_topBar.getHeight() - 6.f);
    title.setColor(m_windowTitleColor);
    title.setStyle(sf::Text::Bold);
    title.setPosition(6.f, -m_topBar.getHeight());
    target.draw(title, states);
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
        if (event.mouseButton.button == sf::Mouse::Left && m_moveModeActive)
        {
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
