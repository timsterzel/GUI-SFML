#pragma once
#ifndef TEXTBUTTONWIDGET_HPP
#define TEXTBUTTONWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "ButtonWidget.hpp"
#include "TextWidget.hpp"
#include <string>

namespace gsf
{
    class TextButtonWidget: public gsf::ButtonWidget
    {
    public:
        typedef std::unique_ptr<TextButtonWidget> Ptr;
    private:
        const sf::Font &m_font;
        std::wstring m_text;
        sf::Color m_textColor;
        sf::Color m_hoverTextColor;
        unsigned int m_charSize;
        TextWidget *m_textWidget;
    public:
        static Ptr create(const sf::Font &font);
        static Ptr create(float width, float height, const sf::Font &font);
        static Ptr create(float width, float height, const std::wstring &text, 
                const sf::Font &font);
        explicit TextButtonWidget(const sf::Font &font);
        TextButtonWidget(float width, float height, const sf::Font &font);
        TextButtonWidget(float width, float height, const std::wstring &text, 
                const sf::Font &font);

        const std::wstring& getText() const;
        void setText(const std::wstring &text);

        sf::Color getTextColor() const;
        void setTextColor(sf::Color color);

        sf::Color getHoverTextColor() const;
        void setHoverTextColor(sf::Color color);

        unsigned int getCharacterSize() const;
        void setCharacterSize(unsigned int size);

    protected:
        void placeText();
        virtual void boundsChanged() override;

        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    private:
        void init();
    };
}

#endif // !TEXTBUTTONWIDGET_HPP
