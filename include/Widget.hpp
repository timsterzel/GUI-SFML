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

        protected:
        //bool m_isCollisionCheckOn;

        private:
            std::vector<Ptr> m_children;
            Widget *m_parent;


        public:
            Widget();
            virtual ~Widget();

            void attachChild(Ptr child);
            Ptr detachChild(const Widget& node);

            // dt is the delta time
            void update(float dt);
            //void onCommand(const Command &command, float dt);
            // Get absolute world transform
            sf::Transform getWorldTransform() const;
            // Get absolute position in world
            sf::Vector2f getWorldPosition() const;

            bool isActive() const;
            void setIsActive(bool isActive);

            // draw should not get overridden
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;

        private:

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
            void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

            virtual void updateCurrent(float dt);
            void updateChildren(float dt);
    };

}

#endif // WIDGET_HPP
