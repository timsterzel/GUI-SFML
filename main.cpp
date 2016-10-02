#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextWidget.hpp"
#include "VerticalLayout.hpp"

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
    textWidget.centerOrigin();
    textWidget.setBackgroundColor(sf::Color::Red);
    textWidget.setCharacterSize(60);
    textWidget.setPosition(windowWidth / 2.f, windowHeight / 2.f);

    gsf::VerticalLayout layout;
    layout.setPosition(200.f , 100.f);
    layout.setBackgroundColor(sf::Color::Cyan);
    std::vector<std::unique_ptr<gsf::TextWidget>> textWidgets;
    for (int i = { 0 }; i != 3; i++)
    {
        std::string textString = "Text Num " + std::to_string(i);
        std::unique_ptr<gsf::TextWidget> text = { std::make_unique<gsf::TextWidget>(textString, font, 40, sf::Color::White) };
        text->setBackgroundColor(sf::Color::Red);
        layout.attachChild(std::move(text));
    }


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
        window.draw(layout);
        window.display();
    }

    return 0;
}
