#ifndef GUISFMLENVIRONMENT_HPP
#define GUISFMLENVIRONMENT_HPP
#include <SFML/Graphics.hpp>

namespace gsf
{
    class GUISFMLEnvironment : public sf::Drawable
    {
        private:

        public:
            GUISFMLEnvironment();
            virtual ~GUISFMLEnvironment();

            // dt is the delta time
            virtual void update(float dt);

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            virtual void handleEvents(sf::Event &event);

    };

}

#endif // GUISFMLENVIRONMENT_HPP
