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

            MoveableBlock m_scrollbarHorizontal;
            bool m_scrollbarMoveActive;
            sf::Vector2f m_scrollbarMoveModeRelPos;

        public:
            ScrollableWidget(float width, float height);
            virtual ~ScrollableWidget();

            void setIsVerticalScrollEnabled(bool isEnabled);
            bool isVerticalScrollEnabled() const;
            void setIsHorizontalScrollEnabled(bool isEnabled);
            bool isHorizontalScrollEnabled() const;

            float getTotalWidth() const;
            float getTotalHeight() const;

            // Get the view of the widget (the shown area on display)
            sf::View getShownAreaView(sf::RenderTarget &target) const;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
            virtual void updateCurrent(float dt);

        protected:

            virtual bool handleEventCurrent(sf::Event &event) override;
    };

}

#endif // SCROLLABLEWIDGET_HPP
