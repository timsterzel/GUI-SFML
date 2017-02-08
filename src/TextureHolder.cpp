#include "TextureHolder.hpp"

void gsf::TextureHolder::load(const std::string &id, const std::string &fileName)
{
    std::unique_ptr<sf::Texture> texture{ std::make_unique<sf::Texture>() };
    if (!texture->loadFromFile(fileName))
    {
        throw std::runtime_error("gsf::TextureHolder::load - Failed to load " 
                + fileName);
    }
    auto inserted = m_textureMap.insert(std::make_pair(id, std::move(texture)));
    // Stop execute in debug mode when there was an error by inserting the texture
    // (e.g try to add the same id twice)
    assert(inserted.second);
}

sf::Texture& gsf::TextureHolder::get(const std::string &id)
{
    auto found = m_textureMap.find(id);
    // Stop programm in debug mode, when trying to get a resource which is not loaded
    assert(found != m_textureMap.end());
    return *found->second;
}

sf::Texture& gsf::TextureHolder::get(const std::string &id) const
{
    auto found = m_textureMap.find(id);
    // Stop programm in debug mode, when trying to get a resource which is not loaded
    assert(found != m_textureMap.end());
    return *found->second;
}
