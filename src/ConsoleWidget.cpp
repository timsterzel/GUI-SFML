#include "ConsoleWidget.hpp"
#include "TextInputWidget.hpp"
#include <iostream>

gsf::ConsoleWidget::ConsoleWidget(float width, float height, sf::Font &font)
: ChildWidget{ width , height }
, m_textDisplay{ nullptr }
, m_textInput{ nullptr }
, m_inpHistoryCursPos{ 0 }
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
    m_textInput->setIsHorizontalScrollbarDrawn(false);
    
    attachChild(std::move(textDisplay));
    attachChild(std::move(textInput));
}

void gsf::ConsoleWidget::addTextToDisplay(std::wstring text)
{
    std::wstring actualStr{ m_textDisplay->getText() };
    if (actualStr.size() > 0)
    {
        actualStr += L"\n";
    }
    m_textDisplay->setText(actualStr + text);
}

void gsf::ConsoleWidget::setOnCommandEnteredListener(std::function
    <void(Widget*, std::wstring)> listener)
{
    m_onCommandEnteredListener = listener;
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
    /*
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
    }
    */
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            std::cout << "size: " << m_inputHistory.size() << std::endl;
            if (m_inputHistory.size() > 0 && 
                    m_inpHistoryCursPos < m_inputHistory.size())
            {
                std::cout << "UPP" << std::endl;
                m_inpHistoryCursPos++;
                std::size_t i{ m_inputHistory.size() - m_inpHistoryCursPos };
                m_textInput->setText(m_inputHistory[i]);
            }
            return true;
        case sf::Keyboard::Down: 
            if (m_inputHistory.size() > 0 && m_inpHistoryCursPos > 1)
            {
                m_inpHistoryCursPos--;
                std::size_t i{ m_inputHistory.size() - m_inpHistoryCursPos };
                m_textInput->setText(m_inputHistory[i]);
            }
            return true;
        default:
            break;
        }
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
                std::wstring inputText{ m_textInput->getText() };
                // Store input in history
                m_inputHistory.push_back(inputText);
                // Set history cursor back to 0, so we start again at the beginning
                // when going through history
                m_inpHistoryCursPos = 0;
                addTextToDisplay(L">" + inputText);
                m_textInput->setText(L"");
                if (m_onCommandEnteredListener)
                {
                    m_onCommandEnteredListener(this, inputText);
                }
                return true;
            }
        }
    }
    return false;
}