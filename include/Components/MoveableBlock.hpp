#ifndef GSF_MOVEABLEBLOCK
#define GSF_MOVEABLEBLOCK
#include <SFML/Graphics.hpp>

namespace gsf
{
    class MoveableBlock: public sf::Transformable, public sf::Drawable
    {
        private:
            //sf::Vector2f m_pos;
            sf::Vector2f m_lastPos;

            float m_width;
            float m_height;

            sf::Color m_fillColor;

        public:

            MoveableBlock();
            MoveableBlock(float width, float height);
            virtual ~MoveableBlock();

            // Change the position and store the old pos
            void setPositionAndStoreOld(float x, float y);
            void setPositionAndStoreOld(sf::Vector2f pos);
            sf::Vector2f getLastPosition() const;
            
            void setSize(float width, float height);
            void setSize(sf::Vector2f size);
            float getWidth() const;
            void setWidth(float width);
            float getHeight() const;
            void setHeight(float height);

            sf::Color getFillColor() const;
            void setFillColor(sf::Color color);

            float getLeft() const;
            float getRight() const;
            float getTop() const;
            float getBottom() const;

            // Move block and store old pos
            void moveAndStoreOldPos(float x, float y);
            void moveAndStoreOldPos(sf::Vector2f xy);

            bool isPointIntersecting(sf::Vector2f point);

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    };

}

#endif // !GSF_MOVEABLEBLOCK
