#include "Widgets/CheckBoxWidget.hpp"
#include <iostream>

gsf::CheckBoxWidget::Ptr gsf::CheckBoxWidget::create()
{
    Ptr widget{ std::make_unique<CheckBoxWidget>() };
    return std::move(widget);
}

gsf::CheckBoxWidget::Ptr gsf::CheckBoxWidget::create(float width, float height)
{
    Ptr widget{ std::make_unique<CheckBoxWidget>(width, height) };
    return std::move(widget);
}

gsf::CheckBoxWidget::CheckBoxWidget()
: ButtonWidget{  }
, m_isChecked{ false }
, m_checkedShapeColor{ sf::Color::Black }
{
    init();
}

gsf::CheckBoxWidget::CheckBoxWidget
    (float width, float height)
: ButtonWidget{ width, height }
, m_isChecked{ false }
{
    init();
}

void gsf::CheckBoxWidget::init()
{
    setHoverFillColor(sf::Color::White);
}

bool gsf::CheckBoxWidget::isChecked() const
{
    return m_isChecked;
}

void gsf::CheckBoxWidget::setIsChecked(bool isChecked)
{
    m_isChecked = isChecked;
}

sf::Color gsf::CheckBoxWidget::getCheckedShapeColor() const
{
    return m_checkedShapeColor;
}

void gsf::CheckBoxWidget::setCheckedShapeColor(sf::Color color)
{
    m_checkedShapeColor = color;
}

bool gsf::CheckBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    bool handled{ ButtonWidget::handleEventCurrentAfterChildren(event, target) };
    sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseButton.x, 
            event.mouseButton.y }) };
    bool isMouseInShownArea{ getShownArea().contains(mousePos) };
    if (isMouseInShownArea)
    {
        if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
        {
            m_isChecked = !m_isChecked;
        }
    }
    return handled;
}
void gsf::CheckBoxWidget::updateCurrentAfterChildren(float dt)
{
    ButtonWidget::updateCurrentAfterChildren(dt);
}

void gsf::CheckBoxWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{
    ButtonWidget::drawCurrentAfterChildren(target, states, defaultView);
    // Draw checked
    if (m_isChecked)
    {
        // If the CheckBox is checked, it is shown by a rectangle in the center of
        // the box which have 80% of the checkboxs width and height
        sf::RectangleShape shape{ { getWidth() * 0.8f, getHeight() * 0.8f } };
        // Center
        shape.setPosition(getWidth() * 0.1, getHeight() * 0.1);
        shape.setFillColor(m_checkedShapeColor);
        target.draw(shape, states);
    }
}
