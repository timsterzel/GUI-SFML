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

sf::Text& gsf::TextWidget::getText()
{
    return m_text;
}

void gsf::TextWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void gsf::TextWidget::updateCurrent(float dt)
{
    // Do nothing by default
}
