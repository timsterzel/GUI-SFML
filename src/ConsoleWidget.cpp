#include "ConsoleWidget.hpp"
#include "TextInputWidget.hpp"
#include <iostream>

gsf::ConsoleWidget::ConsoleWidget(float width, float height, sf::Font &font)
: ChildWidget{ width , height }
, m_textDisplay{ nullptr }
, m_textInput{ nullptr }
{
    std::unique_ptr<TextInputWidget> textDisplay{ 
        std::make_unique<TextInputWidget>(width, height - 20.f, font) };
    std::unique_ptr<TextInputWidget> textInput{ 
        std::make_unique<TextInputWidget>(width, 20.f, font) };
    m_textDisplay = textDisplay.get();
    m_textInput = textInput.get();

    m_textDisplay->setIsHorizontalScrollEnabled(false);
    //m_textDisplay->setBackgroundColor(sf::Color::Green);

    m_textInput->setIsVerticalScrollEnabled(false);
    //m_textInput->setBackgroundColor(sf::Color::White);
    m_textInput->setPosition(0.f, height - 20.f);

    attachChild(std::move(textDisplay));
    attachChild(std::move(textInput));
}

bool gsf::ConsoleWidget::isFocused() const
{
    return m_isFocused;
}

void gsf::ConsoleWidget::drawCurrent(sf::RenderTarget &target, 
        sf::RenderStates states) const
{

}

void gsf::ConsoleWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states) const
{

}

void gsf::ConsoleWidget::updateCurrent(float dt)
{

}

bool gsf::ConsoleWidget::handleEventCurrent(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };

    }
    if (event.type == sf::Event::KeyPressed && m_isFocused)
    {
    
    }
    return false;
    //return handled;
}
