#include "GUIEnvironment.hpp"
#include <iostream>
#include <cassert>

gsf::GUIEnvironment::GUIEnvironment()
: m_isMouseInWindow{ true }
, m_isWindowFocused{ true }
//, m_isWindowRoughOutEnabled{ false }
{

}

gsf::GUIEnvironment::~GUIEnvironment()
{

}

void gsf::GUIEnvironment::addWidget(Widget::Ptr widget)
{
    m_widgets.push_back(std::move(widget));
}

/*
void gsf::GUIEnvironment::setIsWindowRoughOutEnabled(bool isEnabled)
{
    m_isWindowRoughOutEnabled = isEnabled;
}

bool gsf::GUIEnvironment::isWindowRoughOutEnabled() const
{
    return m_isWindowRoughOutEnabled;
}
*/

gsf::Widget::Ptr gsf::GUIEnvironment::removeWidget(const Widget& widget)
{
    auto found = std::find_if(m_widgets.begin(), m_widgets.end(), 
            [&] (Widget::Ptr &p) -> bool { return p.get() == &widget; });
    // There is an error when we try to detach a widget which does not exists, 
    // so stop execution in debug mode
    assert(found != m_widgets.end());

    Widget::Ptr result = std::move(*found);
    m_widgets.erase(found);
    return result;
}

void gsf::GUIEnvironment::draw(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    for (const Widget::Ptr &widget : m_widgets)
    {
        widget->draw(target, states);
    }
}

void gsf::GUIEnvironment::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::MouseLeft || event.type == sf::Event::LostFocus)
    {
        m_isMouseInWindow = false;
    }
    else if(event.type == sf::Event::MouseEntered)
    {
        m_isMouseInWindow = true;
    }
    if (event.type == sf::Event::LostFocus)
    {
       m_isWindowFocused = false;
    }
    if (event.type == sf::Event::GainedFocus)
    {
        m_isWindowFocused = true;
    }

    // Dont handle mouse move events when mouse is not inside window or 
    // window is not focussed
    
    if (event.type == sf::Event::MouseMoved && 
            (!m_isMouseInWindow || !m_isWindowFocused))
    {
        return;
    }

    // Iterate backwards, because the widgets which are shown at the front of the window
    // have a higher priority forevent handling
    // (Widgets drawn at the front are the ones which are at the end of the vector)
    for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++)
    {
        if ((*it)->handleEventWidget(event))
        {
            // Event handled so we have nothing to handly anymore.
            // So we can ensure that a event is handled by the window in the front
            // and not affect a window behind it.
            break;
        }
    }

}

void gsf::GUIEnvironment::update(float dt)
{
    for (const Widget::Ptr &widget : m_widgets)
    {
        widget->update(dt);
    }
    // Move widget to foreground which are marked for this
    // (Forground at the window, which is the last item in our vector)
    bool moved{ false };
    do
    {
        moved = false;
        for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
        {
            if ((*it)->isMarkedForMoveToForeground()) {
                (*it)->setMoveToForground(false);
                // Move actual object to end of vector
                std::rotate(it, it + 1 , m_widgets.end());
                // Leave actual loop and start again from beginning, 
                // because vector has changed
                moved = true;
                break;
            }
        }
    } while (moved);
    // Remove widgets which signals that there are removeable
    m_widgets.erase(std::remove_if(m_widgets.begin(), m_widgets.end(),
                    [] (Widget::Ptr &widget) { return widget->isRemoveable(); }),
                    m_widgets.end());
}
