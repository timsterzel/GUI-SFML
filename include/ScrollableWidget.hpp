#ifndef SCROLLABLEWIDGET_HPP
#define SCROLLABLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "ChildWidget.hpp"
#include "Components/MoveableBlock.hpp"

namespace gsf
{
    class ScrollableWidget: public gsf::ChildWidget
    {
        protected:

        private:
            // The total size, not the shown.
            // A Scrollable can have a shown size (the size, the widget take on the screen)
            // and a total size (the size with all the children widgets inside the scollable widget)
            float m_totalWidth;
            float m_totalHeight;
            // Store how much the children should by moved (scrolled) in the next
            // update step
            float m_scrollOffsetX;
            float m_scrollOffsetY;

            float m_scrollSpeed;
            // Set by user (default: true)
            bool m_isVerticalScrollEnabled;
            bool m_isHorizontalScrollEnabled;
            // the thickness of the scrollbars. By Verticalscrollbar the width and
            // bei horizontal scrolling the height
            float m_scrollbarThickness;
            // Scrollbar Vertical
            // Only scroll when there is a need to scrolling
            // (child is not shown fully in widget)
            bool m_isVerticalScrollNeeded;
            MoveableBlock m_scrollbarVertical;
            bool m_scrollbarVerMoveActive;
            sf::Vector2f m_scrollbarVerMoveModeRelPos;
            // Scrollbar Horizontal
            bool m_isHorizontalScrollNeeded;
            MoveableBlock m_scrollbarHorizontal;
            bool m_scrollbarHorMoveActive;
            sf::Vector2f m_scrollbarHorMoveModeRelPos;
            // Horizontal padding
            const float SCROLLBAR_PAD_HOR;
            // Vertical padding
            const float SCROLLBAR_PAD_VER;


        public:
            ScrollableWidget(float width, float height);
            virtual ~ScrollableWidget();

            void calculateVerticalScrollbarSize();
            void calculateHorizontalScrollbarSize();
            void calculateScrollbarSizes();


            void setIsVerticalScrollEnabled(bool isEnabled);
            bool isVerticalScrollEnabled() const;
            void setIsHorizontalScrollEnabled(bool isEnabled);
            bool isHorizontalScrollEnabled() const;

            float getTotalWidth() const;
            float getTotalHeight() const;

            //bool handleEvent(sf::Event &event) override;

            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            void correctScrollBarPosition();

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
            virtual void updateCurrent(float dt);

            virtual void childAdded() override;

            virtual void childRemoved() override;

        protected:

            // Special Events are Events like scrolling (which have a higher priorety then the child events)
            bool handleSpecialEvents(sf::Event &event);

            virtual bool handleEventCurrent(sf::Event &event) override;

            virtual bool handleEventChildren(sf::Event &event);
    };

}

#endif // SCROLLABLEWIDGET_HPP
