#include "Utility.hpp"
#include <utility>
#include <algorithm>
#include <sstream>

sf::Color gsf::Utility::stringToColor(const std::string &str)
{
    std::string colorStr{ toUpper(str) };
    if (colorStr == "BLACK")
    {
        return sf::Color::Black;
    }
    else if (colorStr == "WHITE")
    {
        return sf::Color::White;
    }
    else if (colorStr == "RED")
    {
        return sf::Color::Red;
    }
    else if (colorStr == "GREEN")
    {
        return sf::Color::Green;
    }
    else if (colorStr == "BLUE")
    {
        return sf::Color::Blue;
    }
    else if (colorStr == "YELLOW")
    {
        return sf::Color::Yellow;
    }
    else if (colorStr == "MAGENTA")
    {
        return sf::Color::Magenta;
    }
    else if (colorStr == "CYAN")
    {
        return sf::Color::Cyan;
    }
    else if (colorStr == "TRANSPARENT")
    {
        return sf::Color::Transparent;
    }
    // Check if it is in a rgb or rgba format
    // Remove '(',')' and whitespaces from char
    std::string rmCh = "() ";
    for (std::size_t i{ 0 }; i < rmCh.size(); i++)
    {
        colorStr.erase(
            std::remove(colorStr.begin(), colorStr.end(), rmCh[i]), colorStr.end());
    }
    std::vector<std::string> splitted{ splitString(colorStr, ',') };
    std::vector<int> rgbaVec;
    for (auto str : splitted)
    {
        // Check if splitted string is a valid number
        for (char c : str)
        {
            if (!std::isdigit(c))
            {
                // No valid rgb or rgba color
                return sf::Color::Transparent;
            }
        }
        int num { std::stoi(str) };
        rgbaVec.push_back(num);
    }
    if (rgbaVec.size() < 3)
    {
        // No valid rgb or rgba color
        return sf::Color::Transparent;
    }
    int r = rgbaVec[0];
    int g = rgbaVec[1];
    int b = rgbaVec[2];
    int a = 255;
    if (rgbaVec.size() > 3)
    {
        a = rgbaVec[3];
    }
    return sf::Color(r, g, b, a);
}

std::string gsf::Utility::toUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}


std::vector<std::string> gsf::Utility::splitString(const std::string &str, 
                char delimiter)
{
    std::vector<std::string> splittedStr;
    std::stringstream ss(str);
    std::string tmp;
    while(getline(ss, tmp, delimiter))
    {
        splittedStr.push_back(tmp);
    }
    return splittedStr;
}

bool gsf::Utility::stringToBool(const std::string &str)
{
    std::string strUpper{ toUpper(str) };
    if (str == "TRUE" || str =="1")
    {
        return true;
    }
    return false;
}
