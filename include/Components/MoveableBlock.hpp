#ifndef MOVEABLEBLOCK
#define MOVEABLEBLOCK
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
            MoveableBlock(float width, float height);
            virtual ~MoveableBlock();

            sf::Vector2f getPosition() const;
            void setPosition(float x, float y);
            void setPosition(sf::Vector2f pos);
            // Change the position and store the old pos
            void setPositionAndStoreOld(float x, float y);
            void setPositionAndStoreOld(sf::Vector2f pos);
            sf::Vector2f getLastPosition() const;

            float getWidth() const;
            void setWidth(float width);
            float getHeight() const;
            void setHeight(float height);

            float getLeft() const;
            float getRight() const;
            float getTop() const;
            float getBottom() const;

            void move(float x, float y);
            void move(sf::Vector2f xy);
            // Move block and store old pos
            void moveAndStoreOldPos(float x, float y);
            void moveAndStoreOldPos(sf::Vector2f xy);

            bool isPointIntersecting(sf::Vector2f point);

    };

}

#endif // MOVEABLEBLOCK
