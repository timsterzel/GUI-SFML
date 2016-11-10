#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>

namespace gsf
{
    class MoveableBlock
    {
        private:
            sf::Vector2f m_pos;
            sf::Vector2f m_lastPos;

            float m_width;
            float m_height;
        public:

            MoveableBlock();
            virtual ~MoveableBlock();

            sf::Vector2f getPosition() const;
            void setPosition(float x, float y);
            void setPosition(sf::Vector2f pos);
            sf::Vector2f getLastPosition() const;

            float getWidth() const;
            void setWidth(float width);
            float getHeight() const;
            void setHeight(float height);

            void move(float x, float y);
            void move(sf::Vector2f xy);

    };

}

#endif // WIDGET_HPP
