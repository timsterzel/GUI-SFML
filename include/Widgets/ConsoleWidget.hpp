#pragma once
#ifndef CONSOLEWIDGET_HPP
#define CONSOLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widgets/Widget.hpp"
#include "Widgets/ScrollableWidget.hpp"
#include "Widgets/TextWidget.hpp"
#include <string>
#include <vector>
#include "Widgets/TextInputWidget.hpp"

namespace gsf
{
    class ConsoleWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<ConsoleWidget> Ptr;
    private:
        TextInputWidget *m_textDisplay;
        TextInputWidget *m_textInput;
        // Store inputs in console here
        std::vector<sf::String> m_inputHistory;
        // With the arrow keys, the user can select inputs from histroy
        // here we store the actual position in history
        std::size_t m_inpHistoryCursPos;
        // Is called when input was entered
        std::function<void(Widget*, sf::String)> 
            m_onCommandEnteredListener;
    public:
        static Ptr create(sf::Font &font);
        static Ptr create(float width, float height, sf::Font &font);
        explicit ConsoleWidget(sf::Font &font);
        ConsoleWidget(float width, float height, sf::Font &font);

        void addTextToDisplay(sf::String text);
            
        void setOnCommandEnteredListener(std::function
                    <void(Widget*, sf::String)> listener);
    protected:
        virtual void loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes) override;
        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states, sf::View defaultView) const override;
    private:
        void init(sf::Font &font);
    };

}

#endif // CONSOLEWIDGET_HPP
