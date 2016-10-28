#ifndef WINDOWWIDGET_HPP
#define WINDOWWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "ChildWidget.hpp"

namespace gsf
{
    class WindowWidget: public gsf::ChildWidget
    {
        protected:

        private:
            float m_topbarHeight;

            bool m_moveModeActive;
            // The relative Mouse pos where the topbar is clicked by activating moving
            sf::Vector2f m_moveModeRelMousePos;
        public:
            WindowWidget();
            WindowWidget(float width, float height);
            virtual ~WindowWidget();

            // Get the view of the widget (the shown area on display)
            sf::View getShownAreaView(sf::RenderTarget &target) const;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        private:
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

            virtual void updateCurrent(float dt) override;

            virtual bool handleEventCurrent(sf::Event &event) override;

            bool isPointInTopBar(sf::Vector2f point);

            // Calculate the size of the current View
            virtual void calculateSize() override;
            virtual void arrangeChildren() override;
    };

}

#endif // WINDOWWIDGET_HPP
