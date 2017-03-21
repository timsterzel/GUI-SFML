#pragma once
#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "libs/tinyxml2.h"

namespace gsf
{
    class GUIEnvironment;
}

namespace gsf
{
    class Widget: protected sf::Transformable
    {
    public:
        typedef std::unique_ptr<Widget> Ptr;
        typedef std::pair<Widget*, Widget*> Pair;
    protected:

        gsf::GUIEnvironment *m_context;
        // All xml attributes (also the one of child classes) are stored here
        std::map<std::string, std::string> m_xmlAttributes;
        // The loaded theme as xml document
        tinyxml2::XMLDocument m_theme;
        // The orientation of the Widget. If a Orientation is set, a given position
        // is perhaps ignored. Not all orientations have an effect on all widgets and
        // not all orientations can get combined. (E.g. Left and Right or 
        // Top and Bottom are conflicting)
        int m_orientation;
        // The area of the content. That is the area where child widgets are drawn too
        sf::FloatRect m_contentArea;
        // The full area of the widget without the outline. By default ist the same as
        // the contentArea but in some widgets it can differ (E.g. a WindowWidget has
        // a topbar, but child widgets are only drawn in the contentArea)
        sf::FloatRect m_fullArea;


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
        static const std::map<std::string, std::string> ThemeAttributes;
    public:
        static Ptr create(bool isWindowWidget = false, 
                std::string themePath = "");
        static Ptr create(float width, float height, bool isWindowWidget = false, 
                std::string themePath = "");
        
        Widget(bool isWindowWidget = false, std::string themePath = "");
        Widget(float width, float height, bool isWindowWidget = false, 
                std::string themePath = "");

        void setContext(GUIEnvironment *context);
        void removeContext();
        gsf::GUIEnvironment* getContext() const;
        // Override some methods of sf::Transformable class, so there are accessible
        // from outside the class
        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f &position);    
        const sf::Vector2f& getPosition() const;
        
