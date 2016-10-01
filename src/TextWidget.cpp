#include "TextWidget.hpp"
#include <iostream>

gsf::TextWidget::TextWidget()
: m_bgColor{ sf::Color::Transparent }
{

}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font)
: m_bgColor{ sf::Color::Transparent }
{
    init(text, font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize)
: m_bgColor{ sf::Color::Transparent }
{
    init(text, font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color)
: m_bgColor{ sf::Color::Transparent }
{
    init(text, font, characterSize, color);
}

void gsf::TextWidget::init(std::string text, sf::Font &font, int characterSize, sf::Color color)
{
    m_text.setString(text);
    m_text.setFont(font);
	m_text.setCharacterSize(characterSize);
	m_text.setColor(color);

	sf::FloatRect localBounds = { m_text.getLocalBounds() };
    // Top and left of the bounds are not allways 0, so we add the twice amound of this,
    // So the text is centered in the widget
    setHeight(localBounds.height + localBounds.top * 2);
    setWidth(localBounds.width + localBounds.left * 2);
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
}

std::string gsf::TextWidget::getText() const
{
    return m_text.getString();
}

void gsf::TextWidget::setCharacterSize(const unsigned int size)
{
    m_text.setCharacterSize(size);
}

unsigned int gsf::TextWidget::getCharacterSize() const
{
    return m_text.getCharacterSize();
}

void gsf::TextWidget::setTextColor(const sf::Color color)
{
    m_text.setColor(color);
}

sf::Color gsf::TextWidget::getTextColor() const
{
    return m_text.getColor();
}

void gsf::TextWidget::setBackgroundColor(const sf::Color color)
{
    m_bgColor = color;
}

sf::Color gsf::TextWidget::getBackgroundColor() const
{
    return m_bgColor;
}

void gsf::TextWidget::centerOrigin()
{
    setOrigin(getWidth() / 2.f, getHeight() / 2.f);
}

void gsf::TextWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw background
    sf::RectangleShape bgShape({ m_width, m_height });
    bgShape.setFillColor(m_bgColor);
    target.draw(bgShape, states);
    // Draw text
    target.draw(m_text, states);
}

void gsf::TextWidget::updateCurrent(float dt)
{
    // Do nothing by default
}
