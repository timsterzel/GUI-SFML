#include "ComboBoxWidget.hpp"
#include <iostream>

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create()
{
    Ptr widget{ std::make_unique<ComboBoxWidget>() };
    return std::move(widget);
}

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create(float width, float height)
{
    Ptr widget{ std::make_unique<ComboBoxWidget>(width, height) };
    return std::move(widget);
}

gsf::ComboBoxWidget::ComboBoxWidget()
: Widget{  }
{
    init();
}

gsf::ComboBoxWidget::ComboBoxWidget(float width, float height)
: Widget{ width, height }
{
    init();
}


void gsf::ComboBoxWidget::init()
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
}

bool gsf::ComboBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    bool handled = Widget::handleEventCurrentAfterChildren(event, target);
    if (event.type == sf::Event::MouseMoved)
    {

        sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseMove.x, 
            event.mouseMove.y }) };
        bool intersects{ isIntersecting(mousePos) };
        bool isInShownArea{ getShownArea().contains(mousePos) };
    }
    return handled;
}

void gsf::ComboBoxWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ComboBoxWidget::drawCurrentBeforeChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{

}
