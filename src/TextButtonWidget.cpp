#include "TextButtonWidget.hpp"
#include <iostream>

gsf::TextButtonWidget::TextButtonWidget(const sf::Font &font)
: ButtonWidget{  }
, m_font{ font }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
{
    init();
}

gsf::TextButtonWidget::TextButtonWidget
    (float width, float height, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
{
    init();
}
gsf::TextButtonWidget::TextButtonWidget(float width,float height, 
        const std::string &text, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
, m_text{ text }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
{
    init();
}

void gsf::TextButtonWidget::init()
{

}

sf::Color gsf::TextButtonWidget::getTextColor() const
{
    return m_textColor;
}

void gsf::TextButtonWidget::setTextColor(sf::Color color)
{
    m_textColor = color;
}

sf::Color gsf::TextButtonWidget::getHoverTextColor() const
{
    return m_hoverTextColor;
}

void gsf::TextButtonWidget::setHoverTextColor(sf::Color color)
{
    m_hoverTextColor = color;
}

const std::string& gsf::TextButtonWidget::getText() const
{
    return m_text;
}

void gsf::TextButtonWidget::setText(const std::string& text)
{
    m_text = text;
}

unsigned int gsf::TextButtonWidget::getCharacterSize() const
{
    return m_charSize;
}
void gsf::TextButtonWidget::setCharacterSize(unsigned int size)
{
    m_charSize = size;
}

void gsf::TextButtonWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    ButtonWidget::drawWidget(target, states);
    // Draw text
    sf::Text text{ m_text, m_font };
    text.setCharacterSize(m_charSize);
    text.setFillColor(m_isHovering ? m_hoverTextColor : m_textColor);
    sf::FloatRect rect{ text.getLocalBounds() };
    // sf::Text has non-zero values for widh and height so we dont may ignore them
    text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    text.setPosition(getWidth() / 2.f, getHeight() / 2.f);
    target.draw(text, states);
}

void gsf::TextButtonWidget::update(float dt)
{
    ButtonWidget::update(dt);
}

bool gsf::TextButtonWidget::handleEvent(sf::Event &event)
{
    bool handled = ButtonWidget::handleEvent(event);

    return handled;
}
