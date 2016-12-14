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

        public:
            GUISFMLEnvironment();
            virtual ~GUISFMLEnvironment();

            void addWidget(Widget::Ptr widget);
            Widget::Ptr removeWidget(const Widget& widget);

            void update(float dt);

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            void handleEvents(sf::Event &event);

    };

}

#endif // GUISFMLENVIRONMENT_HPP
