#include "Widgets/ConsoleWidget.hpp"
#include "Widgets/TextInputWidget.hpp"
#include "Utility.hpp"
#include <iostream>

gsf::ConsoleWidget::Ptr gsf::ConsoleWidget::create(sf::Font &font)
{
    Ptr widget{ std::make_unique<ConsoleWidget>(font) };
    return std::move(widget);
}

gsf::ConsoleWidget::Ptr gsf::ConsoleWidget::create(float width, float height, 
        sf::Font &font)
{
    Ptr widget{ std::make_unique<ConsoleWidget>(width, height, font) };
    return std::move(widget);
}

gsf::ConsoleWidget::ConsoleWidget(sf::Font &font)
: Widget{  }
, m_textDisplay{ nullptr }
, m_textInput{ nullptr }
, m_inpHistoryCursPos{ 0 }
{
    init(font);
}
gsf::ConsoleWidget::ConsoleWidget(float width, float height, sf::Font &font)
: Widget{ width , height }
, m_textDisplay{ nullptr }
, m_textInput{ nullptr }
, m_inpHistoryCursPos{ 0 }
{
    init(font);
}

void gsf::ConsoleWidget::init(sf::Font &font)
{
    std::unique_ptr<TextInputWidget> textDisplay{ 
        std::make_unique<TextInputWidget>(getWidth(), 
                getHeight() - 20.f - 4.f, font) };
    std::unique_ptr<TextInputWidget> textInput{ 
        std::make_unique<TextInputWidget>(getWidth(), 20.f, font) };
    m_textDisplay = textDisplay.get();
    m_textInput = textInput.get();

    m_textDisplay->setIsHorizontalScrollEnabled(false);
    m_textDisplay->setBackgroundColor(sf::Color::White);
    m_textDisplay->setIsEditable(false);

    m_textInput->setIsVerticalScrollEnabled(false);
    m_textInput->setBackgroundColor(sf::Color::White);
    m_textInput->setPosition(0.f, getHeight() - 20.f);
    m_textInput->setIsNewLineAccepted(false);
    m_textInput->setIsHorizontalScrollbarDrawn(false);
    m_textInput->setOutlineThickness(4.f);;

    setOutlineThickness(4.f);

    attachChild(std::move(textDisplay));
    attachChild(std::move(textInput));
}

void gsf::ConsoleWidget::loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes)
{
    Widget::loadAttributes(document, attributes);
    Widget::loadAttributes(document, attributes, "ConsoleWidget");
}

void gsf::ConsoleWidget::applyAttribute(const std::string &name, 
        const std::string &value)
{
    Widget::applyAttribute(name, value);
}

void gsf::ConsoleWidget::addTextToDisplay(sf::String text)
{
    sf::String actualStr{ m_textDisplay->getText() };
    if (actualStr.getSize() > 0)
    {
        actualStr += "\n";
    }
    m_textDisplay->setText(actualStr + text);
}

void gsf::ConsoleWidget::setOnCommandEnteredListener(std::function
    <void(Widget*, sf::String)> listener)
{
    m_onCommandEnteredListener = listener;
}

bool gsf::ConsoleWidget::handleEventCurrentAfterChildren(sf::Event &event, const sf::RenderTarget &target)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event, target) };
    /*
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseButton.x, 
            event.mouseButton.y }) };
    }
    */
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            if (m_inputHistory.size() > 0 && 
                    m_inpHistoryCursPos < m_inputHistory.size())
            {
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
        //wchar_t c{ static_cast<wchar_t>(event.text.unicode) };
        sf::Uint32 c{ event.text.unicode };
        //sf::String c{ static_cast<sf::String>(event.text.unicode) };
        switch (c)
        {
        // New line, enter key
        case 13: 
            if (m_textInput->isFocused())
            {
                //std::cout << "entered 13" << std::endl;
                // Add entered text to display
                sf::String inputText{ m_textInput->getText() };
                // Store input in history
                m_inputHistory.push_back(inputText);
                // Set history cursor back to 0, so we start again at the beginning
                // when going through history
                m_inpHistoryCursPos = 0;
                addTextToDisplay(">" + inputText);
                m_textInput->setText("");
                if (m_onCommandEnteredListener)
                {
                    m_onCommandEnteredListener(this, inputText);
                }
                return true;
            }
        }
    }
    return handled;
}

void gsf::ConsoleWidget::updateCurrentAfterChildren(float dt)
{

}

void gsf::ConsoleWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states, sf::View defaultView) const
{

}
