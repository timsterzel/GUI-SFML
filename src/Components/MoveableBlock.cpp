#include "Components/MoveableBlock.hpp"
#include <iostream>

gsf::MoveableBlock::MoveableBlock()
{

}

gsf::MoveableBlock::MoveableBlock(float width, float height)
: m_width(width)
, m_height(height)
{

}

gsf::MoveableBlock::~MoveableBlock()
{

}

sf::Vector2f gsf::MoveableBlock::getPosition() const
{
    return m_pos;
}

void gsf::MoveableBlock::setPosition(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void gsf::MoveableBlock::setPosition(sf::Vector2f pos)
{
    setPosition(pos.x, pos.y);
}

void gsf::MoveableBlock::setPositionAndStoreOld(float x, float y)
{
    m_lastPos = m_pos;
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

float gsf::MoveableBlock::getLeft() const
{
    return m_pos.x - (getWidth() / 2.f);
}

float gsf::MoveableBlock::getRight() const
{
    return m_pos.x + (getWidth() / 2.f);
}

float gsf::MoveableBlock::getTop() const
{
    return m_pos.y - (getHeight() / 2.f);
}

float gsf::MoveableBlock::getBottom() const
{
    return m_pos.y + (getHeight() / 2.f);
}

void gsf::MoveableBlock::move(float x, float y)
{
    setPosition(m_pos.x + x, m_pos.y + y);
}

void gsf::MoveableBlock::move(sf::Vector2f xy)
{
    move(xy.x, xy.y);
}

void gsf::MoveableBlock::moveAndStoreOldPos(float x, float y)
{
    setPositionAndStoreOld(m_pos.x + x, m_pos.y + y);
}

void gsf::MoveableBlock::moveAndStoreOldPos(sf::Vector2f xy)
{
    moveAndStoreOldPos(xy.x, xy.y);
}

bool gsf::MoveableBlock::isPointIntersecting(sf::Vector2f point)
{
    return point.x >= getLeft() && point.x <= getRight() && point.y >= getTop() && point.y <= getBottom();
}
