#include "WindowWidget.hpp"
#include <iostream>

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
    m_btnClose.setPosition(getWidth() - (m_btnClose.getWidth() / 2.f) - 6.f, -m_topBar.getHeight() + (m_btnClose.getHeight() / 2.f) + 3.f);
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

const std::string& gsf::WindowWidget::getWindowTitle() const
{
    return m_windowTitle;
}

void gsf::WindowWidget::setWindowTitle(const std::string &text)
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

sf::View gsf::WindowWidget::getWindowTitleView(sf::RenderTarget &target) const
{
    sf::View view;

    float left = { getWorldLeft() };
    float top = { getWorldTop() - m_topBar.getHeight() };
    // Only draw in the toolbar from left til the close button (with little margin)
    float width = { getWidth() - (getWidth() - m_btnClose.getLeft()) - 12.f  };
    float height = { m_topBar.getHeight() };

    view.setSize(width, height);
    view.setCenter(left + (width / 2.f), top + (height / 2.f));
    // The viewport is the area where the widget is on screen
    view.setViewport(sf::FloatRect(left / target.getSize().x , top / target.getSize().y,
        width / target.getSize().x, height / target.getSize().y));
    return view;
}

sf::View gsf::WindowWidget::getTopBarView(sf::RenderTarget &target) const
{
    sf::View view;

    float left = { getWorldLeft() };
    float top = { getWorldTop() - m_topBar.getHeight() };
    // Only draw in the toolbar from left til the close button (with little margin)
    float width = { getWidth() };
    float height = { m_topBar.getHeight() };

    view.setSize(width, height);
    view.setCenter(left + (width / 2.f), top + (height / 2.f));
    // The viewport is the area where the widget is on screen
    view.setViewport(sf::FloatRect(left / target.getSize().x , top / target.getSize().y,
        width / target.getSize().x, height / target.getSize().y));
    return view;
}


void gsf::WindowWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
        //states.transform *= getTransform();

        drawCurrent(target, states);

        // We change the view of the target, so that only the area of the widget and its child
        // which are in its shown area are drawn on the RenderTarget
        //sf::View defaultView = target.getView();
        //sf::View view = { getShownAreaView(target) };
        //target.setView(view);

        drawChildren(target, states);
        //Widget::draw(target, states);

        //target.setView(defaultView);
}

void gsf::WindowWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View defaultView = target.getView();
    // Draw Topbar
    sf::View viewTopBar = { getTopBarView(target) };
    target.setView(viewTopBar);
    target.draw(m_topBar, states);
    // Draw close Button
    target.draw(m_btnClose, states);

    // Draw window title
    sf::View viewTitle = { getWindowTitleView(target) };
    target.setView(viewTitle);

    sf::Text title;
    title.setFont(m_windowTitleFont);
    title.setString(m_windowTitle);
    title.setCharacterSize(m_topBar.getHeight() - 6.f);
    title.setFillColor(m_windowTitleColor);
    title.setStyle(sf::Text::Bold);
    title.setPosition(6.f, -m_topBar.getHeight());
    target.draw(title, states);
    
    target.setView(defaultView);
    
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
