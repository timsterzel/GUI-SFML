#include "Components/MoveableBlock.hpp"
#include <iostream>

gsf::MoveableBlock::MoveableBlock()
: m_width(0.f)
, m_height(0.f)
, m_fillColor{ sf::Color::White }
{

}

gsf::MoveableBlock::MoveableBlock(float width, float height)
: m_width(width)
, m_height(height)
, m_fillColor{ sf::Color::White }
{

}

gsf::MoveableBlock::~MoveableBlock()
{

}

void gsf::MoveableBlock::setPositionAndStoreOld(float x, float y)
{
    m_lastPos = getPosition();
    setPosition(x, y);
}

void gsf::MoveableBlock::setPositionAndStoreOld(sf::Vector2f pos)
{
    setPositionAndStoreOld(pos.x, pos.y);
}

sf::Vector2f gsf::MoveableBlock::getLastPosition() const
{
    return m_lastPos;
}

float gsf::MoveableBlock::getWidth() const
{
    return m_width;
}

void gsf::MoveableBlock::setWidth(float width)
{
    m_width = width;
}

float gsf::MoveableBlock::getHeight() const
{
    return m_height;
}

void gsf::MoveableBlock::setHeight(float height)
{
    m_height = height;
}

sf::Color gsf::MoveableBlock::getFillColor() const
{
    return m_fillColor;
}

void gsf::MoveableBlock::setFillColor(sf::Color color)
{
    m_fillColor = color;
}

float gsf::MoveableBlock::getLeft() const
{
    return getPosition().x - getOrigin().x;
}

float gsf::MoveableBlock::getRight() const
{
    return getPosition().x + getOrigin().x;
}

float gsf::MoveableBlock::getTop() const
{
    return getPosition().y - getOrigin().y;
}

float gsf::MoveableBlock::getBottom() const
{
    return getPosition().y + getOrigin().y;
}

void gsf::MoveableBlock::moveAndStoreOldPos(float x, float y)
{
    setPositionAndStoreOld(getPosition().x + x, getPosition().y + y);
}

void gsf::MoveableBlock::moveAndStoreOldPos(sf::Vector2f xy)
{
    moveAndStoreOldPos(xy.x, xy.y);
}

bool gsf::MoveableBlock::isPointIntersecting(sf::Vector2f point)
{
    return point.x >= getLeft() && point.x <= getRight() && point.y >= getTop() && point.y <= getBottom();
}

void gsf::MoveableBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::RectangleShape rect({ m_width, m_height });
    rect.setFillColor(getFillColor());
    target.draw(rect, states);
}
