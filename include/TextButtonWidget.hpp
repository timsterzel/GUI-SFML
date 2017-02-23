#ifndef TEXTBUTTONWIDGET_HPP
#define TEXTBUTTONWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "ButtonWidget.hpp"
#include <string>

namespace gsf
{
    class TextButtonWidget: public gsf::ButtonWidget
    {
        private:
            const sf::Font &m_font;
            std::string m_text;
            sf::Color m_textColor;
            sf::Color m_hoverTextColor;
            unsigned int m_charSize;
        public:
            explicit TextButtonWidget(const sf::Font &font);
            TextButtonWidget(float width, float height, const sf::Font &font);
            TextButtonWidget(float width, float height, const std::string &text, 
                    const sf::Font &font);
            
            void init();

            const std::string& getText() const;
            void setText(const std::string &text);
            
            sf::Color getTextColor() const;
            void setTextColor(sf::Color color);

            sf::Color getHoverTextColor() const;
            void setHoverTextColor(sf::Color color);

            unsigned int getCharacterSize() const;
            void setCharacterSize(unsigned int size);
            
            virtual void update(float dt) override;
        protected:
            virtual bool handleEvent(sf::Event &event) override;
            
        private:

            virtual void drawWidget(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
    };

}

#endif // !TEXTBUTTONWIDGET_HPP