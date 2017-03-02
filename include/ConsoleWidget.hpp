#pragma once
#ifndef CONSOLEWIDGET_HPP
#define CONSOLEWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "ScrollableWidget.hpp"
#include "TextWidget.hpp"
#include <string>
#include <vector>
#include "TextInputWidget.hpp"

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
        std::vector<std::wstring> m_inputHistory;
        // With the arrow keys, the user can select inputs from histroy
        // here we store the actual position in history
        std::size_t m_inpHistoryCursPos;
        // Is called when input was entered
        std::function<void(Widget*, std::wstring)> 
            m_onCommandEnteredListener;
    public:
        static Ptr create(sf::Font &font);
        static Ptr create(float width, float height, sf::Font &font);
        explicit ConsoleWidget(sf::Font &font);
        ConsoleWidget(float width, float height, sf::Font &font);

        void addTextToDisplay(std::wstring text);
            
        void setOnCommandEnteredListener(std::function
                    <void(Widget*, std::wstring)> listener);
    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
    private:
        void init(sf::Font &font);
    };

}

#endif // CONSOLEWIDGET_HPP
