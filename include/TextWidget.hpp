#ifndef TEXTWIDGET_HPP
#define TEXTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class TextWidget: public gsf::Widget
    {
        protected:

        private:
            sf::Text m_text;
            sf::Color m_bgColor;
        public:
            TextWidget();
            TextWidget(std::string text, sf::Font &font);
            TextWidget(std::string text, sf::Font &font, int characterSize);
            TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color);

            //sf::Text& getText();
            void setText(const std::string text);
            std::string getText() const;

            void setCharacterSize(const unsigned int size);
            unsigned int getCharacterSize() const;

            void setTextColor(const sf::Color color);
            sf::Color getTextColor() const;

            void setBackgroundColor(const sf::Color color);
            sf::Color getBackgroundColor() const;

            void centerOrigin();

            virtual ~TextWidget();

        private:
            void init(std::string text, sf::Font &font, int characterSize, sf::Color color);

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);

            // Calculate the size of the current widget
            virtual void calculateSize();
    };

}

#endif // TEXTWIDGET_HPP
