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
    // There is an error when we try to detach a child which does not exists,so stop execution in debug mode
    assert(found != m_widgets.end());

    Widget::Ptr result = std::move(*found);
    m_widgets.erase(found);
    return result;
}

void gsf::GUISFMLEnvironment::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void gsf::GUISFMLEnvironment::handleEvents(sf::Event &event)
{

}

void gsf::GUISFMLEnvironment::update(float dt)
{

}
