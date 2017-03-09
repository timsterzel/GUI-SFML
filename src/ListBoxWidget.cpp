#include "ListBoxWidget.hpp"
#include <iostream>

gsf::ListBoxWidget::Ptr gsf::ListBoxWidget::create(const sf::Font &font)
{
    Ptr widget{ std::make_unique<ListBoxWidget>(font) };
    return std::move(widget);
}

gsf::ListBoxWidget::Ptr gsf::ListBoxWidget::create(float width, float height,
        const sf::Font &font)
{
    Ptr widget{ std::make_unique<ListBoxWidget>(width, height, font) };
    return std::move(widget);
}

gsf::ListBoxWidget::ListBoxWidget(const sf::Font &font)
: Widget{  }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_charSize{ 12 }
, m_font(font)
{
    init(font);
}

gsf::ListBoxWidget::ListBoxWidget(float width, float height, const sf::Font &font)
: Widget{ width, height }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_charSize{ 12 }
, m_font(font)
{
    init(font);
}


void gsf::ListBoxWidget::init(const sf::Font &font)
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
    
    ScrollableWidget::Ptr scrollableWidget
        { ScrollableWidget::create(getWidth(), getHeight()) };
    m_scrollableWidget = scrollableWidget.get();
    scrollableWidget->setIsHorizontalScrollEnabled(false);
    attachChild(std::move(scrollableWidget));
    createScrollable();
}

void gsf::ListBoxWidget::addElement(std::wstring element)
{
    m_elements.push_back(element);
    createScrollable();
}
std::wstring gsf::ListBoxWidget::getElement(int index) const
{
    return m_elements[index];
}

std::wstring gsf::ListBoxWidget::currentText() const
{
    return m_elements.size() > 0 ? m_elements[m_currentIndex] : L"";

}
int gsf::ListBoxWidget::currentIndex() const
{
    return m_currentIndex;
}

int gsf::ListBoxWidget::count() const
{
    return m_elements.size();
}

void gsf::ListBoxWidget::boundsChanged()
{
    if (m_scrollableWidget)
    {
        m_scrollableWidget->setWidth(getWidth());
        m_scrollableWidget->setHeight(getHeight());
    }
    /*
    m_charSize = getHeight() - 2.f;
    if (m_currentText)
    {
        m_currentText->setCharacterSize(m_charSize);
    }
    */
}

void gsf::ListBoxWidget::createScrollable()
{
    VerticalLayout::Ptr layout{ VerticalLayout::create() };
    for (auto element : m_elements)
    {
        TextWidget::Ptr textWidget{ TextWidget::create(element, m_font) };
        layout->attachChild(std::move(textWidget));
    }
    layout->setBackgroundColor(sf::Color::Red);
    m_scrollableWidget->attachChild(std::move(layout));
}

bool gsf::ListBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    bool handled = Widget::handleEventCurrentAfterChildren(event, target);
    if (event.type == sf::Event::MouseMoved)
    {

        sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseMove.x, 
            event.mouseMove.y }) };
        bool intersects{ isIntersecting(mousePos) };
        bool isInShownArea{ getShownArea().contains(mousePos) };
    }
    return handled;
}

void gsf::ListBoxWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ListBoxWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{
    /*
    sf::View oldView{ target.getView() };
    target.setView(defaultView);
    m_scrollableWidget->draw(target, states, defaultView);

    target.setView(oldView);
    */    
}
