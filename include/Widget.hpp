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
            sf::Color m_bgColor;
            Widget *m_parent;
            // If this is true, widget should be draw at the foreground
            // This is eg useful for windows
            bool m_moveToForeground;
            // When it is true the widget signals that it can get removed next time
            bool m_removeNext;
            // Only render window when it is visible
            bool m_isVisible;

            std::vector<Ptr> m_children;

            std::function<void(Widget*, sf::Vector2f)> m_onLeftClickListener;

        public:
            Widget();
            Widget(float width, float height);
            virtual ~Widget();

            void setParent(Widget *parent);
            Widget* getParent() const;

            void setMoveToForground(bool moveToForeground);
            bool isMarkedForMoveToForeground() const;

            void setIsVisible(bool isVisible);
            bool isVisible() const;

            void setOnLeftClickListener(std::function<void(Widget *widget, sf::Vector2f)> onLeftClickListener);

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

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final override;
            // Returns true if widget has handled the event and children dont have to handle it
            bool handleEventWidget(sf::Event &event);

        protected:

            // Returns true if widget has handled the event and children dont have to handle it
            virtual bool handleEvent(sf::Event &event);

        private:
            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const;

            // Calculate the size of the current widget
            virtual void calculateSize();


    };

}

#endif // WIDGET_HPP
