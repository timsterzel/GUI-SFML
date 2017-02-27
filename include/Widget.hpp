#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>
#include <functional>

namespace gsf
{
    class Widget: public sf::Transformable, public sf::Drawable
    {
    public:
        typedef std::unique_ptr<Widget> Ptr;
        typedef std::pair<Widget*, Widget*> Pair;

    protected:
        // The width and height is the size of the "content" the real
        // size can differ. (E.g. a window have a topbar or there can be a outline)
        float m_width;
        float m_height;

        std::vector<Ptr> m_children;
        
        sf::Color m_outlineColor;
        float m_outlineThickness;
        sf::Color m_bgColor;
        // A parent can have a parent, e.g. when it is added to a widget of type
        // childWidget
        Widget *m_parent;
        // If this is true, widget should be draw at the foreground
        // This is eg useful for windows
        bool m_moveToForeground;
        // When it is true the widget signals that it can get removed next time
        bool m_isRemoveable;
        // Only render window when it is visible
        bool m_isVisible;

        std::function<void(Widget*, sf::Vector2f)> m_onLeftClickListener;
        std::function<void(Widget*, sf::Vector2f)> m_onRightClickListener;
        std::function<void(Widget*, sf::Vector2f)> m_onMiddleClickListener;
    private:
        // Window Widgets are special, so we store the information if
        // the widget is a window here
        bool m_isWindowWidget;
        
    public:
        Widget(bool isWindowWidget = false);
        Widget(float width, float height, bool isWindowWidget = false);
        
        virtual void attachChild(Ptr child);
        Widget::Ptr detachChild(const Widget& node);
        
        sf::Color getOutlineColor() const;
        void setOutlineColor(sf::Color color);
        float getOutlineThickness() const;
        void setOutlineThickness(float outline);
            
        void setParent(Widget *parent);
        Widget* getParent() const;

        void setMoveToForground(bool moveToForeground);
        bool isMarkedForMoveToForeground() const;

        void setIsRemoveable(bool isRemoveable);
        bool isRemoveable() const;

        void setIsVisible(bool isVisible);
        bool isVisible() const;
            
        bool isWindowWidget() const;

        void setOnLeftClickListener(std::function<void(Widget *widget, 
                    sf::Vector2f)> listener);
        void setOnRightClickListener(std::function<void(Widget *widget, 
                    sf::Vector2f)> listener);
        void setOnMiddleClickListener(std::function<void(Widget *widget, 
                    sf::Vector2f)> listener);
            
        void setWidth(const float width);
        float getWidth() const;
        void setHeight(const float height);
        float getHeight() const;

        float getLeft() const;
        float getRight() const;
        float getTop() const;
        float getBottom() const;
        float getWorldLeft() const;
        float getWorldRight() const;
        float getWorldTop() const;
        float getWorldBottom() const;
            
        // The global bounds of the widget. Here the outline thickniss is in the
        // bounds. So the width and height can has higher values then the 
        // widgets height and width
        sf::FloatRect getGlobalBounds() const;
        sf::FloatRect getLocalBounds() const;
        // The total bounds without the outline
        sf::FloatRect getGlobalBoundsWithoutOutline() const;
        virtual sf::FloatRect getLocalBoundsWithoutOutline() const;
        // The bounds of the content area(This is he area where child widget
        // content is drawn)
        sf::FloatRect getGlobalContentBounds() const;
        virtual sf::FloatRect getLocalContentBounds() const;
        
        void setBackgroundColor(const sf::Color color);
        sf::Color getBackgroundColor() const;

        void centerOrigin();

        //void onCommand(const Command &command, float dt);
        // Get absolute world transform
        sf::Transform getWorldTransform() const;
        // Get absolute position in world
        sf::Vector2f getWorldPosition() const;

        //bool isActive() const;
        //void setIsActive(bool isActive);

        bool isIntersecting(sf::Vector2f pos) const;

        // Returns true if widget has handled the event and children dont 
        // have to handle it
        bool handleEvent(sf::Event &event);
        // dt is the delta time
        virtual void update(float dt);
        
        virtual void draw(sf::RenderTarget &target, 
                sf::RenderStates states) const final override;

    protected:
        // The view which result in the parent area and the actual area
        sf::FloatRect getOverlappingArea(sf::FloatRect rectThis, 
                sf::FloatRect rectParent) const;
        // Creates a view which only shows the given rect area
        sf::View createViewFromRect(sf::FloatRect rect, 
                sf::RenderTarget &target) const;

        // Get the shown area of the widget. The Shown area is the width and 
        // height of the widget,
        // with left and top coordinates (top-left corner), but is affected by 
        // the values of its parent too. The final shown area is the overlapping
        // area off the widget and all its parents
        sf::FloatRect getShownArea() const;
        // Returns a view in which only the shown area of the widget is shown 
        // by drawing. This includes the outline
        //sf::View getOutlineShownAreaView(sf::RenderTarget &target) const;
        sf::FloatRect getShownAreaWithoutOutline() const;
        sf::FloatRect getContentShownArea() const;

        // The shown area with the outline 
        sf::View getShownAreaView(sf::RenderTarget &target) const;
        // The shown area without the outline
        sf::View getShownAreaViewWithoutOutline(sf::RenderTarget &target) const;
        // The shown of the content. This is only the area where child widgets 
        // are shown
        sf::View getContentShownAreaView(sf::RenderTarget &target) const;
        
        // Is called when the bounds of the widget changes (e.g. width, height
        // outlineThickness) so necessary things can get changed
        virtual void boundsChanged();
        
        virtual bool handleEventCurrentBeforeChildren(sf::Event &event);
        virtual bool handleEventChildren(sf::Event &event);
        virtual bool handleEventCurrentAfterChildren(sf::Event &event);
        
        virtual void updateCurrentBeforeChildren(float dt);
        virtual void updateChildren(float dt);
        virtual void updateCurrentAfterChildren(float dt);
        
        virtual void drawCurrentBeforeChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const;
        virtual void drawChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const;
    private:

        // Calculate the size of the current widget
        virtual void calculateSize();

        // Place Children in this Widget
        virtual void arrangeChildren();
        // Things which should get done when a child was added
        virtual void childAdded();
        // Things which should get done when a child was removed
        virtual void childRemoved();
    };
}

#endif // WIDGET_HPP
