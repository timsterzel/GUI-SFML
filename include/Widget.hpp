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
            /*
            enum class Orientation
            {
                Left,
                Right,
                Top,
                Down,
                Center
            };
            */

        protected:
            float m_width;
            float m_height;

            sf::Color m_outlineColor;
            float m_outlineThickness;
            sf::Color m_bgColor;
            // A parent can have a parent, e.g. when it is added to a widget of type childWidget
            Widget *m_parent;
            // If this is true, widget should be draw at the foreground
            // This is eg useful for windows
            bool m_moveToForeground;
            // When it is true the widget signals that it can get removed next time
            bool m_isRemoveable;
            // Only render window when it is visible
            bool m_isVisible;

            std::vector<Ptr> m_children;

            std::function<void(Widget*, sf::Vector2f)> m_onLeftClickListener;
            std::function<void(Widget*, sf::Vector2f)> m_onRightClickListener;
            std::function<void(Widget*, sf::Vector2f)> m_onMiddleClickListener;
        public:
            Widget();
            Widget(float width, float height);
            virtual ~Widget();


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

            void setOnLeftClickListener(std::function<void(Widget *widget, 
                        sf::Vector2f)> onLeftClickListener);
            void setOnRightClickListener(std::function<void(Widget *widget, 
                        sf::Vector2f)> onLeftClickListener);
            void setOnMiddleClickListener(std::function<void(Widget *widget, 
                        sf::Vector2f)> onLeftClickListener);
            
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
            // Same as getGlobalBounds, but with local coordinates for left and top
            sf::FloatRect getLocalBounds() const;

            void setBackgroundColor(const sf::Color color);
            sf::Color getBackgroundColor() const;

            void centerOrigin();

            // dt is the delta time
            virtual void update(float dt);
            //void onCommand(const Command &command, float dt);
            // Get absolute world transform
            sf::Transform getWorldTransform() const;
            // Get absolute position in world
            sf::Vector2f getWorldPosition() const;

            //bool isActive() const;
            //void setIsActive(bool isActive);

            bool isIntersecting(sf::Vector2f pos) const;

            virtual void draw(sf::RenderTarget &target, 
                    sf::RenderStates states) const final override;
            // Returns true if widget has handled the event and children dont 
            // have to handle it
            bool handleEventWidget(sf::Event &event);

        protected:

            // Returns true if widget has handled the event and children dont have 
            // to handle it
            virtual bool handleEvent(sf::Event &event);

            // Get the shown area of the widget. The Shown area is the width and 
            // height of the widget,
            // with left and top coordinates (top-left corner), but is affected by 
            // the values of its parent too. The final shown area is the overlapping
            // area off the widget and all its parents
            sf::FloatRect getShownArea() const;
            // Returns a view in which only the shown area of the widget is shown 
            // by drawing
            sf::View getShownAreaView(sf::RenderTarget &target) const;
            
            // Is called when the bounds of the widget changes (e.g. width, height
            // outlineThickness) so necessary things can get changed    
            virtual void boundsChanged();

        private:
            virtual void drawWidget(sf::RenderTarget &target, 
                    sf::RenderStates states) const;

            // Calculate the size of the current widget
            virtual void calculateSize();
    };
}

#endif // WIDGET_HPP
