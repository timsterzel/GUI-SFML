#include "GUI-SFML.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window{ sf::VideoMode{ 1280, 720 }, "GUI-SFML Example Orientation" };
    // Create an instance of GUIEnvironment which handle the drawing, updating and 
    // events of the widgets which are added to it
    // It needs the window as a parameter
    gsf::GUIEnvironment environment{ window };

    environment.createScene("TestScene.xml");
    
    // Get widget from environment by its id, which was defined in the scene xml file
    // if there is now widget with the given id, the moethod return nullptr
    /*
    gsf::Widget* widget{ environment.getWidgetByID("textWidget_test") };
    // Add listener to widget
    widget->setOnLeftClickListener([](gsf::Widget *widget, sf::Vector2f pos)
    {
        std::cout << "Widget clicked \n";
    });
    
    gsf::ListBoxWidget* listBoxWidget{ static_cast<gsf::ListBoxWidget*>(
            environment.getWidgetByID("listBoxWidget_list1")) };
    listBoxWidget->addElement("HALLO");
    
    gsf::ComboBoxWidget* comboBoxWidget{ static_cast<gsf::ComboBoxWidget*>(
            environment.getWidgetByID("comboBoxWidget_cb1")) };
    //comboBoxWidget->addElement("HALLO");
    */
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
        // 1.f is only a placeholder, this vlaue have to be replaced with the 
        // delta time since the last update call
        environment.update(1.f);

        window.clear(sf::Color::White);
        window.draw(environment);
        window.display();
    }
}
