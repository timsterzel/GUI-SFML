#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextWidget.hpp"

int main()
{
    unsigned int windowWidth = { 1280 };
    unsigned int windowHeight = { 720 };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GUI-SFML");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/LiberationSans-Regular.ttf"))
    {
        std::cout << "Error by loading Font" << std::endl;
    }

    gsf::TextWidget textWidget("Im a Text", font, 12, sf::Color::White);
    //textWidget.getText().setColor(sf::Color::Red);
    //textWidget.centerOrigin();
    textWidget.setBackgroundColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(textWidget);
        window.display();
    }

    return 0;
}
