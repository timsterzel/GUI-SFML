#ifndef GUISFMLENVIRONMENT_HPP
#define GUISFMLENVIRONMENT_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <vector>
#include <memory>

namespace gsf
{
    class GUISFMLEnvironment : public sf::Drawable
    {
        private:
            std::vector<Widget::Ptr> m_widgets;
            // Is true when ever the mouse is inside the window and false
            // when the mouse is outside
            bool m_isMouseInWindow;
            bool m_isWindowFocused;
        public:
            GUISFMLEnvironment();
            virtual ~GUISFMLEnvironment();

            void addWidget(Widget::Ptr widget);
            Widget::Ptr removeWidget(const Widget& widget);

            void update(float dt);

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            void handleEvent(sf::Event &event);

    };

}

#endif // GUISFMLENVIRONMENT_HPP
