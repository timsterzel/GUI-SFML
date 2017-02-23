#pragma once
#ifndef SCROLLABLEWIDGET_HPP
#define SCROLLABLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widget.hpp"
#include "Components/MoveableBlock.hpp"

namespace gsf
{
    class ScrollableWidget: public gsf::Widget
    {
    protected:

    private:
        // The total size, not the shown.
        // A Scrollable can have a shown size 
        // (the size, the widget take on the screen)
        // and a total size (the size with all the children widgets 
        // inside the scollable widget)
        float m_totalWidth;
        float m_totalHeight;
        // Store how much the children should by moved (scrolled) in the next
        // update step
        float m_scrollOffsetX;
        float m_scrollOffsetY;

        float m_scrollSpeed;

        sf::Color m_scrollBarColor;
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

        bool m_isVerticalScrollbarDrawn;
        bool m_isHorizontalScrollbarDrawn;
            
        const float SCROLLBAR_PAD;
        // The two scrollbars dont overlap. The Scrollbars stops before
        // The other scrollbars top begin and have in addition this padding
        const float PAD_BETTWEEN_SCROLLBARS;
    public:
        ScrollableWidget(float width, float height);

        // ScrollableWidget only can handle one widget, so we have to 
        // implement the methods different
        void attachChild(Ptr child) override;

        void calculateVerticalScrollbarSize();
        void calculateHorizontalScrollbarSize();
        void calculateScrollbarSizes();

        void setScrollBarColor(sf::Color color);
        sf::Color getScrollBarColor() const;

        void setIsVerticalScrollEnabled(bool isEnabled);
        bool isVerticalScrollEnabled() const;
        void setIsHorizontalScrollEnabled(bool isEnabled);
        bool isHorizontalScrollEnabled() const;

        void setIsVerticalScrollbarDrawn(bool isDrawn);
        void setIsHorizontalScrollbarDrawn(bool isDrawn);

        float getTotalWidth() const;
        float getTotalHeight() const;
        // Call when the scrollbar etc should get recalucated
        void recalculateScroll();

        // Update the child position, so that it matches with the scollbar
        void updateChildPosition();

        // Move to left, right, top or bottom
        void scrollToLeft();
        void scrollToRight();
        void scrollToTop();
        void scrollToBottom();
    private:
        void correctScrollBarPosition();

        void handleChildScroll();

        virtual void childAdded() override;
        virtual void childRemoved() override;
    protected:
        // Special Events are Events like scrolling 
        // (which have a higher priorety then the child events)
        virtual bool handleEventCurrentBeforeChildren(sf::Event &event) override;
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt);
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
    private:
        void init();
    };
}

#endif // SCROLLABLEWIDGET_HPP
