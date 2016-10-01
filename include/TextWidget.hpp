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
        public:
            TextWidget();
            TextWidget(std::string text, sf::Font &font);
            TextWidget(std::string text, sf::Font &font, int characterSize);
            TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color);

            sf::Text& getText();

            virtual ~TextWidget();

        private:
            void init(std::string text, sf::Font &font, int characterSize, sf::Color color);

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);
    };

}

#endif // TEXTWIDGET_HPP
