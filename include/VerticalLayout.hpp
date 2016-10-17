#ifndef VERTICALLAYOUT_HPP
#define VERTICALLAYOUT_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widget.hpp"

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
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

            virtual void updateCurrent(float dt) override;

            // Calculate the size of the current View
            virtual void calculateSize() override;
            virtual void arrangeChildren() override;
    };

}

#endif // VERTICALLAYOUT_HPP
