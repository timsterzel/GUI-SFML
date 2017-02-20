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
    class ConsoleWidget: public gsf::ChildWidget
    {
        private:
            TextInputWidget *m_textDisplay;
            TextInputWidget *m_textInput;
            // Store inputs in console here
            std::vector<std::wstring> m_inputHistory;
            // With the arrow keys, the user can select inputs from histroy
            // here we store the actual position in history
            std::size_t m_inputHistoryIndex;

        public:
            ConsoleWidget(float width, float height, sf::Font &font);

        protected:

            virtual void drawCurrent(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;

            virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states) const;
            virtual bool handleEventCurrent(sf::Event &event) override;
        private:

            virtual void updateCurrent(float dt) override;

    };

}

#endif // CONSOLEWIDGET_HPP
