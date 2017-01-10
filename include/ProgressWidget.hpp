#ifndef PROGRESSWIDGET_HPP
#define PROGRESSWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class ProgressWidget: public gsf::Widget
    {
        protected:

        private:

        public:
            ProgressWidget();

            virtual ~ProgressWidget();

            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const override;
            virtual void update(float dt) override;

        protected:
            virtual bool handleEvent(sf::Event &event) override;
    };

}

#endif // !PROGRESSWIDGET_HPP
