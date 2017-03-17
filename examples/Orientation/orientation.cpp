#include "GUI-SFML.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window{ sf::VideoMode{ 1280, 720 }, "GUI-SFML Example Orientation" };
    // Some widgets need a Font to work properly, so we load one
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/LiberationSans-Regular.ttf"))
    {
        std::cout << "Error by loading Font" << std::endl;
    }
    // Create an instance of GUIEnvironment which handle the drawing, updating and 
    // events of the widgets which are added to it
    // It needs the window as a parameter
    gsf::GUIEnvironment environment{ window };
    
    // Create a Vertical layout. The "create" method create a unique_ptr with the
    // given parameters.
    // The height of the layout is automatic calculated and depends
    // of its child widgets.
    gsf::VerticalLayout::Ptr layout{ gsf::VerticalLayout::create(200.f, 0.f) };
    layout->setPosition(200.f, 200.f);
    layout->setOutlineThickness(6.f);
    //layout->setOrientation(gsf::Orientation::Top | gsf::Orientation::Left);
    layout->setOrientation(gsf::Orientation::Center);
    // Make background gray
    layout->setBackgroundColor(sf::Color{ 192, 192, 192 });
    
    // Create some TextWidgets
    gsf::TextWidget::Ptr text1{ gsf::TextWidget::create("Text One", font) };
    gsf::TextWidget::Ptr text2{ gsf::TextWidget::create("Text Two", font) };
    gsf::TextWidget::Ptr text3{ gsf::TextWidget::create("Text Three", font) };
    // Add TextWidgets to the Layout
    layout->attachChild(std::move(text1));
    layout->attachChild(std::move(text2));
    layout->attachChild(std::move(text3));

    // Add Layout to environment
    environment.addWidget(std::move(layout));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            environment.handleEvent(event);
        }
        //environment.update(dt);

        window.clear(sf::Color::White);
        window.draw(environment);
        window.display();
    }
}
