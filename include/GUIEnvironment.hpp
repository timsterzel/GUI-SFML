#pragma once
#ifndef GUIENVIRONMENT_HPP
#define GUIENVIRONMENT_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace gsf
{
    class Widget;
}

namespace gsf
{

    class GUIEnvironment : public sf::Drawable
    {
    private:
        const sf::RenderWindow &m_window;
        std::vector<Widget::Ptr> m_widgets;
        // Special Widgets are widgets which belongs to other widgets and are parts
        // of them (e.g. a ComboBoxWidget shows a ListBoxWidget when it was clicked)
        //std::vector<Widget*> m_specialWidgets;
        // Is true when ever the mouse is inside the window and false
        // when the mouse is outside
        bool m_isMouseInWindow;
        bool m_isWindowFocused;
        // If it is enabled window can rought out of the Render Window
        //bool m_isWindowRoughOutEnabled;
    public:
        explicit GUIEnvironment(const sf::RenderWindow &m_window);
        ~GUIEnvironment();

        void addWidget(Widget::Ptr widget);
        Widget::Ptr removeWidget(const Widget& widget);
        
        sf::View getCurrentView() const;
        /*
        void addSpecialWidget(Widget *widget);
        void removeSpecialWidget(const Widget *widget);
        */
        //void setIsWindowRoughOutEnabled(bool isEnabled);
        //bool isWindowRoughOutEnabled() const;

        void handleEvent(sf::Event &event);
        void update(float dt);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    private:
        // Place the Widget depending on its Orientation
        void placeWidget(Widget *widget);
    };
}

#endif // GUIENVIRONMENT_HPP
