#include "Widgets/VerticalLayoutWidget.hpp"
#include "Utility.hpp"
#include <iostream>

gsf::VerticalLayoutWidget::Ptr gsf::VerticalLayoutWidget::create()
{
    Ptr widget{ std::make_unique<VerticalLayoutWidget>() };
    return widget;
}

gsf::VerticalLayoutWidget::Ptr gsf::VerticalLayoutWidget::create(float width, float height)
{
    Ptr widget{ std::make_unique<VerticalLayoutWidget>(width, height) };
    return widget;
}

gsf::VerticalLayoutWidget::VerticalLayoutWidget()
: Widget{  }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

gsf::VerticalLayoutWidget::VerticalLayoutWidget(float width, float height)
: Widget{ width, height }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

void gsf::VerticalLayoutWidget::init()
{

}

void gsf::VerticalLayoutWidget::loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes)
{
    Widget::loadAttributes(document, attributes);
    Widget::loadAttributes(document, attributes, "VerticalLayoutWidget");
}

void gsf::VerticalLayoutWidget::applyAttribute(const std::string &name, 
        const std::string &value)
{
    Widget::applyAttribute(name, value);
    if (name == "autoDetermineWidth")
    {
        bool val{ Utility::stringToBool(value) };
        setAutoDetermineWidth(val);
    }
    else if(name == "autoDetermineHeight")
    {
        bool val{ Utility::stringToBool(value) };
        setAutoDetermineHeight(val);
    }
}

void gsf::VerticalLayoutWidget::setAutoDetermineWidth(bool autoDetermine)
{
    m_autoDetermineWidth = autoDetermine;
}

void gsf::VerticalLayoutWidget::setAutoDetermineHeight(bool autoDetermine)
{
    m_autoDetermineHeight = autoDetermine;
}

void gsf::VerticalLayoutWidget::enableAutoDetermineWidth()
{
    m_autoDetermineWidth = true;
}

void gsf::VerticalLayoutWidget::disableAutoDetermineWidth()
{
    m_autoDetermineWidth = false;
}

void gsf::VerticalLayoutWidget::enableAutoDetermineHeight()
{
    m_autoDetermineHeight = true;
}

void gsf::VerticalLayoutWidget::disableAutoDetermineHeight()
{
    m_autoDetermineHeight = false;
}

void gsf::VerticalLayoutWidget::calculateSize()
{    
    if (!m_autoDetermineHeight && !m_autoDetermineWidth)
    {
        return;
    }
    float height{ 0.f };
    float width{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        height += child->getLocalBounds().height;
        float childWidth{ child->getLocalBounds().width };
        if (childWidth > width)
        {
            width = childWidth;
        }
    }
    if (m_autoDetermineHeight)
    {
        if (getID() == "vertWidget_vl1")
            std::cout << "Auto Det height is true\n";
        
        setHeight(height);
    }
    if (m_autoDetermineWidth)
    {
        setWidth(width);
    }   
}

void gsf::VerticalLayoutWidget::arrangeChildren()
{
    float distance{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        // Its important to add the outline thickness to the position so the whole
        // widget is visible
        child->setPosition(0.f + child->getOrigin().x + child->getOutlineThickness(), 
                distance + child->getOrigin().y + child->getOutlineThickness());
        distance += child->getLocalBounds().height;
    }
    calculateSize();
}

bool gsf::VerticalLayoutWidget::handleEventCurrentAfterChildren(sf::Event &event,
        const sf::RenderTarget &target)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event, target) };
    return handled;
}

void gsf::VerticalLayoutWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::VerticalLayoutWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}
