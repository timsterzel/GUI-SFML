#include "TextWidget.hpp"
#include <iostream>

gsf::TextWidget::TextWidget()
{

}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font)
{
    init(text, font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize)
{
    init(text, font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color)
{
    init(text, font, characterSize, color);
}

void gsf::TextWidget::init(std::string text, sf::Font &font, int characterSize, sf::Color color)
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
/*
sf::Text& gsf::TextWidget::getText()
{
    return m_text;
}
*/
void gsf::TextWidget::setText(const std::string text)
{
    m_text.setString(text);
    calculateSize();
    centerOrigin();
}

std::string gsf::TextWidget::getText() const
{
    return m_text.getString().toAnsiString();
}

void gsf::TextWidget::setCharacterSize(const unsigned int size)
{
    m_text.setCharacterSize(size);
    calculateSize();
    centerOrigin();
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

void gsf::TextWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    // Draw background
    sf::RectangleShape bgShape({ m_width, m_height });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
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
    sf::FloatRect localBounds = { m_text.getLocalBounds() };
    // Top and left of the bounds are not allways 0, so we add the twice amound of this,
    // So the text is centered in the widget
    setHeight(localBounds.height + localBounds.top * 2);
    setWidth(localBounds.width + localBounds.left * 2);
}
