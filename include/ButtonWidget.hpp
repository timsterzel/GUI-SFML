#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class ButtonWidget: public gsf::Widget
    {
        private:
            //sf::Color m_outlineColor;
            //float m_outlineThickness;
            const sf::Font &m_font;
            std::string m_text;
            // True when mouse hover over button
            bool m_isHovering;
            // The color of the widget when mouse hover over button
            sf::Color m_hoverFillColor;
        public:
            ButtonWidget(const sf::Font &font);
            ButtonWidget(float width, float height, const sf::Font &font);
            ButtonWidget(float width, float height, const std::string &text, 
                    const sf::Font &font);

            virtual ~ButtonWidget();

            const std::string& getText() const;
            void setText(const std::string &text);
            
            sf::Color getHoverFillColor() const;
            void setHoverFillColor(sf::Color color);

            virtual void drawWidget(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
            virtual void update(float dt) override;

        protected:
            virtual bool handleEvent(sf::Event &event) override;
    };

}

#endif // !BUTTONWIDGET_HPP
