#pragma once
#ifndef VERTICALLAYOUT_HPP
#define VERTICALLAYOUT_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widget.hpp"

namespace gsf
{
    class VerticalLayout: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<VerticalLayout> Ptr;
    public:
        static Ptr create();
        static Ptr create(float width, float height);
        VerticalLayout();
        VerticalLayout(float width, float height);

        virtual void attachChild(Widget::Ptr child) override;
        virtual Widget::Ptr detachChild(const Widget& node);
    private:
        // Calculate the size of the current View
        virtual void calculateSize() override;
        virtual void arrangeChildren() override;

        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    };
}

#endif // VERTICALLAYOUT_HPP
