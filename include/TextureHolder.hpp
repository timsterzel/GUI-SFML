#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cassert>

namespace gsf
{
    class TextureHolder
    {
        private:
            std::map<std::string, std::unique_ptr<sf::Texture>> m_textureMap;

        public:
            void load(const std::string &id, const std::string &fileName);

            sf::Texture& get(const std::string &id);
            sf::Texture& get(const std::string &id) const;
    };
}
#endif // TEXTUREHOLDER_HPP
