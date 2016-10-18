#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>

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
            std::vector<Ptr> m_children;
            Widget *m_parent;

        public:
            Widget();
            Widget(float width, float height);
            virtual ~Widget();

            void attachChild(Ptr child);
            Ptr detachChild(const Widget& node);

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
            void update(float dt);
            //void onCommand(const Command &command, float dt);
            // Get absolute world transform
            sf::Transform getWorldTransform() const;
            // Get absolute position in world
            sf::Vector2f getWorldPosition() const;

            //bool isActive() const;
            //void setIsActive(bool isActive);

            bool isIntersecting(sf::Vector2f pos) const;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            // Returns true if widget has handled the event and children dont have to handle it
            bool handleEvent(sf::Event &event);

        private:

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
            void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);
            void updateChildren(float dt);

            bool handleEventChildren(sf::Event &event);
            virtual bool handleEventCurrent(sf::Event &event);

            // Calculate the size of the current Widget
            virtual void calculateSize();
            // Place Children in this Widget
            virtual void arrangeChildren();
    };

}

#endif // WIDGET_HPP
