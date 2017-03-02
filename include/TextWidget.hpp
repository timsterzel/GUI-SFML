#pragma once
#ifndef TEXTWIDGET_HPP
#define TEXTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class TextWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<TextWidget> Ptr;
    private:
        sf::Text m_text;
    public:
        static Ptr create();
        static Ptr create(std::string text, sf::Font &font);
        static Ptr create(std::string text, sf::Font &font, int characterSize);
        static Ptr create(std::string text, sf::Font &font, int characterSize, 
                sf::Color color);
        static Ptr create(std::wstring text, sf::Font &font);
        static Ptr create(std::wstring text, sf::Font &font, int characterSize);
        static Ptr create(std::wstring text, sf::Font &font, int characterSize, 
                sf::Color color);
        TextWidget();
        TextWidget(std::string text, sf::Font &font);
        TextWidget(std::string text, sf::Font &font, int characterSize);
        TextWidget(std::string text, sf::Font &font, int characterSize, 
                sf::Color color);
        TextWidget(std::wstring text, sf::Font &font);
        TextWidget(std::wstring text, sf::Font &font, int characterSize);
        TextWidget(std::wstring text, sf::Font &font, int characterSize, 
                sf::Color color);

        void setText(const sf::String &text);
        void setText(const std::wstring text);
        sf::String getText() const;
        // get text as wide string
        std::wstring getWideText() const;

        void setFont(const sf::Font &font);
        const sf::Font& getFont() const;

        void setCharacterSize(const unsigned int size);
        unsigned int getCharacterSize() const;

        void setTextColor(const sf::Color color);
        sf::Color getTextColor() const;

        sf::Vector2f findGlobalCharacterPos(std::size_t index) const;
        sf::Vector2f findLocalCharacterPos(std::size_t index) const;
        // Returns the width and height of the given char which it have
        // with the used character size and font
        sf::Vector2f getWidthAndHeightOfChar(wchar_t c) const;
        // Returns the local bounds of the char of the given index
        sf::FloatRect getLocalBoundsOfChar(std::size_t i) const;
        // Determine the index of the char which is on the given position.
        // Returns -1 when there is no char on the given position
        int findIndexOfCharOnPos(sf::Vector2f localPos) const;
    protected:
        int findCharOnPosBinary(sf::Vector2f localPos, std::size_t l, 
                std::size_t r, std::size_t totalLength) const;

        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
        virtual void updateCurrentAfterChildren(float dt) override;
    private:
        void init(std::string text, sf::Font &font, int characterSize, 
                sf::Color color);
        // Calculate the size of the current widget
        virtual void calculateSize() override;
    };
}

#endif // TEXTWIDGET_HPP
