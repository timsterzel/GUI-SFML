#include "TextInputWidget.hpp"
#include <iostream>

gsf::TextInputWidget::TextInputWidget(float width, float height, sf::Font &font)
: ChildWidget{ width, height }
//, m_text{ "", font, 12, sf::Color::Black }
, m_text{ nullptr }
, m_font{ font }
, m_charSize{ 12 }
, m_isEditable{ true }
, m_cursor{ "|", font, m_charSize }
, m_scrollable{ nullptr }
, m_acceptNewLines{ true }
, m_isFocused{ false }
, m_cursorPos{ 0 }
, m_lBreaksBefCur{ 0 }
, m_isCursorShown{ true }
, m_blinkFreq{ 0.8f }
, m_lastBlinkTime{ 0.f }
, m_minBreakCharCnt{ 0 }
{
    std::unique_ptr<TextWidget> text{ 
        std::make_unique<TextWidget>("", font, m_charSize, sf::Color::Black) };
    std::unique_ptr<ScrollableWidget> scrollabe{ 
        std::make_unique<ScrollableWidget>(width, height) };
    m_scrollable = scrollabe.get();
    m_text = text.get();
    scrollabe->setBackgroundColor(sf::Color::Transparent);
    scrollabe->attachChild(std::move(text));
    //attachChild(std::move(text));
    attachChild(std::move(scrollabe));
    m_cursor.setFillColor(sf::Color::Black);
}

void gsf::TextInputWidget::setIsEditable(bool isEditable)
{
    m_isEditable = isEditable;
}

bool gsf::TextInputWidget::isEditable() const
{
    return m_isEditable;
}

void gsf::TextInputWidget::setText(const std::wstring &text)
{
    m_currentText = text;
    m_text->setText(m_currentText);
    // Move cursor to end of text
    m_cursorPos = m_currentText.size();
    // Adjust text so that it fits the scrollbar when horizontal scrolling is disabled
    adjustShownText();
    m_scrollable->recalculateScroll();
    m_scrollable->scrollToBottom();
}

std::wstring gsf::TextInputWidget::getText() const
{
    //return m_text->getText().toWideString();
    return m_currentText;
}

void gsf::TextInputWidget::setCharacterSize(const unsigned int size)
{
    m_text->setCharacterSize(size);
    m_charSize = size;
    m_cursor.setCharacterSize(size);
}

unsigned int gsf::TextInputWidget::getCharacterSize() const
{
    return m_charSize;
}

void gsf::TextInputWidget::setTextColor(const sf::Color color)
{
    m_text->setTextColor(color);
}

sf::Color gsf::TextInputWidget::getTextColor() const
{
    return m_text->getTextColor();
}

void gsf::TextInputWidget::setIsNewLineAccepted(bool isAccepted)
{
    m_acceptNewLines = isAccepted;
}

bool gsf::TextInputWidget::getIsNewLineAccepted() const
{
    return m_acceptNewLines;
}

bool gsf::TextInputWidget::isFocused() const
{
    return m_isFocused;
}

void gsf::TextInputWidget::setIsVerticalScrollEnabled(bool isEnabled)
{
    m_scrollable->setIsVerticalScrollEnabled(isEnabled);
}

bool gsf::TextInputWidget::isVerticalScrollEnabled() const
{
    return m_scrollable->isVerticalScrollEnabled();
}

void gsf::TextInputWidget::setIsHorizontalScrollEnabled(bool isEnabled)
{
    m_scrollable->setIsHorizontalScrollEnabled(isEnabled);
}

bool gsf::TextInputWidget::isHorizontalScrollEnabled() const
{
    return m_scrollable->isHorizontalScrollEnabled();
}

void gsf::TextInputWidget::drawCurrent(sf::RenderTarget &target, 
        sf::RenderStates states) const
{

}

void gsf::TextInputWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states) const
{   
    // Draw cursor after children, so that children are not drawn over cursor
    if (m_isCursorShown && m_isEditable)
    {
        target.draw(m_cursor, states);
    }
}

void gsf::TextInputWidget::updateCurrent(float dt)
{
    if (!m_isEditable)
    {
        // Nothing to do
        return;
    }
    
    // Update cursor stuff
    m_lastBlinkTime += dt;
    if (m_lastBlinkTime >= m_blinkFreq)
    {
        m_isCursorShown = !m_isCursorShown;
        m_lastBlinkTime = 0.f;
    }

    m_cursor.setPosition(m_text->findCharacterPos(m_cursorPos + m_lBreaksBefCur));
    //std::wstring text{ m_currentText };
    //std::wstring text{ m_shownText };
    //m_text->setText(text); 
}

