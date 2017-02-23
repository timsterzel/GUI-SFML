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
        VerticalLayout();
        VerticalLayout(float width, float height);
    private:
        // Calculate the size of the current View
        virtual void calculateSize() override;
        virtual void arrangeChildren() override;

        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren
            (sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif // VERTICALLAYOUT_HPP
