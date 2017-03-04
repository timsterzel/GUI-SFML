#include "WindowWidget.hpp"
#include <iostream>

gsf::WindowWidget::Ptr gsf::WindowWidget::create(float width, float height, 
        std::wstring title, sf::Font &font)
{
    Ptr widget{ std::make_unique<WindowWidget>(width, height, title, font) };
    return std::move(widget);
}

gsf::WindowWidget::WindowWidget(float width, float height, std::wstring title, 
        sf::Font &font)
: Widget{ width, height }
//, m_topBar{ width, 20.f }
//, m_btnClose{ m_topBar.getHeight() - 6.f, m_topBar.getHeight() - 6.f }
, m_topBarHeight{ 20.f }
, m_windowTitle{ title, font }
, m_windowTitleFont{ font }
, m_windowTitleColor{ sf::Color::White }
, m_moveModeActive{ false }
{
    init();
}

void gsf::WindowWidget::init()
{
    setOutlineThickness(4.f);
    m_windowTitle.setFillColor(m_windowTitleColor);
    m_windowTitle.setStyle(sf::Text::Bold);
    boundsChanged();
    setTopBarFillColor(sf::Color::Black);
    setWindowTitleColor(sf::Color::White);
    setCloseButtonFillColor(sf::Color::White);
}

void gsf::WindowWidget::attachChild(Widget::Ptr child)
{
    Widget::attachChild(std::move(child));
}

gsf::Widget::Ptr gsf::WindowWidget::detachChild(const Widget& node)
{
    return Widget::detachChild(node);
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

sf::Color gsf::WindowWidget::getCloseButtonSymbolFillColor() const
{
    return m_btnCloseSymbolColor;
}

void gsf::WindowWidget::setCloseButtonSymbolFillColor(const sf::Color color)
{
    m_btnCloseSymbolColor = color;
    m_btnCloseSymbolA.setFillColor(color);
    m_btnCloseSymbolB.setFillColor(color);
}

std::wstring gsf::WindowWidget::getWindowTitle() const
{
    return m_windowTitle.getString().toWideString();
    //return m_windowTitle;
}

void gsf::WindowWidget::setWindowTitle(const std::wstring &text)
{
    m_windowTitle.setString(text);
    //m_windowTitle = text;
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

sf::View gsf::WindowWidget::getWindowTitleView(sf::RenderTarget &target, 
        sf::View defaultView) const
{
    sf::View view;

    float left{ getGlobalBounds().left };
    float top{ getWorldTop() };
    // Only draw in the toolbar from left til the close button (with little margin)
    float width{ getWidth() - (getWidth() - m_btnClose.getLeft()) - 12.f  };
    float height{ m_topBar.getHeight() };

    view.setSize(width, height);
    view.setCenter(left + (width / 2.f), top + (height / 2.f));
    // The viewport is the area where the widget is on screen
    view.setViewport(sf::FloatRect(left / target.getSize().x , 
                top / target.getSize().y, width / target.getSize().x, 
                height / target.getSize().y));
    return view;
}
/*
sf::View gsf::WindowWidget::getTopBarView(sf::RenderTarget &target) const
{
    sf::View view;
    
    float left{ getGlobalBounds().left };
    float top{ getWorldTop() - m_topBar.getHeight() };
    // Only draw in the toolbar from left til the close button (with little margin)
    float width{ m_topBar.getWidth() };
    float height{ m_topBar.getHeight() };

    view.setSize(width, height);
    view.setCenter(left + (width / 2.f), top + (height / 2.f));
    // The viewport is the area where the widget is on screen
    view.setViewport(sf::FloatRect(left / target.getSize().x , 
                top / target.getSize().y,
        width / target.getSize().x, height / target.getSize().y));
    return view;
}
*/
void gsf::WindowWidget::boundsChanged()
{
    // The full area is not only the width and heigt of the content area but also
    // the height of the topBar
    m_fullArea.width = getWidth();
    m_fullArea.height = getHeight() + m_topBarHeight;
    // The content area not include the topbar, so its starts after the topbar
    m_contentArea.top = m_topBarHeight;
    
    m_topBar.setPosition(0.f, 0.f);
    m_topBar.setWidth(getLocalContentBounds().width);
    m_topBar.setHeight(m_topBarHeight);
    m_windowTitle.setCharacterSize(m_topBar.getHeight() - 6.f);
    m_windowTitle.setPosition(6.f, 0.f);
    // The Topbar is drawn over the real area of the widget
    // So the topbar dont hide child elements
    //m_topBar.setOrigin(m_topBar.getWidth() / 2.f, m_topBar.getHeight() / 2.f);
    
    //m_topBar.setPosition(-m_outlineThickness + m_topBar.getWidth() / 2.f, 
    //        -m_topBar.getHeight() + m_topBar.getHeight() / 2.f );
    
    m_btnClose.setWidth(m_topBar.getHeight() - 6.f);
    m_btnClose.setHeight(m_topBar.getHeight() - 6.f);
    //m_btnClose.setOrigin(m_btnClose.getWidth() / 2.f, m_btnClose.getHeight() / 2.f);
    
    m_btnClose.setPosition(m_topBar.getRight() 
            - m_btnClose.getWidth() - 2.f, 
            m_topBarHeight - getOutlineThickness()
            - m_btnClose.getHeight()
            );
    
    float btnSymbolWidth{ m_btnClose.getHeight() - 2.f };
    float btnSymbolHeight{ btnSymbolWidth / 6.f };
    m_btnCloseSymbolA.setSize({ btnSymbolWidth, btnSymbolHeight });
    m_btnCloseSymbolA.setOrigin( btnSymbolWidth / 2.f, btnSymbolHeight / 2.f); 
    m_btnCloseSymbolA.setFillColor(m_btnCloseSymbolColor);
    m_btnCloseSymbolA.setPosition(
            m_btnClose.getLeft() + m_btnClose.getWidth() / 2.f,
            m_btnClose.getTop() + m_btnClose.getHeight() / 2.f);
    m_btnCloseSymbolA.setRotation(45.f);
    
    m_btnCloseSymbolB.setSize({ btnSymbolWidth, btnSymbolHeight });
    m_btnCloseSymbolB.setOrigin( btnSymbolWidth / 2.f, btnSymbolHeight / 2.f); 
    m_btnCloseSymbolB.setFillColor(m_btnCloseSymbolColor);
    m_btnCloseSymbolB.setPosition(
            m_btnClose.getLeft() + m_btnClose.getWidth() / 2.f,
            m_btnClose.getTop() + m_btnClose.getHeight() / 2.f);
    m_btnCloseSymbolB.setRotation(-45.f);
}

void gsf::WindowWidget::childAdded(Widget &child)
{
    // Move child widget by the topbars height down so it is at the 
    // upper left corner when its position is (0.f, 0.f). 
    // (At the real (0.f, 0.f) local point there is the topBar)
    child.move(0.f, m_topBarHeight);
}

void gsf::WindowWidget::arrangeChildren()
{

}

bool gsf::WindowWidget::handleEventCurrentBeforeChildren(sf::Event &event)
{
    bool handled{ Widget::handleEventCurrentBeforeChildren(event) };
    sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
    sf::Vector2f localMousePoint{ convertToLocalPoint({ mousePos.x, 
            mousePos.y }) };
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && 
                m_topBar.isPointIntersecting(localMousePoint))
        {
            // Check if close button was pressed. 
            // We have to map the mouse coordinate to local widget coordinates
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
        if (event.mouseButton.button == sf::Mouse::Left && isIntersecting(mousePos))
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
    return handled;
}

bool gsf::WindowWidget::handleEventCurrentAfterChildren(sf::Event &event)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event) };
    if (event.type == sf::Event::MouseMoved && m_moveModeActive)
    {
        setPosition(event.mouseMove.x - getOrigin().x - m_moveModeRelMousePos.x, 
                event.mouseMove.y - getOrigin().y - m_moveModeRelMousePos.y);
    }
    return handled;
}

void gsf::WindowWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::WindowWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    sf::View oldView{ target.getView() };
    // Draw Topbar
    //sf::View viewTopBar{ getTopBarView(target) };
    //target.setView(viewTopBar);
    target.draw(m_topBar, states);
    // Draw close Button
    target.draw(m_btnClose, states);
    target.draw(m_btnCloseSymbolA, states);
    target.draw(m_btnCloseSymbolB, states);

    // Draw window title
    sf::View viewTitle{ getWindowTitleView(target, defaultView) };
    target.setView(viewTitle);
    /*
    sf::Text title;
    title.setFont(m_windowTitleFont);
    title.setString(m_windowTitle);
    title.setCharacterSize(m_topBar.getHeight() - 6.f);
    title.setFillColor(m_windowTitleColor);
    title.setStyle(sf::Text::Bold);
    //title.setPosition(6.f, -m_topBar.getHeight());
    title.setPosition(6.f, 0.f);
    target.draw(title, states);
    */
    target.draw(m_windowTitle, states);
    target.setView(oldView);
}
