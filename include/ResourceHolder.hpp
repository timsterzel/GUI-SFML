#pragma once
#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

namespace gsf
{
    template <typename Resource>
    class ResourceHolder
    {
    private:
        std::map<std::string, std::unique_ptr<Resource>> m_resourceMap;

    public:
        void load(const std::string &id, const std::string &fileName);
        //Resource& get(const std::string &id);
        Resource& get(const std::string &id) const;
        //Resource& get(std::size_t index);
        Resource& getFirst() const;

        std::size_t size() const;
        void clear();
        // Return if a resource with the given id exists
        bool exists(const std::string &id) const;
    };
}

#include "../src/ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP
