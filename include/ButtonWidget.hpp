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
            // True when mouse hover over button
            bool m_isHovering;
            // The color of the widget when mouse hover over button
            sf::Color m_hoverFillColor;
        public:
            ButtonWidget();
            ButtonWidget(float width, float height);

            virtual ~ButtonWidget();
            
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