bool gsf::TextInputWidget::handleEventCurrent(sf::Event &event)
{
    if (!m_isEditable)
    {
        // Nothing to do
        return false;
    }
    //bool handled{ ChildWidget::handleEvent(event) };/*|| 
      //  m_scrollable->handleEventWidget(event) };*/
    // Check if actual Widget is focused
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
        
        //sf::Vector2f localPos{ mousePos.x - getWorldPosition().x,
        //    mousePos.y - getWorldPosition().y };
        //std::cout << "pressed on: " << findIndexOfCharOnPos(localPos);

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
            // when cursor is moved it should be drawn so we reset its status
            resetCursorStatus();
            adjustShownText();
            //m_cursor.setPosition(
            //    m_text->findCharacterPos(m_cursorPos + m_lBreaksBefCur));
            return true;
        case sf::Keyboard::Right: 
            if (m_cursorPos < m_currentText.length())
            {
                m_cursorPos++;
            }
            resetCursorStatus();
            adjustShownText();
            //m_cursor.setPosition
            //    (m_text->findCharacterPos(m_cursorPos + m_lBreaksBefCur));
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
        case 13: 
            // Dont add new line, when new lines are not accepted
            if (!m_acceptNewLines)
            {
                return false;
            }
            m_currentText.insert(m_cursorPos, L"\n"); m_cursorPos++; 
            break;
        // Add char to text
        default: m_currentText.insert(m_cursorPos, std::wstring() + c); m_cursorPos++;
        }
        resetCursorStatus();
        m_shownText = m_currentText;
        m_text->setText(m_shownText);
        adjustShownText();
        //m_cursor.setPosition
            //(m_text->findCharacterPos(m_cursorPos + m_lBreaksBefCur));
        m_scrollable->recalculateScroll();
        m_scrollable->scrollToRight();
        m_scrollable->scrollToBottom();
        return true;
    }
    return false;
    //return handled;
}

void gsf::TextInputWidget::adjustShownText()
{
    if (!m_scrollable->isHorizontalScrollEnabled() && m_currentText.size() > 0)
    {
        m_lBreaksBefCur = 0;
        std::wstring shownString{ L"" };
        // The chars which are in the actual line
        unsigned int charCntLine{ 0 };
        // The total width of all chars in the current line
        float lineWidth{ 0.f };
        for (unsigned int i{ 0 }; i < m_currentText.size(); i++)
        {
            wchar_t c{ m_currentText[i] };
            // Width of the current char
            float cWidth{ m_text->getWidthAndHeightOfChar(c).x }; 
            lineWidth += cWidth;
            // When Text is out of scrollable widget, we have to add a new line 
            if (lineWidth > m_scrollable->getWidth())
            {
                if (i < m_cursorPos)
                {
                    // We have to increase the "line breaks befor cursor" counter
                    // so we add the cursor later on the right position
                    m_lBreaksBefCur++;
                }
                //shownString += m_currentText.substr(i - charCntLine, charCntLine);
                // Add new line
                shownString += L"\n";
                // add the char with which the line was to wide in the new line
                shownString += c;
                // We have added the char c in the new line, 
                // so we have now 1 char in the current line
                charCntLine = 1;
                lineWidth = cWidth;
            }
            else
            {
                charCntLine++;
                shownString += c;
            }
        }
        m_shownText = shownString;
        m_text->setText(m_shownText);
    }
}

// Use binary search to get the right position
int gsf::TextInputWidget::findIndexOfCharOnPos(sf::Vector2f localPos) const
{
    return findCharOnPosBinary(localPos, 0, m_text->getWideText().size() - 1);
}

int gsf::TextInputWidget::findCharOnPosBinary(sf::Vector2f localPos, std::size_t l, 
    std::size_t r) const
{
    // Nothing found
    if (r <= l)
    {
        return -1;
    }
    // Get center as index
    //std::size_t i{ static_cast<std::size_t>( (r - l) / 2 )};
    int i = (r - l) / 2;
    std::cout << "Index: " << i << std::endl;
    sf::FloatRect cRect{ m_text->getLocalBoundsOfChar(i) };
    
    //    ++++++++
    //    ++++c---
    //    --------
    //    
    //    c : index of i
    //    + : left of i
    //    - : right of i
    
    // Found char (case c)
    if (cRect.contains(localPos))
    {
        return i;
    }
    // Left of i (case +)
    if ( (localPos.x < cRect.left && localPos.y <= cRect.top + cRect.height) ||
            (localPos.x > cRect.left && localPos.y < cRect.top) )
    {
        return findCharOnPosBinary(localPos, l, i - 1);
    }
    // Right of i (case -)
    else
    {
        return findCharOnPosBinary(localPos, i + 1, r);
    }
}

void gsf::TextInputWidget::resetCursorStatus()
{
    m_lastBlinkTime = 0.f;
    m_isCursorShown = true;
}
