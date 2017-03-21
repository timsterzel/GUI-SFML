#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace gsf
{
    namespace Utility
    {
        // Make string to color. Compatible Strings:
        // "black", "white", "red", "green", "blue", "yellow", "magenta", "cyan", 
        // "transparent"
        // "(r,g,b)" "(r,g,b,a)"
        // Large and lower case is not important. If string is no legal string
        // Transparent is returned
        sf::Color stringToColor(const std::string &str);
        std::string toUpper(std::string str);
        std::vector<std::string> splitString(const std::string &str, char delimiter);
    }
}

#endif // UTILITY_HPP
