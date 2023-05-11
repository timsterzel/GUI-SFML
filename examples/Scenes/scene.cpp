#include "GUI-SFML.hpp"
#include <iostream>

int main()
{
    //sf::RenderWindow window{ sf::VideoMode{ 1280, 720 }, "GUI-SFML Example" };
    sf::RenderWindow window{ sf::VideoMode{ 800, 600 }, "GUI-SFML Example" };
    // Create an instance of GUIEnvironment which handle the drawing, updating and 
    // events of the widgets which are added to it
    // It needs the window as a parameter
    gsf::GUIEnvironment environment{ window };

    environment.createScene("TestScene.xml");
    
    gsf::ListBoxWidget* listBoxWidget{ static_cast<gsf::ListBoxWidget*>(
            environment.getWidgetByID("listBoxWidget_lb1")) };
    

    gsf::TextInputWidget* textInputWidget{ static_cast<gsf::TextInputWidget*>(
            environment.getWidgetByID("textInputWidget_ti1")) };
    listBoxWidget->addElement("Hello");

    gsf::TextButtonWidget* textButtonWidget{ static_cast<gsf::TextButtonWidget*>(
            environment.getWidgetByID("textButtonWidget_tb1")) };
    textButtonWidget->setOnLeftClickListener(
            [listBoxWidget, textInputWidget](gsf::Widget *widget, sf::Vector2f pos)
    {
        std::cout << "Pressed \n";
        sf::String txt{ textInputWidget->getText() };
        std::cout << "Text: " << txt.toAnsiString() << std::endl;
        listBoxWidget->addElement(txt);

    });
    
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
        // Call update() method without deltaTime parameter, so the envitonment
        // handle the deltaTime. If you determine the deltaTime by yourself you can
        // call update with yout deltaTime as parameter.
        environment.update();

        window.clear(sf::Color::White);
        window.draw(environment);
        window.display();
    }
}
