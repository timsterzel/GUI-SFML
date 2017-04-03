#include "../../include/Widgets/HorizontalLayoutWidget.hpp"
#include "../../include/Utility.hpp"
#include <iostream>

gsf::HorizontalLayoutWidget::Ptr gsf::HorizontalLayoutWidget::create()
{
    Ptr widget{ std::make_unique<HorizontalLayoutWidget>() };
    return widget;
}

gsf::HorizontalLayoutWidget::Ptr gsf::HorizontalLayoutWidget::create(float width, float height)
{
    Ptr widget{ std::make_unique<HorizontalLayoutWidget>(width, height) };
    return widget;
}

gsf::HorizontalLayoutWidget::HorizontalLayoutWidget()
: Widget{  }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

gsf::HorizontalLayoutWidget::HorizontalLayoutWidget(float width, float height)
: Widget{ width, height }
, m_autoDetermineWidth{ true }
, m_autoDetermineHeight{ true }
{
    init();
}

void gsf::HorizontalLayoutWidget::init()
{

}

void gsf::HorizontalLayoutWidget::loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes)
{
    Widget::loadAttributes(document, attributes);
    Widget::loadAttributes(document, attributes, "HorizontalLayoutWidget");
}

void gsf::HorizontalLayoutWidget::applyAttribute(const std::string &name, 
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

void gsf::HorizontalLayoutWidget::setAutoDetermineWidth(bool autoDetermine)
{
    m_autoDetermineWidth = autoDetermine;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::setAutoDetermineHeight(bool autoDetermine)
{
    m_autoDetermineHeight = autoDetermine;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::enableAutoDetermineWidth()
{
    m_autoDetermineWidth = true;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::disableAutoDetermineWidth()
{
    m_autoDetermineWidth = false;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::enableAutoDetermineHeight()
{
    m_autoDetermineHeight = true;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::disableAutoDetermineHeight()
{
    m_autoDetermineHeight = false;
    calculateSize();
}

void gsf::HorizontalLayoutWidget::calculateSize()
{
    if (!m_autoDetermineHeight && !m_autoDetermineWidth)
    {
        return;
    }
    float height{ 0.f };
    float width{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        width += child->getLocalBounds().width;
        
        float childHeight{ child->getLocalBounds().height };
        if (childHeight > height)
        {
            height = childHeight;
        }
    }
    if (m_autoDetermineHeight)
    {
        setHeight(height);
    }
    if (m_autoDetermineWidth)
    {
        setWidth(width);
    }   
}

void gsf::HorizontalLayoutWidget::arrangeChildren()
{
    float distance{ 0.f };
    for (const Widget::Ptr &child : m_children)
    {
        child->setTopPosition(0.f);
        child->setLeftPosition(distance);
        distance += child->getLocalBounds().width;
    }
    calculateSize();
}

bool gsf::HorizontalLayoutWidget::handleEventCurrentAfterChildren(sf::Event &event,
        const sf::RenderTarget &target)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event, target) };
    return handled;
}

void gsf::HorizontalLayoutWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::HorizontalLayoutWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}
