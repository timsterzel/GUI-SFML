#ifndef VERTICALLAYOUT_HPP
#define VERTICALLAYOUT_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class VerticalLayout: public gsf::Widget
    {
        protected:

        private:

        public:
            VerticalLayout(float width, float height);
            virtual ~VerticalLayout();

        private:
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);

            // Calculate the size of the current View
            virtual void calculateSize();
            virtual void arrangeChildren();
    };

}

#endif // VERTICALLAYOUT_HPP
