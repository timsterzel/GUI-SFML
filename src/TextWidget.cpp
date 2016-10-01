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
	m_text.setColor(color);
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

void gsf::TextWidget::centerOrigin()
{
    sf::FloatRect localRect = m_text.getLocalBounds();
    m_text.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
}

void gsf::TextWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void gsf::TextWidget::updateCurrent(float dt)
{
    // Do nothing by default
}
