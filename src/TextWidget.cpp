#include "TextWidget.hpp"
#include <iostream>

gsf::TextWidget::TextWidget()
: Widget()
{

}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font)
: Widget()
{
    init(sf::String(text), font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize)
: Widget()
{
    init(sf::String(text), font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color)
: Widget()
{
    init(sf::String(text), font, characterSize, color);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font)
: Widget()
{
    init(sf::String(text), font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font, int characterSize)
: Widget()
{
    init(sf::String(text), font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font, int characterSize, sf::Color color)
: Widget()
{
    init(sf::String(text), font, characterSize, color);
}

void gsf::TextWidget::init(std::string text, sf::Font &font, int characterSize, 
        sf::Color color)
{
    m_text.setString(text);
    m_text.setFont(font);
	m_text.setCharacterSize(characterSize);
	m_text.setFillColor(color);
	calculateSize();
}

gsf::TextWidget::~TextWidget()
{

}

void gsf::TextWidget::setText(const sf::String &text)
{
    m_text.setString(text);
    calculateSize();
    //centerOrigin();
}

void gsf::TextWidget::setText(const std::wstring text)
{
    m_text.setString(text);
    calculateSize();
    //centerOrigin();
}
sf::String gsf::TextWidget::getText() const
{
    return m_text.getString();
}


std::wstring gsf::TextWidget::getWideText() const
{
    return m_text.getString().toWideString();
}

void gsf::TextWidget::setFont(const sf::Font &font)
{
    m_text.setFont(font);
}

const sf::Font& gsf::TextWidget::getFont() const
{
    return *(m_text.getFont());
}

void gsf::TextWidget::setCharacterSize(const unsigned int size)
{
    m_text.setCharacterSize(size);
    calculateSize();
    //centerOrigin();
}

unsigned int gsf::TextWidget::getCharacterSize() const
{
    return m_text.getCharacterSize();
}

void gsf::TextWidget::setTextColor(const sf::Color color)
{
    m_text.setFillColor(color);
}

sf::Color gsf::TextWidget::getTextColor() const
{
    return m_text.getFillColor();
}

sf::Vector2f gsf::TextWidget::findCharacterPos(std::size_t index) const
{
    return m_text.findCharacterPos(index) + getPosition();    
}

void gsf::TextWidget::drawWidget(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    // Draw text
    target.draw(m_text, states);
}

void gsf::TextWidget::update(float dt)
{
    // Do nothing by default
}

bool gsf::TextWidget::handleEvent(sf::Event &event)
{
    bool handled = Widget::handleEvent(event);
    return handled;
}

void gsf::TextWidget::calculateSize()
{
    sf::FloatRect localBounds{ m_text.getLocalBounds() };
    // Top and left of the bounds are not allways 0, 
    // so we add the twice amound of this,
    // so the text is centered in the widget
    setHeight(localBounds.height + localBounds.top * 2);
    setWidth(localBounds.width + localBounds.left * 2);
}
