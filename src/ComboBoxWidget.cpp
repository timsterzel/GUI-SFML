#include "ComboBoxWidget.hpp"
#include <iostream>

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create(const sf::Font &font)
{
    Ptr widget{ std::make_unique<ComboBoxWidget>(font) };
    return std::move(widget);
}

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create(float width, float height,
        const sf::Font &font)
{
    Ptr widget{ std::make_unique<ComboBoxWidget>(width, height, font) };
    return std::move(widget);
}

gsf::ComboBoxWidget::ComboBoxWidget(const sf::Font &font)
: Widget{  }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_currentText{ nullptr }
, m_charSize{ 0 }
{
    init(font);
}

gsf::ComboBoxWidget::ComboBoxWidget(float width, float height, const sf::Font &font)
: Widget{ width, height }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_currentText{ nullptr }
, m_charSize{ 0 }
{
    init(font);
}


void gsf::ComboBoxWidget::init(const sf::Font &font)
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
    TextWidget::Ptr currentText{ 
        TextWidget::create("", font) };
    m_currentText = currentText.get();
    attachChild(std::move(currentText));

    ScrollableWidget::Ptr scrollable{ 
        ScrollableWidget::create(getWidth(), getHeight()) };
    m_scrollableWidget = scrollable.get();
    boundsChanged();
}

void gsf::ComboBoxWidget::addElement(std::wstring element)
{
    m_elements.push_back(element);
    // if we have only one element we select it
    if (m_elements.size() == 1)
    {
        m_currentIndex = 0;
        m_currentText->setText(m_elements[0]);
    }
}
std::wstring gsf::ComboBoxWidget::getElement(int index) const
{
    return m_elements[index];
}

std::wstring gsf::ComboBoxWidget::currentText() const
{
    return m_elements.size() > 0 ? m_elements[m_currentIndex] : L"";

}
int gsf::ComboBoxWidget::currentIndex() const
{
    return m_currentIndex;
}

int gsf::ComboBoxWidget::count() const
{
    return m_elements.size();
}

void gsf::ComboBoxWidget::boundsChanged()
{
    m_charSize = getHeight() - 2.f;
    if (m_currentText)
    {
        m_currentText->setCharacterSize(m_charSize);
    }
}

bool gsf::ComboBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
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

void gsf::ComboBoxWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ComboBoxWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{
    //m_currentText->draw(target, states, defaultView);
}
