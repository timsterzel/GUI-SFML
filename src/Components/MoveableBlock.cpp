#include "Components/MoveableBlock.hpp"
#include <iostream>

gsf::MoveableBlock::MoveableBlock()
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
    m_lastPos = m_pos;
    m_pos.x = x;
    m_pos.y = y;
}

void gsf::MoveableBlock::setPosition(sf::Vector2f pos)
{
    setPosition(pos.x, pos.y);
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

void gsf::MoveableBlock::move(float x, float y)
{
    setPosition(m_pos.x + x, m_pos.y + y);
}

void gsf::MoveableBlock::move(sf::Vector2f xy)
{
    move(xy.x, xy.y);
}
