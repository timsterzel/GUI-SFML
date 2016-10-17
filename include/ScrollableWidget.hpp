#ifndef SCROLLABLEWIDGET_HPP
#define SCROLLABLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widget.hpp"

namespace gsf
{
    class ScrollableWidget: public gsf::Widget
    {
        protected:

        private:
            // The total size, not the shown.
            // A Scrollable can have a shown size (the size, the widget take on the screen)
            // and a total size (the size with all the children widgets inside the scollable widget)
            float m_totalWidth;
            float m_totalHeight;
            bool m_isVerticalScrollEnabled;
            bool m_isHorizontalScrollEnabled;
        public:

            virtual ~ScrollableWidget();

            void setIsVerticalScrollEnabled(bool isEnabled);
            bool isVerticalScrollEnabled() const;
            void setIsHorizontalScrollEnabled(bool isEnabled);
            bool isHorizontalScrollEnabled() const;

        private:

        protected:
            ScrollableWidget(float width, float height);
    };

}

#endif // SCROLLABLEWIDGET_HPP
