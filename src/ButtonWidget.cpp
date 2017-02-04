#include "ButtonWidget.hpp"
#include <iostream>

gsf::ButtonWidget::ButtonWidget(const sf::Font &font)
: Widget()
, m_font{ font }  
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}

gsf::ButtonWidget::ButtonWidget(float width, float height, const sf::Font &font)
: Widget(width, height)
, m_font{ font }
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}
gsf::ButtonWidget::ButtonWidget(float width,float height, const std::string &text, const sf::Font &font)
: Widget(width, height)
, m_font{ font }
, m_text{ text }
{
    m_bgColor = sf::Color::Red;
    m_outlineThickness = 2.f;
    m_outlineColor = sf::Color::White;
}

gsf::ButtonWidget::~ButtonWidget()
{

}


const std::string& gsf::ButtonWidget::getText() const
{
    return m_text;
}

void gsf::ButtonWidget::setText(const std::string& text)
{
    m_text = text;
}

void gsf::ButtonWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw text
    sf::Text text{ m_text, m_font };
    sf::FloatRect rect{ text.getLocalBounds() };
    // sf::Text has non-zero values for widh and height so we dont may ignore them
    text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    text.setPosition(getWidth() / 2.f, getHeight() / 2.f);
    target.draw(text, states);
}

void gsf::ButtonWidget::update(float dt)
{
    // Do nothing by default
}

bool gsf::ButtonWidget::handleEvent(sf::Event &event)
{
    bool handled = Widget::handleEvent(event);
    return handled;
}
