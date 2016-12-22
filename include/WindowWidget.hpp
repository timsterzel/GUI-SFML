#ifndef WINDOWWIDGET_HPP
#define WINDOWWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "ChildWidget.hpp"
#include "Components/MoveableBlock.hpp"

namespace gsf
{
    class WindowWidget: public gsf::ChildWidget
    {
        protected:

        private:
            float m_topbarHeight;
            MoveableBlock m_topbar;
            MoveableBlock m_btnClose;


            bool m_moveModeActive;
            // The relative Mouse pos where the topbar is clicked by activating moving
            sf::Vector2f m_moveModeRelMousePos;
        public:
            WindowWidget();
            WindowWidget(float width, float height);
            void init();
            virtual ~WindowWidget();

            // Get the view of the widget (the shown area on display)
            sf::View getShownAreaView(sf::RenderTarget &target) const;

            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const override;
        private:
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

            virtual void updateCurrent(float dt) override;

            virtual bool handleSpecialEvents(sf::Event &event);

            virtual bool handleEventCurrent(sf::Event &event) override;

            // Calculate the size of the current View
            virtual void calculateSize() override;
            virtual void arrangeChildren() override;
    };

}

#endif // WINDOWWIDGET_HPP
