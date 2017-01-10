#include "ProgressWidget.hpp"
#include <iostream>

gsf::ProgressWidget::ProgressWidget()
{

}

gsf::ProgressWidget::~ProgressWidget()
{

}

void gsf::ProgressWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // Draw text
    //target.draw(m_text, states);
}

void gsf::ProgressWidget::update(float dt)
{
    // Do nothing by default
}

bool gsf::ProgressWidget::handleEvent(sf::Event &event)
{
    bool handled = Widget::handleEvent(event);
    return handled;
}
