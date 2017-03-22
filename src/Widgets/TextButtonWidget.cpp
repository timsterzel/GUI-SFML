#include "Widgets/TextButtonWidget.hpp"
#include "Utility.hpp"
#include <iostream>

gsf::TextButtonWidget::Ptr gsf::TextButtonWidget::create(const sf::Font &font)
{
    Ptr widget{ std::make_unique<TextButtonWidget>(font) };
    return std::move(widget);
}

gsf::TextButtonWidget::Ptr gsf::TextButtonWidget::create(float width, float height, 
        const sf::Font &font)
{
    Ptr widget{ std::make_unique<TextButtonWidget>(width, height, font) };
    return std::move(widget);
}

gsf::TextButtonWidget::Ptr gsf::TextButtonWidget::create(float width, float height, 
        const sf::String &text, const sf::Font &font)
{
    Ptr widget{ std::make_unique<TextButtonWidget>(width, height, text, font) };
    return std::move(widget);
}

gsf::TextButtonWidget::TextButtonWidget(const sf::Font &font)
: ButtonWidget{  }
, m_font{ font }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
, m_textWidget{ nullptr }
{
    init();
}

gsf::TextButtonWidget::TextButtonWidget
    (float width, float height, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
, m_textWidget{ nullptr }
{
    init();
}
gsf::TextButtonWidget::TextButtonWidget(float width,float height, 
        const sf::String &text, const sf::Font &font)
: ButtonWidget{ width, height }
, m_font{ font }
, m_text{ text }
, m_textColor{ sf::Color::Black }
, m_hoverTextColor{ sf::Color::White }
, m_charSize{ 12 }
, m_textWidget{ nullptr }
{
    init();
}

void gsf::TextButtonWidget::init()
{
    TextWidget::Ptr textWidget{ TextWidget::create
        (m_text, m_font, m_charSize, m_textColor) };
    m_textWidget = textWidget.get();
    attachChild(std::move(textWidget));
    m_textWidget->setTextColor(m_textColor);
    placeText();
}

void gsf::TextButtonWidget::loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes)
{
    ButtonWidget::loadAttributes(document, attributes);
    Widget::loadAttributes(document, attributes, "TextButtonWidget");
}

void gsf::TextButtonWidget::applyAttribute(const std::string &name, 
        const std::string &value)
{
    ButtonWidget::applyAttribute(name, value);
    if (name == "backgroundColor")
    {
        sf::Color color{ Utility::stringToColor(value) };
        setBackgroundColor(color);
    }
    else if(name == "outlineColor")
    {
        sf::Color color { Utility::stringToColor(value) };
        setOutlineColor(color);
    }
    else if (name == "outlineThickness")
    {
        float thickness{ std::stof(value) };
        setOutlineThickness(thickness);
    }
}

sf::Color gsf::TextButtonWidget::getTextColor() const
{
    return m_textColor;
}

void gsf::TextButtonWidget::setTextColor(sf::Color color)
{
    m_textColor = color;
    if (!m_isHovering)
    {
        m_textWidget->setTextColor(color);
    }
}

sf::Color gsf::TextButtonWidget::getHoverTextColor() const
{
    return m_hoverTextColor;
}

void gsf::TextButtonWidget::setHoverTextColor(sf::Color color)
{
    m_hoverTextColor = color;
    if (m_isHovering)
    {
        m_textWidget->setTextColor(color);
    }
}

const sf::String& gsf::TextButtonWidget::getText() const
{
    return m_text;
}

void gsf::TextButtonWidget::setText(const sf::String& text)
{
    m_text = text;
    m_textWidget->setText(text);
    placeText();
}

unsigned int gsf::TextButtonWidget::getCharacterSize() const
{
    return m_charSize;
}
void gsf::TextButtonWidget::setCharacterSize(unsigned int size)
{
    m_charSize = size;
    m_textWidget->setCharacterSize(size);
    placeText();
}

void gsf::TextButtonWidget::placeText()
{
    sf::FloatRect bounds{ m_textWidget->getLocalBounds() };
    m_textWidget->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    m_textWidget->setPosition(getWidth() / 2.f, getHeight() / 2.f);
}

void gsf::TextButtonWidget::boundsChanged()
{
    Widget::boundsChanged();
    placeText();
}

bool gsf::TextButtonWidget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    bool isHoveringBefore{ m_isHovering };
    bool handled{ ButtonWidget::handleEventCurrentAfterChildren(event, target) };
    if (m_isHovering != isHoveringBefore)
    {
        m_textWidget->setTextColor(m_isHovering ? m_hoverTextColor : m_textColor);
    }
    return handled;
}

void gsf::TextButtonWidget::updateCurrentAfterChildren(float dt)
{
    ButtonWidget::updateCurrentAfterChildren(dt);
}

void gsf::TextButtonWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{
    ButtonWidget::drawCurrentAfterChildren(target, states, defaultView);
}
