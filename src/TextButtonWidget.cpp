#include "TextButtonWidget.hpp"
#include <iostream>

gsf::TextButtonWidget::TextButtonWidget(const sf::Font &font)
: ButtonWidget{  }
, m_font{ font }
{

}

gsf::TextButtonWidget::TextButtonWidget
    (float width, float height, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
{

}
gsf::TextButtonWidget::TextButtonWidget(float width,float height, 
        const std::string &text, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
, m_text{ text }
{

}

gsf::TextButtonWidget::~TextButtonWidget()
{

}

const std::string& gsf::TextButtonWidget::getText() const
{
    return m_text;
}

void gsf::TextButtonWidget::setText(const std::string& text)
{
    m_text = text;
}

void gsf::TextButtonWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    ButtonWidget::drawWidget(target, states);
    // Draw text
    sf::Text text{ m_text, m_font };
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
