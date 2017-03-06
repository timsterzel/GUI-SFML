#pragma once
#ifndef COMBOBOXWIDGET_HPP
#define COMBOBOXWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"

namespace gsf
{
    class ComboBoxWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<ComboBoxWidget> Ptr;
    public:
        static Ptr create();
        static Ptr create(float width, float height);
        ComboBoxWidget();
        ComboBoxWidget(float width, float height);

    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentBeforeChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    private:
        void init();
    };
}

#endif // !COMBOBOXWIDGET_HPP
