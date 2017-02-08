#ifndef GUIENVIRONMENT_HPP
#define GUIENVIRONMENT_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "TextureHolder.hpp"
#include <vector>
#include <memory>

namespace gsf
{
    class GUIEnvironment : public sf::Drawable
    {
        private:
            std::vector<Widget::Ptr> m_widgets;
            // Is true when ever the mouse is inside the window and false
            // when the mouse is outside
            bool m_isMouseInWindow;
            bool m_isWindowFocused;
            // If it is enabled window can rought out of the Render Window
            //bool m_isWindowRoughOutEnabled;
        
            TextureHolder m_textureHolder; 
        public:
            GUIEnvironment();
            virtual ~GUIEnvironment();

            void addWidget(Widget::Ptr widget);
            Widget::Ptr removeWidget(const Widget& widget);
            
            //void setIsWindowRoughOutEnabled(bool isEnabled);
            //bool isWindowRoughOutEnabled() const;

            void update(float dt);

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            void handleEvent(sf::Event &event);

            void loadTexture(const std::string &id, const std::string &fileName);
    };

}

#endif // GUIENVIRONMENT_HPP
