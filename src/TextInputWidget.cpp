#include"TextInputWidget.hpp"
#include<iostream>

gsf::TextInputWidget::TextInputWidget(float width, float height, sf::Font &font)
: Widget{ width, height }
, m_isFocused{ false }
, m_cursorPos{ 0 }
{
    m_text.setFont(font);
    m_text.setCharacterSize(12);
    m_text.setFillColor(sf::Color::Black);
}

void gsf::TextInputWidget::setText(const std::string &text)
{
   m_text.setString(text);
}

std::string gsf::TextInputWidget::getText() const
{
   return m_text.getString().toAnsiString();
}

void gsf::TextInputWidget::setCharacterSize(const unsigned int size)
{
   m_text.setCharacterSize(size);
}

unsigned int gsf::TextInputWidget::getCharacterSize() const
{
   return m_text.getCharacterSize();
}

void gsf::TextInputWidget::setTextColor(const sf::Color color)
{
   m_text.setFillColor(color);
}

sf::Color gsf::TextInputWidget::getTextColor() const
{
   return m_text.getFillColor();
}

bool gsf::TextInputWidget::isFocused() const
{
    return m_isFocused;
}

void gsf::TextInputWidget::drawWidget(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void gsf::TextInputWidget::update(float dt)
{
    // Add cursor
    std::wstring text{ m_currentText };
    text.insert(m_cursorPos, L"|");
    // Draw text
    m_text.setString(text);
}

bool gsf::TextInputWidget::handleEvent(sf::Event &event)
{
    bool handled{ Widget::handleEvent(event) };
    // Check if actual Widget is focused
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
        bool isMouseInShownArea{ getShownArea().contains(mousePos) };
        bool intersecting{ isIntersecting(mousePos) };
        if (isMouseInShownArea && intersecting)
        {
            m_isFocused = true;
        }
        else
        {
            m_isFocused = false;
        }
    }
    if (event.type == sf::Event::KeyPressed && m_isFocused)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            if (m_cursorPos > 0)
            {
                m_cursorPos--;
            }
            return true;
        case sf::Keyboard::Right: 
            if (m_cursorPos < m_currentText.length())
            {
                m_cursorPos++;
            }
            return true;
        default: break;
        }
    }
    // If Widget is focused and Text entered, handle entered text
    if (m_isFocused && event.type == sf::Event::TextEntered)
    {
        // To handle umlauts and other 'exotic' chars we use widestring
        // and wide char
        //std::wstring actualTxt{ m_text.getString().toWideString() };
        wchar_t c{ static_cast<wchar_t>(event.text.unicode) };
        std::cout << "Entered: " << c << std::endl;
        switch (c)
        {
        // Backspace
        case 8: 
            if (m_currentText.length() > 0) 
            {
                // Remove chars right of cursor when there are chars
                if (m_cursorPos > 0 && m_cursorPos < m_currentText.length())
                {
                    m_currentText.erase(m_cursorPos - 1, 1);
                    m_cursorPos--;
                }
                // When cursos is at the end of the text, p
                // place cursor behind char which we want to delete,
                else if (m_cursorPos == m_currentText.length())
                {
                    // Delete last char
                    m_currentText.pop_back();
                    m_cursorPos--;
                }
            }
            break;
        // Delete Pressed
        case 127: 
            if (m_currentText.length() > 0 && 
                    m_cursorPos < m_currentText.length())
            {
                m_currentText.erase(m_cursorPos, 1);
            }
                break;
        // Enter key
        case 13: m_currentText.insert(m_cursorPos, L"\n"); m_cursorPos++; break;
        // Add char to text
        default: m_currentText.insert(m_cursorPos, std::wstring() + c); m_cursorPos++;
        }
        
        return true;
    }
    return handled;
}
