#pragma once
#ifndef VERTICALLAYOUTWIDGET_HPP
#define VERTICALLAYOUTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widgets/Widget.hpp"

namespace gsf
{
    class VerticalLayoutWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<VerticalLayoutWidget> Ptr;
    private:
        // If its true the widht is calculated by the layout and is the maximal
        // width of its children
        bool m_autoDetermineWidth;
        bool m_autoDetermineHeight;
    public:
        static Ptr create();
        static Ptr create(float width, float height);
        VerticalLayoutWidget();
        VerticalLayoutWidget(float width, float height);

        virtual void attachChild(Widget::Ptr child) override;
        virtual Widget::Ptr detachChild(const Widget& node);

        void enableAutoDetermineWidth();
        void disableAutoDetermineWidth();
        void enableAutoDetermineHeight();
        void disableAutoDetermineHeight();
    protected:
        virtual void loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes) override;
    
    private:
        void init();
        // Calculate the size of the current View
        virtual void calculateSize() override;
        virtual void arrangeChildren() override;

        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    };
}

#endif // VERTICALLAYOUT_HPP
