#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextWidget.hpp"
#include "VerticalLayout.hpp"

typedef std::chrono::high_resolution_clock CLOCK;


int main()
{
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/LiberationSans-Regular.ttf"))
    {
        std::cout << "Error by loading Font" << std::endl;
    }
    sf::Text txtStatFPS;
    txtStatFPS.setFont(font);
    txtStatFPS.setCharacterSize(12);
    txtStatFPS.setColor(sf::Color::White);
    float fps = { 0.f };
    float dt = { 0.f };
    CLOCK::time_point timePoint1 = { CLOCK::now() };

    unsigned int windowWidth = { 1280 };
    unsigned int windowHeight = { 720 };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GUI-SFML");


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
        // Determine deltaTime
        CLOCK::time_point timePoint2 = { CLOCK::now() };
        std::chrono::duration<float> timeSpan = { timePoint2 - timePoint1 };
        timePoint1 = CLOCK::now();
        // Get deltaTime as float in seconds
        dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
        fps = 1.f / dt;
        txtStatFPS.setString("FPS: " + std::to_string(fps));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(textWidget);


        window.draw(layout);
        window.draw(txtStatFPS);
        window.display();
    }

    return 0;
}
