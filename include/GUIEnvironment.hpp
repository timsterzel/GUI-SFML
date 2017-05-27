#pragma once
#ifndef GSF_GUIENVIRONMENT_HPP
#define GSF_GUIENVIRONMENT_HPP
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include "ResourceHolder.hpp"

namespace gsf
{
    class Widget;
}

namespace gsf
{

    class GUIEnvironment : public sf::Drawable
    {
    private:
        typedef std::chrono::high_resolution_clock CLOCK;

        const sf::RenderWindow &m_window;
        std::vector<Widget::Ptr> m_widgets;
        ResourceHolder<sf::Font> m_fonts;
        // A global theme which is aplied on all widgets which are added to
        // the GUIEnvironment
        std::string m_globalThemePath;
        
        // Special Widgets are widgets which belongs to other widgets and are parts
        // of them (e.g. a ComboBoxWidget shows a ListBoxWidget when it was clicked)
        //std::vector<Widget*> m_specialWidgets;
        // Is true when ever the mouse is inside the window and false
        // when the mouse is outside
        bool m_isMouseInWindow;
        bool m_isWindowFocused;
        // If it is enabled window can rought out of the Render Window
        //bool m_isWindowRoughOutEnabled;
        
        // The time point of the last update 
        // (is set when update was called without deltatime)
        CLOCK::time_point m_lastUpdateTime;

    public:
        explicit GUIEnvironment(const sf::RenderWindow &m_window);
        ~GUIEnvironment();

        void addWidget(Widget::Ptr widget, bool applyGlobalTheme = true);
        Widget::Ptr removeWidget(const Widget& widget);
        // Create a scene with the specified scene xml file
        void createScene(const std::string &path);

        sf::View getCurrentView() const;
        
        // Return a pointer to the widget with the given id. If there are more then
        // one Widget with the given id, the method return the first occurrence.
        // When there is no occurrence nullptr is returned
        Widget* getWidgetByID(const std::string &id) const;
        void loadFont(const std::string &id, const std::string &path);
        sf::Font& getFont(const std::string &id) const;

        /*
        void addSpecialWidget(Widget *widget);
        void removeSpecialWidget(const Widget *widget);
        */
        //void setIsWindowRoughOutEnabled(bool isEnabled);
        //bool isWindowRoughOutEnabled() const;

        bool handleEvent(sf::Event &event);
        void update(float dt);
        // Called without deltaTime, so let Environment determine the deltaTime
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    private:
        bool loadResources(tinyxml2::XMLElement *sceneEl);
        void loadWidgetsRecur(tinyxml2::XMLElement *widgetsEl, Widget* parentWidget);
        bool loadWidgets(tinyxml2::XMLElement *sceneEl);
        // Place the Widget depending on its Orientation
        void placeWidget(Widget *widget);
    };
}

#endif // !GSF_GUIENVIRONMENT_HPP
