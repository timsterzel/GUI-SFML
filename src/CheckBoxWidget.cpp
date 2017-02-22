#include "CheckBoxWidget.hpp"
#include <iostream>

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

void gsf::CheckBoxWidget::drawWidget(sf::RenderTarget &target, sf::RenderStates states) const
{
    ButtonWidget::drawWidget(target, states);
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

void gsf::CheckBoxWidget::update(float dt)
{
    ButtonWidget::update(dt);
}

bool gsf::CheckBoxWidget::handleEvent(sf::Event &event)
{
    bool handled = ButtonWidget::handleEvent(event);
    sf::Vector2f mousePos{ (float) event.mouseButton.x, 
        (float) event.mouseButton.y };
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
