#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextWidget.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GUI-SFML");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/LiberationSans-Regular.ttf"))
    {
        std::cout << "Error by loading Font" << std::endl;
    }

    gsf::TextWidget textWidget("Im a Text", font, 12, sf::Color::White);
    //textWidget.getText().setColor(sf::Color::Red);
    textWidget.centerOrigin();

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
