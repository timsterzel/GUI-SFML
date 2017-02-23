#pragma once
#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class ButtonWidget: public gsf::Widget
    {
    protected:
        // True when mouse hover over button
        bool m_isHovering;
    private:
        // The color of the widget when mouse hover over button
        sf::Color m_hoverFillColor;
    public:
        ButtonWidget();
        ButtonWidget(float width, float height);

        sf::Color getHoverFillColor() const;
        void setHoverFillColor(sf::Color color);

        sf::Color getHoverTextColor() const;
        void setHoverTextColor(sf::Color color);
    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
    private:
        void init();
    };
}

#endif // !BUTTONWIDGET_HPP
