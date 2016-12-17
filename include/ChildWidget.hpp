#ifndef CHILDWIDGET_HPP
#define CHILDWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"

namespace gsf
{
    class ChildWidget: public gsf::Widget
    {
        protected:
            std::vector<Ptr> m_children;
        public:
            ChildWidget();
            ChildWidget(float width, float height);
            virtual ~ChildWidget();

            void attachChild(Ptr child);
            Widget::Ptr detachChild(const Widget& node);

            // dt is the delta time
            void update(float dt);

            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const override;

        protected:

            virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
            void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

            // Returns true if widget has handled the event and children dont have to handle it
            bool handleEvent(sf::Event &event) override;
            // Special Events are Events like scrolling (which have a higher priorety then the child events)
            virtual bool handleSpecialEvents(sf::Event &event);

            virtual bool handleEventCurrent(sf::Event &event);

            virtual bool handleEventChildren(sf::Event &event);
        private:

            virtual void updateCurrent(float dt);
            void updateChildren(float dt);

            // Calculate the size of the current Widget
            virtual void calculateSize() override;
            // Place Children in this Widget
            virtual void arrangeChildren();
            // Things which should get done when a child was added
            virtual void childAdded();
            // Things which should get done when a child was removed
            virtual void childRemoved();
    };

}

#endif // CHILDWIDGET_HPP
