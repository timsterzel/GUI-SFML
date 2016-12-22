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
            MoveableBlock m_topBar;
            MoveableBlock m_btnClose;
            std::string m_windowTitle;
            sf::Font &m_windowTitleFont;
            sf::Color m_windowTitleColor;


            bool m_moveModeActive;
            // The relative Mouse pos where the topbar is clicked by activating moving
            sf::Vector2f m_moveModeRelMousePos;
        public:
            //WindowWidget();
            WindowWidget(float width, float height, std::string title, sf::Font &font);
            void init();
            virtual ~WindowWidget();

            sf::Color getTopbarFillColor() const;
            void setTopBarFillColor(const sf::Color color);

            sf::Color getCloseButtonFillColor() const;
            void setCloseButtonFillColor(const sf::Color color);

            std::string getWindowTitle() const;
            void setWindowTitle(std::string text);

            sf::Font getWindowTitleFont() const;
            void setWindowTitleFont(sf::Font &font);

            sf::Color getWindowTitleColor() const;
            void setWindowTitleColor(sf::Color color);

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
