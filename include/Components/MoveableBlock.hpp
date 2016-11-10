#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>

namespace gsf
{
    class MoveableBlock
    {
        private:
            sf::Vector2f m_position;
        public:
            MoveableBlock();
            virtual ~MoveableBlock();
    };

}

#endif // WIDGET_HPP
