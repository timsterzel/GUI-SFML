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
    public:
        typedef std::unique_ptr<ScrollableWidget> Ptr;
        static const float SCROLLBAR_THICKNESS;
    private:
        Widget *m_childWidget;
        // Store how much the children should by moved (scrolled) in the next
        // update step
        //float m_scrollOffsetX;
        //float m_scrollOffsetY;

        float m_scrollSpeed;

        sf::Color m_scrollBarColor;
        sf::Color m_scrollBtnColor;
        sf::Color m_scrollBtnSymbolColor;
        // Set by user (default: true)
        bool m_isVerticalScrollEnabled;
        bool m_isHorizontalScrollEnabled;
        // The thickness of the scrollbars. By Verticalscrollbar its the width and
        // by horizontal scrolling its the height
        float m_scrollbarThickness;

        // Scrollbar Vertical
        // Only scroll when there is a need to scrolling
        // (child is not shown fully in widget)
        MoveableBlock m_scrollUpBtn;
        MoveableBlock m_scrollDownBtn;
        sf::ConvexShape m_scrollUpBtnSymbol;
        sf::ConvexShape m_scrollDownBtnSymbol;
        bool m_isVerticalScrollNeeded;
        MoveableBlock m_scrollbarVertical;
        bool m_scrollbarVerMoveActive;
        sf::Vector2f m_scrollbarVerMoveModeRelPos;

        // Scrollbar Horizontal
        MoveableBlock m_scrollRightBtn;
        MoveableBlock m_scrollLeftBtn;
        sf::ConvexShape m_scrollRightBtnSymbol;
        sf::ConvexShape m_scrollLeftBtnSymbol;
        bool m_isHorizontalScrollNeeded;
        MoveableBlock m_scrollbarHorizontal;
        bool m_scrollbarHorMoveActive;
        sf::Vector2f m_scrollbarHorMoveModeRelPos;

        bool m_isVerticalScrollbarDrawn;
        bool m_isHorizontalScrollbarDrawn;
        // Listener are called when the state of the members m_isVerticalScrollNeeded
        // and m_isHorizontalScrollNeeded changed
        // First paremeter: Actual Widget
        // Second parameter: the new state of the isScrollNeeded member
        std::function<void(Widget*, bool)> m_onVerticalScrollNeededChangedListener;
        std::function<void(Widget*, bool)> m_onHorizontalScrollNeededChangedListener;

    public:
        static Ptr create();
        static Ptr create(float width, float height);
        ScrollableWidget();
        ScrollableWidget(float width, float height);
        
        // ScrollableWidget only can handle one widget, so we have to 
        // implement the methods different
        virtual void attachChild(Widget::Ptr child) override;

        float getScrollbarThickness() const;
        
        void setScrollBarColor(sf::Color color);
        sf::Color getScrollBarColor() const;
        void setScrollBtnColor(sf::Color color);
        sf::Color getScrollBtnColor() const;
        void setScrollBtnSymbolColor(sf::Color color);
        sf::Color getScrollBtnSymbolColor() const;

        void setIsVerticalScrollEnabled(bool isEnabled);
        bool isVerticalScrollEnabled() const;
        void setIsHorizontalScrollEnabled(bool isEnabled);
        bool isHorizontalScrollEnabled() const;

        void setIsVerticalScrollbarDrawn(bool isDrawn);
        void setIsHorizontalScrollbarDrawn(bool isDrawn);

        void setOnVerticalScrollNeededChangedListener(std::function
                <void(Widget*, bool)> listener);
        void setOnHorizontalScrollNeededChangedListener(std::function
                <void(Widget*, bool)> listener);

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
        void init();
        void createScrollbars();
        void createVerticalScrollbar();
        void createHorizontalScrollbar();
        sf::ConvexShape createBtnSymbol(sf::Vector2f pos, float rotation = 0.f) const;

        void correctScrollBarPosition();
        // Correct the position of the childs when there are out of the bounds 
        // and scrolling is needed
        void correctChildWidgetPosition();
        // Adjust the position of the scrollbar so that it matches the position of
        // the childwidget and vise versa
        void adjustVerticalScrollbarPosToChildWidgetPos();
        void adjustVerticalChildWidgetPosToScrollbarPos();
        void adjustHorizontalScrollbarPosToChildWidgetPos();
        void adjustHorizontalChildWidgetPosToScrollbarPos();
        
        virtual void childAdded(Widget &child) override;
        virtual void childRemoved() override;
    protected:
        virtual void boundsChanged() override;

        // Special Events are Events like scrolling 
        // (which have a higher priorety then the child events)
        virtual bool handleEventCurrentBeforeChildren(sf::Event &event) override;
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt);
        virtual void drawCurrentBeforeChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
    };
}

#endif // SCROLLABLEWIDGET_HPP
