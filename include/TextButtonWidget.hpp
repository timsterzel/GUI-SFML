#pragma once
#ifndef TEXTBUTTONWIDGET_HPP
#define TEXTBUTTONWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "ButtonWidget.hpp"
#include <string>

namespace gsf
{
    class TextButtonWidget: public gsf::ButtonWidget
    {
    public:
        typedef std::unique_ptr<TextButtonWidget> Ptr;
    private:
        const sf::Font &m_font;
        std::string m_text;
        sf::Color m_textColor;
        sf::Color m_hoverTextColor;
        unsigned int m_charSize;
    public:
        static Ptr create(const sf::Font &font);
        static Ptr create(float width, float height, const sf::Font &font);
        static Ptr create(float width, float height, const std::string &text, 
                const sf::Font &font);
        explicit TextButtonWidget(const sf::Font &font);
        TextButtonWidget(float width, float height, const sf::Font &font);
        TextButtonWidget(float width, float height, const std::string &text, 
                const sf::Font &font);

        const std::string& getText() const;
        void setText(const std::string &text);

        sf::Color getTextColor() const;
        void setTextColor(sf::Color color);

        sf::Color getHoverTextColor() const;
        void setHoverTextColor(sf::Color color);

        unsigned int getCharacterSize() const;
        void setCharacterSize(unsigned int size);

    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
    private:
        void init();
    };
}

#endif // !TEXTBUTTONWIDGET_HPP
