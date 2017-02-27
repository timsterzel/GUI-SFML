#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextButtonWidget.hpp"
#include "CheckBoxWidget.hpp"
#include "ConsoleWidget.hpp"
#include "GUIEnvironment.hpp"
#include "ProgressWidget.hpp"
#include "TextWidget.hpp"
#include "TextInputWidget.hpp"
#include "VerticalLayout.hpp"
#include "ScrollableWidget.hpp"
#include "WindowWidget.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

void determineFpsAndDeltaTime(sf::Text &txtStatFPS, float &dt, 
        float &averageFpsTime, float &fpsInSec, int &fpsCnt, 
        int &averageFpsInOneSec,
        CLOCK::time_point &timePoint1);

int main()
{
    unsigned int windowWidth{ 1280 };
    unsigned int windowHeight{ 720 };
    sf::RenderWindow window(sf::VideoMode{ windowWidth, windowHeight }, "GUI-SFML");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/LiberationSans-Regular.ttf"))
    {
        std::cout << "Error by loading Font" << std::endl;
    }

    sf::Text txtStatFPS;
    txtStatFPS.setFont(font);
    txtStatFPS.setCharacterSize(12);
    txtStatFPS.setFillColor(sf::Color::Black);
    float dt{ 0.f };
    float averageFpsTime{ 0.f };
    float fpsInSec{ 0.f };
    int fpsCnt{ 0 };
    int averageFpsInOneSec{ 0 };
    CLOCK::time_point timePoint1{ CLOCK::now() };

    gsf::GUIEnvironment guiEnvironment;
    std::unique_ptr<gsf::TextWidget> textWidget{ 
    std::make_unique<gsf::TextWidget>
        //012345678 9012345 678901 23456
        ("IM A TEXT\nTESTA\nTESTB\nTESTC\nS", font) };
    //textWidget->centerOrigin();
    textWidget->setBackgroundColor(sf::Color::Red);
    textWidget->setCharacterSize(60);
    textWidget->setPosition(windowWidth / 2.f + 100.f, windowHeight / 2.f - 330.f);
    guiEnvironment.addWidget(std::move(textWidget));
    
    std::unique_ptr<gsf::ProgressWidget> progressWidget{ 
        std::make_unique<gsf::ProgressWidget>(260, 40) };
    progressWidget->setPosition(460, 460);
    progressWidget->setProgress(50);
    guiEnvironment.addWidget(std::move(progressWidget));
    
    std::unique_ptr<gsf::ScrollableWidget> scrollableWidget{ 
        std::make_unique<gsf::ScrollableWidget>(300, 200) };
    scrollableWidget->setBackgroundColor(sf::Color::Blue);

    std::unique_ptr<gsf::VerticalLayout> layout{ 
        std::make_unique<gsf::VerticalLayout>() };
    layout->setPosition(0.f , 0.f);
    layout->setBackgroundColor(sf::Color::Cyan);
    
    for (int i{ 0 }; i != 6; i++)
    {
        std::string textString{ "Text Num " + std::to_string(i) };
        std::unique_ptr<gsf::TextWidget> text{ std::make_unique<gsf::TextWidget>
                (textString, font, 40, sf::Color::White) };
        if (i % 2 == 0)
        {
            text->setBackgroundColor(sf::Color::Green);
        }
        else
        {
            text->setBackgroundColor(sf::Color::Magenta);
        }
        std::function<void(gsf::Widget*, sf::Vector2f)> leftClickListener = 
            [] (gsf::Widget* widget, sf::Vector2f mousePos)
        {
            gsf::TextWidget *textWidget = static_cast<gsf::TextWidget*>(widget);
            std::cout << "TextWidget: Left Mouse Button Clicked. Text: " 
                << textWidget->getText().toAnsiString() << std::endl;
        };
        text->setOnLeftClickListener(leftClickListener);
        layout->attachChild(std::move(text));
    }

    scrollableWidget->attachChild(std::move(layout));

    std::unique_ptr<gsf::WindowWidget> windowWidget{ 
        std::make_unique<gsf::WindowWidget>(300.f, 360.f, "", font) };
    windowWidget->setPosition(0.f , 0.f);
    //windowWidget->setBackgroundColor(sf::Color::White);
    windowWidget->attachChild(std::move(scrollableWidget));
    windowWidget->setIsVisible(true);
    guiEnvironment.addWidget(std::move(windowWidget));
    
    std::unique_ptr<gsf::WindowWidget> windowWidget2{ 
        std::make_unique<gsf::WindowWidget>(300.f, 360.f, "", font) };
    windowWidget2->setPosition(240.f , 40.f);
    //windowWidget2->setBackgroundColor(sf::Color::Red);
    //windowWidget2->setTopBarFillColor(sf::Color::Green);
    //windowWidget2->setCloseButtonFillColor(sf::Color::Blue);
    windowWidget2->setWindowTitle("Test");
    //windowWidget2->setWindowTitleColor(sf::Color::Red);
    guiEnvironment.addWidget(std::move(windowWidget2));

    std::unique_ptr<gsf::WindowWidget> windowWidget3{ 
        std::make_unique<gsf::WindowWidget>
            (300.f, 360.f, "Test Window TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT", font) };
    windowWidget3->setPosition(300.f , 60.f);
    //windowWidget3->setOutlineThickness(12.f);
    //windowWidget3->setOutlineColor(sf::Color::White);
    //windowWidget3->setBackgroundColor(sf::Color::Blue);
    guiEnvironment.addWidget(std::move(windowWidget3));
    
    // BUTTON TEST
    std::unique_ptr<gsf::TextButtonWidget> buttonWidget{ 
        std::make_unique<gsf::TextButtonWidget>
            (200.f, 80.f, "CABBBBBTTTTTTTTTTTTTTTTTTTTTTClick me", font) };
    buttonWidget->setPosition(240.f , 360.f);
    buttonWidget->setOnLeftClickListener(
            [] (gsf::Widget* widget, sf::Vector2f mousePos)
            {
                std::cout << "Button Left Click\n";

            });
    buttonWidget->setOnRightClickListener(
            [] (gsf::Widget* widget, sf::Vector2f mousePos)
            {
                std::cout << "Button Right Click\n";

            });
    buttonWidget->setOnMiddleClickListener(
            [] (gsf::Widget* widget, sf::Vector2f mousePos)
            {
                std::cout << "Button Middle Click\n";

            });
    guiEnvironment.addWidget(std::move(buttonWidget));
    
    // SCROLLBAR TEST
    std::unique_ptr<gsf::ScrollableWidget> scrollableWidget3{ 
        std::make_unique<gsf::ScrollableWidget>(300, 200) };
    scrollableWidget3->setPosition(820.f, 420.f);
    scrollableWidget3->setBackgroundColor(sf::Color::Yellow);

    std::unique_ptr<gsf::VerticalLayout> layout4{ 
        std::make_unique<gsf::VerticalLayout>() };
    layout4->setBackgroundColor(sf::Color::Cyan);

    for (int i{0}; i != 10; i++)
    {
        std::string textString{ "Text Text Text Text Text Text Text Num " 
            + std::to_string(i) };
        std::unique_ptr<gsf::TextWidget> text{ 
            std::make_unique<gsf::TextWidget>
                (textString, font, 40, sf::Color::White) };
        if (i % 2 == 0)
        {
            text->setBackgroundColor(sf::Color::Green);
        }
        else
        {
            text->setBackgroundColor(sf::Color::Magenta);
        }
        std::function<void(gsf::Widget*, sf::Vector2f)> leftClickListener = 
            [] (gsf::Widget* widget, sf::Vector2f mousePos)
        {
            gsf::TextWidget *textWidget = static_cast<gsf::TextWidget*>(widget);
            std::cout << "TextWidget: Left Mouse Button Clicked. Text: " 
                << textWidget->getText().toAnsiString() << std::endl;
        };
        text->setOnLeftClickListener(leftClickListener);
        //text->setBackgroundColor(sf::Color::Red);
        layout4->attachChild(std::move(text));
    }
    scrollableWidget3->attachChild(std::move(layout4));
    guiEnvironment.addWidget(std::move(scrollableWidget3));

    std::unique_ptr<gsf::TextInputWidget> textInput1{ 
        std::make_unique<gsf::TextInputWidget>(300.f, 60.f, font) };
    textInput1->setPosition(320.f, 520.f);
    textInput1->setBackgroundColor(sf::Color::White);
    textInput1->setIsHorizontalScrollEnabled(false);
    textInput1->setText(L"Test Text HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH :)");
    guiEnvironment.addWidget(std::move(textInput1));
    
    // Console Widget
    std::unique_ptr<gsf::ConsoleWidget> console1{ 
        std::make_unique<gsf::ConsoleWidget>(500.f, 200.f, font) };
    console1->setPosition(700.f, 200.f);
    console1->setOnCommandEnteredListener(
            [] (gsf::Widget *widget, std::wstring inputText)
            {
                std::wcout << "CommandEnteredListener command: " << inputText 
                    << std::endl;
                gsf::ConsoleWidget *consoleWidget{ 
                    static_cast<gsf::ConsoleWidget*>(widget) };
                consoleWidget->addTextToDisplay(L"OK");
            }
    );
    guiEnvironment.addWidget(std::move(console1));
    
    // CheckBoxWidget
    std::unique_ptr<gsf::CheckBoxWidget> checkBox1{ 
        std::make_unique<gsf::CheckBoxWidget>(60, 60.f) };
    checkBox1->setPosition(10.f, 620.f);
    guiEnvironment.addWidget(std::move(checkBox1));
    
    while (window.isOpen())
    {
        determineFpsAndDeltaTime(txtStatFPS, dt, averageFpsTime, fpsInSec, fpsCnt, 
            averageFpsInOneSec, timePoint1);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            guiEnvironment.handleEvent(event);
        }
        guiEnvironment.update(dt);


        window.clear(sf::Color::White);
        window.draw(guiEnvironment);
        window.draw(txtStatFPS);
        window.display();
    }

    return 0;
}

void determineFpsAndDeltaTime(sf::Text &txtStatFPS, float &dt, 
        float &averageFpsTime, float &fpsInSec, int &fpsCnt, 
        int &averageFpsInOneSec,
        CLOCK::time_point &timePoint1)
{
    CLOCK::time_point timePoint2{ CLOCK::now() };
    std::chrono::duration<float> timeSpan{ timePoint2 - timePoint1 };
    timePoint1 = CLOCK::now();
    // Get deltaTime as float in seconds
    dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> 
        (timeSpan).count();
    float fps{ 1.f / dt };
    
    averageFpsTime += dt;
    fpsInSec += fps;
    fpsCnt++;
    if (averageFpsTime >= 1.f)
    {
        averageFpsInOneSec = fpsInSec / fpsCnt;
        averageFpsTime = 0.f;
        fpsInSec = 0.f;
        fpsCnt = 0;
    }

    txtStatFPS.setString("FPS: " + std::to_string(averageFpsInOneSec) + " (" 
            + std::to_string(fps) + ")");
}