        // Place the widget so that the left side is on the given pos
        void setLeftPosition(float pos);
        // Place the widget so that the right side is on the given pos
        void setRightPosition(float pos);
        // Place the widget so that the top side is on the given pos
        void setTopPosition(float pos);
        // Place the widget so that the bottomside is on the given pos
        void setBottomPosition(float pos);
        // Place the widget so that the horizontal center is on the given pos
        void setHorizontalCenterPosition(float pos);
        // Place the widget so that the vertical center is on the given pos
        void setVerticalCenterPosition(float pos);
        // Place the widget so that the center is on the given pos
        void setCenterPosition(float x, float y);
        // The orientation of the Widget. If a Orientation is set, a given position
        // is perhaps ignored. Not all orientations have an effect on all widgets and
        // not all orientations can get combined. (E.g. Left and Right or 
        // Top and Bottom are conflicting)
        void setOrientation(int orientation);
        int getOrientation() const;
        
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f &origin);
        const sf::Vector2f& getOrigin() const;
        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f &offset);

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

        void setOnLeftClickListener(std::function<void(Widget*, 
                    sf::Vector2f)> listener);
        void setOnRightClickListener(std::function<void(Widget*, 
                    sf::Vector2f)> listener);
        void setOnMiddleClickListener(std::function<void(Widget*, 
                    sf::Vector2f)> listener);
            
        void setWidth(const float width);
        float getWidth() const;
        void setHeight(const float height);
        float getHeight() const;
        // The bounds of the content area
        float getLeft() const;
        float getRight() const;
        float getTop() const;
        float getBottom() const;
        float getWorldLeft() const;
        float getWorldRight() const;
        float getWorldTop() const;
        float getWorldBottom() const;
        // The real bounds with outline
        float getRealLeft() const;
        float getRealRight() const;
        float getRealTop() const;
        float getRealBottom() const;
        float getWorldRealLeft() const;
        float getWorldRealRight() const;
        float getWorldRealTop() const;
        float getWorldRealBottom() const;
        // The global bounds of the widget. Here the outline thickniss is in the
        // bounds. So the width and height can has higher values then the 
        // widgets height and width
        sf::FloatRect getGlobalBounds() const;
        sf::FloatRect getLocalBounds() const;
        // The total bounds without the outline
        sf::FloatRect getGlobalBoundsWithoutOutline() const;
        sf::FloatRect getLocalBoundsWithoutOutline() const;
        // The bounds of the content area(This is he area where child widget
        // content is drawn)
        sf::FloatRect getGlobalContentBounds() const;
        sf::FloatRect getLocalContentBounds() const;
        
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
        // Place child widgets by there orientation
        void placeChildWidgets();

        // Load theme attributes and apply them
        void applyTheme(const std::string &path);
        // Returns true if widget has handled the event and children dont 
        // have to handle it
        bool handleEvent(sf::Event &event, const sf::RenderTarget &target);
        // dt is the delta time
        virtual void update(float dt);
               
        //virtual void draw(sf::RenderTarget &target, 
        //        sf::RenderStates states) const final override;
        // The draw method needs the default view of the window, so we can
        // calculate the proportion of custom views correct later
        void draw(sf::RenderTarget &target, 
            sf::RenderStates states, sf::View defaultView) const;
    protected:
        virtual void attachChild(Ptr child);
        virtual Widget::Ptr detachChild(const Widget& node);
        
        // Called when a context was set
        virtual void contextSet();
        // Called when the context was removed
        virtual void contextRemoved();

        sf::Vector2f convertToLocalPoint(sf::Vector2f globalPoint) const;

        sf::FloatRect getFullAreaRect() const;
        // The view which result in the parent area and the actual area
        sf::FloatRect getOverlappingArea(sf::FloatRect rectThis, 
                sf::FloatRect rectParent) const;
        // Creates a view which only shows the given rect area
        sf::View createViewFromRect(sf::FloatRect rect, 
                sf::RenderTarget &target, sf::View defaultView) const;

        // Get the shown area of the widget. The Shown area is the width and 
        // height of the widget,
        // with left and top coordinates (top-left corner), but is affected by 
        // the values of its parent too. The final shown area is the overlapping
        // area off the widget and all its parents
        sf::FloatRect getShownArea() const;
        sf::FloatRect getContentShownArea() const;

        // The shown area with the outline 
        sf::View getShownAreaView(sf::RenderTarget &target, 
                sf::View defaultView) const;
        // The shown of the content. This is only the area where child widgets 
        // are shown
        sf::View getContentShownAreaView(sf::RenderTarget &target, 
                sf::View defaultView) const;
        // Load the attributes of the given element from m_theme xml file and 
        // store them in m_xmlAttributes
        void loadAttributes(const std::string &widgetName);
        // Apply the attribute data which are stored in m_xmlAttributes.
        // Widgets which have own stylings should override this one and apply them.
        // Its important to call its parent class method, when there is one, so all 
        // styling stages where run through
        virtual void applyAttributes();
        // Is called when the bounds of the widget changes (e.g. width, height
        // outlineThickness) so necessary things can get changed
        virtual void boundsChanged();
        
        virtual void placeChildWidget(Widget *widget);

        virtual bool handleEventCurrentBeforeChildren(sf::Event &event, 
                const sf::RenderTarget &target);
        virtual bool handleEventChildren(sf::Event &event, 
                const sf::RenderTarget &target);
        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target);
        
        virtual void updateCurrentBeforeChildren(float dt);
        virtual void updateChildren(float dt);
        virtual void updateCurrentAfterChildren(float dt);
        
        virtual void drawCurrentBeforeChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const;
        virtual void drawChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const;
    private:  
        void init(const std::string &themePath);
        // Load the theme file and store it in m_theme
        void loadThemeFile(const std::string &themePath);
        //virtual void draw(sf::RenderTarget &target, 
               // sf::RenderStates states) const final override;

        // Calculate the size of the current widget
        virtual void calculateSize();

        // Place Children in this Widget
        virtual void arrangeChildren();
        // Things which should get done when a child was added
        virtual void childAdded(Widget &child);
        // Things which should get done when a child was removed
        virtual void childRemoved();
    };
}

#endif // WIDGET_HPP
