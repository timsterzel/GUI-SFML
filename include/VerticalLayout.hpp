#ifndef VERTICALLAYOUT_HPP
#define VERTICALLAYOUT_HPP
#include <SFML/Graphics.hpp>
#include "View.hpp"
#include <string>

namespace gsf
{
    class VerticalLayout: public gsf::View
    {
        protected:

        private:
            sf::Color m_bgColor;
        public:
            VerticalLayout();
            ~VerticalLayout();

            void setBackgroundColor(const sf::Color color);
            sf::Color getBackgroundColor() const;

            void centerOrigin();

        private:
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);

            // Calculate the size of the current View
            virtual void calculateSize();
    };

}

#endif // VERTICALLAYOUT_HPP
