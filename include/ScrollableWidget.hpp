#ifndef SCROLLABLEWIDGET_HPP
#define SCROLLABLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "ChildWidget.hpp"

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
            float m_scrollOffsetX;
            float m_scrollOffsetY;
            float m_scrollSpeed;
            bool m_isVerticalScrollEnabled;
            bool m_isHorizontalScrollEnabled;

        public:

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

        protected:
            ScrollableWidget(float width, float height);

            virtual bool handleEventCurrent(sf::Event &event) override;
    };

}

#endif // SCROLLABLEWIDGET_HPP
