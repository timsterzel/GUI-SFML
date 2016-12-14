#include "GUISFMLEnvironment.hpp"
#include <iostream>
#include <cassert>

gsf::GUISFMLEnvironment::GUISFMLEnvironment()
{

}

gsf::GUISFMLEnvironment::~GUISFMLEnvironment()
{

}

void gsf::GUISFMLEnvironment::addWidget(Widget::Ptr widget)
{
    m_widgets.push_back(std::move(widget));
}

gsf::Widget::Ptr gsf::GUISFMLEnvironment::removeWidget(const Widget& widget)
{
    auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&] (Widget::Ptr &p) -> bool { return p.get() == &widget; });
    // There is an error when we try to detach a widget which does not exists,so stop execution in debug mode
    assert(found != m_widgets.end());

    Widget::Ptr result = std::move(*found);
    m_widgets.erase(found);
    return result;
}

void gsf::GUISFMLEnvironment::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const Widget::Ptr &widget : m_widgets)
    {
        widget->draw(target, states);
    }
}

void gsf::GUISFMLEnvironment::handleEvent(sf::Event &event)
{
    for (const Widget::Ptr &widget : m_widgets)
    {
        widget->handleEvent(event);
    }
}

void gsf::GUISFMLEnvironment::update(float dt)
{
    for (const Widget::Ptr &widget : m_widgets)
    {
        widget->update(dt);
    }
    // Move widget to foreground which are marked for this
    // (Forground at the window, which is the last item in our vector)
    bool moved = false;
    do
    {
        moved = false;
        for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
        {
            if ((*it)->isMarkedForMoveToForeground()) {
                (*it)->setMoveToForground(false);
                // Move actual object to end of vector
                std::rotate(it, it + 1 , m_widgets.end());
                // Leave actual loop and start again from beginning, because vector has changed
                moved = true;
                break;
            }
        }
    } while (moved);
}
