#include "ConsoleWidget.hpp"
#include "TextInputWidget.hpp"
#include <iostream>

gsf::ConsoleWidget::ConsoleWidget(float width, float height, sf::Font &font)
: ChildWidget{ width , height }
, m_textDisplay{ nullptr }
, m_textInput{ nullptr }
, m_inputHistoryIndex{ 0 }
{
    std::unique_ptr<TextInputWidget> textDisplay{ 
        std::make_unique<TextInputWidget>(width, height - 20.f, font) };
    std::unique_ptr<TextInputWidget> textInput{ 
        std::make_unique<TextInputWidget>(width, 20.f, font) };
    m_textDisplay = textDisplay.get();
    m_textInput = textInput.get();

    m_textDisplay->setIsHorizontalScrollEnabled(false);
    m_textDisplay->setBackgroundColor(sf::Color::Magenta);
    m_textDisplay->setIsEditable(false);

    m_textInput->setIsVerticalScrollEnabled(false);
    m_textInput->setBackgroundColor(sf::Color::White);
    m_textInput->setPosition(0.f, height - 20.f);
    m_textInput->setIsNewLineAccepted(false);
    
    attachChild(std::move(textDisplay));
    attachChild(std::move(textInput));
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

    if (event.type == sf::Event::TextEntered)
    {
        wchar_t c{ static_cast<wchar_t>(event.text.unicode) };
        switch (c)
        {
        // New line, enter key
        case 13: 
            if (m_textInput->isFocused())
            {
                std::cout << "entered 13" << std::endl;
                // Add entered text to display
                std::wstring displayText = m_textDisplay->getText();
                if (displayText.size() > 0)
                {
                    displayText += L"\n";
                }
                std::wstring inputText{ m_textInput->getText() };
                m_inputHistory.push_back(inputText);
                m_textDisplay->setText(displayText + L">" + inputText);
                m_textInput->setText(L"");
            }
        }
    }
    return false;
    //return handled;
}
