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
            bool m_isVerticalScrollEnabled;
            bool m_isHorizontalScrollEnabled;

            // Scrollbar horizontal
            MoveableBlock m_scrollbarHorizontal;
            bool m_scrollbarMoveActive;
            sf::Vector2f m_scrollbarMoveModeRelPos;
            // Horizontal padding
            const float SCROLLBAR_PAD_HOR;

        public:
            ScrollableWidget(float width, float height);
            virtual ~ScrollableWidget();

            void calculateScrollbarSize();

            void setIsVerticalScrollEnabled(bool isEnabled);
            bool isVerticalScrollEnabled() const;
            void setIsHorizontalScrollEnabled(bool isEnabled);
            bool isHorizontalScrollEnabled() const;

            float getTotalWidth() const;
            float getTotalHeight() const;

            // Get the view of the widget (the shown area on display)
            sf::View getShownAreaView(sf::RenderTarget &target) const;

            bool handleEvent(sf::Event &event) override;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

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
    };

}

#endif // SCROLLABLEWIDGET_HPP
