#include "TextWidget.hpp"
#include <iostream>

gsf::TextWidget::TextWidget()
: Widget{  }
{

}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font)
: Widget{  }
{
    init(sf::String(text), font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize)
: Widget{  }
{
    init(sf::String(text), font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color)
: Widget{  }
{
    init(sf::String(text), font, characterSize, color);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font)
: Widget{  }
{
    init(sf::String(text), font, 12, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font, int characterSize)
: Widget{  }
{
    init(sf::String(text), font, characterSize, sf::Color::Black);
}

gsf::TextWidget::TextWidget(std::wstring text, sf::Font &font, int characterSize, sf::Color color)
: Widget{  }
{
    init(sf::String(text), font, characterSize, color);
}

void gsf::TextWidget::init(std::string text, sf::Font &font, int characterSize, 
        sf::Color color)
{
    m_text.setString(text);
    m_text.setFont(font);
	m_text.setCharacterSize(characterSize);
	m_text.setFillColor(color);
    setBackgroundColor(sf::Color::Transparent);
	calculateSize();
}

void gsf::TextWidget::setText(const sf::String &text)
{
    m_text.setString(text);
    calculateSize();
    //centerOrigin();
}

void gsf::TextWidget::setText(const std::wstring text)
{
    m_text.setString(text);
    calculateSize();
    //centerOrigin();
}
sf::String gsf::TextWidget::getText() const
{
    return m_text.getString();
}


std::wstring gsf::TextWidget::getWideText() const
{
    return m_text.getString().toWideString();
}

void gsf::TextWidget::setFont(const sf::Font &font)
{
    m_text.setFont(font);
}

const sf::Font& gsf::TextWidget::getFont() const
{
    return *(m_text.getFont());
}

void gsf::TextWidget::setCharacterSize(const unsigned int size)
{
    m_text.setCharacterSize(size);
    calculateSize();
    //centerOrigin();
}

unsigned int gsf::TextWidget::getCharacterSize() const
{
    return m_text.getCharacterSize();
}

void gsf::TextWidget::setTextColor(const sf::Color color)
{
    m_text.setFillColor(color);
}

sf::Color gsf::TextWidget::getTextColor() const
{
    return m_text.getFillColor();
}

sf::Vector2f gsf::TextWidget::findGlobalCharacterPos(std::size_t index) const
{
    return m_text.findCharacterPos(index) + getPosition();    
}

sf::Vector2f gsf::TextWidget::findLocalCharacterPos(std::size_t index) const
{
    sf::FloatRect localBounds{ m_text.getLocalBounds() };
    return m_text.findCharacterPos(index) 
        + sf::Vector2f(localBounds.left, localBounds.top );    
}

sf::Vector2f gsf::TextWidget::getWidthAndHeightOfChar(wchar_t c) const
{
    const sf::Font &font{ *(m_text.getFont()) };
    unsigned int charSize{ m_text.getCharacterSize() };
    // Determine width of the char
    float cWidth{ 0.f };
    bool isBold{ m_text.getStyle() & sf::Text::Bold };
    // Tabs are cases which have to be handled special, because the width is
    // not returned correctly by "advanced", so we calculate the width as 4
    // spaces
    if (c == '\t')
    {
        cWidth = (font.getGlyph(' ', charSize, isBold).advance) * 4;
    }
    else if (c == '\n')
    {
        cWidth = 0.f;
    }
    else
    {
        cWidth = font.getGlyph(c, charSize, isBold).advance;
    }
    // Set Height to lineSpacing
    //float cHeight{ font.getGlyph(c, charSize, isBold).bounds.height };
    float cHeight{ font.getLineSpacing(charSize) };
    return sf::Vector2f{ cWidth, cHeight };
}

sf::FloatRect gsf::TextWidget::getLocalBoundsOfChar(std::size_t i) const
{    
    wchar_t c{ m_text.getString().toWideString()[i] };
    sf::Vector2f charPos{ findLocalCharacterPos(i) };
    sf::Vector2f size{ getWidthAndHeightOfChar(c) };
    sf::FloatRect rect{ charPos.x, charPos.y, size.x, size.y };    
    return rect;
}

void gsf::TextWidget::calculateSize()
{
    sf::FloatRect localBounds{ m_text.getLocalBounds() };
    // Top and left of the bounds are not allways 0, 
    // so we add the twice amound of this,
    // so the text is centered in the widget
    setHeight(localBounds.height + localBounds.top * 2);
    setWidth(localBounds.width + localBounds.left * 2);

    // Without margin on top and left
    /*
    setHeight(localBounds.height); //+ localBounds.top * 2);
    setWidth(localBounds.width); //+ localBounds.left * 2);
    m_text.setPosition(-localBounds.left, -localBounds.top);
    */
}

// Use binary search to get the right position
int gsf::TextWidget::findIndexOfCharOnPos(sf::Vector2f localPos) const
{
    std::size_t totalLength{ getWideText().size() };
    if (totalLength < 1)
    {
        return -1;
    }
    return findCharOnPosBinary(localPos, 0, getWideText().size() - 1, totalLength);
}

// Use binary search to find the clicked position. At the beginnig we test if 
// the clicked position is in the char of the middle of the text.
// If so we are done. Else we have only search left or right of the string
int gsf::TextWidget::findCharOnPosBinary(sf::Vector2f localPos, std::size_t l, 
    std::size_t r, std::size_t totalLength) const
{
    // Nothing found
    if (r < l)
    {
        return -1;
    }
    // Get center as index
    //std::size_t i{ static_cast<std::size_t>( (r - l) / 2 )};
    std::size_t i = (l + r) / 2;
    sf::FloatRect cRect{ getLocalBoundsOfChar(i) };
    
    //    ++++++++
    //    ++++c---
    //    --------
    //    
    //    c : index of i
    //    + : left of i
    //    - : right of i
    
    if (cRect.contains(localPos))
    {
        return i;
    }

    // Left of i (case +)
    if ( ((localPos.x < cRect.left && localPos.y <= cRect.top + cRect.height) ||
            (localPos.x > cRect.left && localPos.y < cRect.top))
            // When i is smaller then 0 we are in no text are
            && i > 0)
    {
        return findCharOnPosBinary(localPos, l, i - 1, totalLength);
    }
    // Right of i (case -)
    // First check if we in text area
    else if (i < totalLength - 1)
    {
        return findCharOnPosBinary(localPos, i + 1, r, totalLength);
    }
    return -1;
}

bool gsf::TextWidget::handleEventCurrentAfterChildren(sf::Event &event)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event) };
    /*    
    if (event.type == sf::Event::MouseButtonPressed)
    {        
        sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
        if (!getShownArea().contains(mousePos))
            return false;
        const sf::Font& font{ *(m_text.getFont()) };
        unsigned int charSize{ m_text.getCharacterSize() };
        sf::Vector2f localPos{ mousePos.x - getWorldPosition().x - getOrigin().x,
            mousePos.y - getWorldPosition().y - getOrigin().y };
        std::cout << "LocalPos: (" << localPos.x << "|" << localPos.y << ")\n";
        std::cout << "Font LineSpacing: " << font.getLineSpacing(charSize) << "\n";
        std::cout << "Pos (0) : (" << m_text.findCharacterPos(0).x << "|"
            << m_text.findCharacterPos(0).y << ")\n";

        std::cout << "Pos (10) : (" << m_text.findCharacterPos(10).x << "|"
            << m_text.findCharacterPos(10).y << ")\n";
        
        std::cout << "Pos (13) : (" << m_text.findCharacterPos(13).x << "|"
            << m_text.findCharacterPos(13).y << ")\n";
        int index = findIndexOfCharOnPos(localPos);
        std::cout << "Clicked on index: " << index << std::endl;
        std::cout << "-------------------------------------------------\n";
        //std::cout << "I: (" << findLocalCharacterPos(0).x << "|" 
        //    << findLocalCharacterPos(0).y << ")" 
        //    << getLocalBoundsOfChar(0).height << "\n";
        //std::cout << "pressed on: " << index << std::endl;
    }
    */
    return handled;
}
void gsf::TextWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}
void gsf::TextWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    // Draw text
    target.draw(m_text, states);
}
