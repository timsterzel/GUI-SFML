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
            // A Scrollable can have a shown size and a total size
            // with all children.
            float m_totalWidth;
            float m_totalHeight;
        public:

            virtual ~ScrollableWidget();

        private:

        protected:
            ScrollableWidget();
    };

}

#endif // SCROLLABLEWIDGET_HPP
