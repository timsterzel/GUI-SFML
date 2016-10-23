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
}

std::string gsf::TextWidget::getText() const
{
    return m_text.getString();
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
    m_text.setColor(color);
}

sf::Color gsf::TextWidget::getTextColor() const
{
    return m_text.getColor();
}

void gsf::TextWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
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
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && isIntersecting(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
        {
            std::cout << "TextWidget: Left Mouse Button Clicked. Text: " << m_text.getString().toAnsiString() << std::endl;
            return true;
        }
    }

    return false;
}

void gsf::TextWidget::calculateSize()
{
    sf::FloatRect localBounds = { m_text.getLocalBounds() };
    // Top and left of the bounds are not allways 0, so we add the twice amound of this,
    // So the text is centered in the widget
    setHeight(localBounds.height + localBounds.top * 2);
    setWidth(localBounds.width + localBounds.left * 2);
}
