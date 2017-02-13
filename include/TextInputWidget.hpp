#ifndef TEXTINPUTWIDGET_HPP
#define TEXTINPUTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "ScrollableWidget.hpp"
#include "TextWidget.hpp"
#include <string>

namespace gsf
{
    class TextInputWidget: public gsf::ChildWidget
    {
        protected:

        private:
            //sf::Text m_text;
            TextWidget *m_text;
            ScrollableWidget *m_scrollable;            
            // Is added to m_text in every draw process
            std::wstring m_currentText;
            // True when Widget is focused
            bool m_isFocused;
            // The position of the cursor inside the text
            unsigned int m_cursorPos;
            // When its true the cursor get drawn. The frequrency of the visibility
            // change is set by the m_blinkFreq member
            bool m_isCursorShown;
            // The time between a visibility change of the cursor
            float m_blinkFreq;
            // The time since the cursor was last shown or invisble in secods
            float m_lastBlinkTime;
        
        public:
            TextInputWidget(float width, float height, sf::Font &font);

            void setText(const std::string &text);
            std::string getText() const;

            void setCharacterSize(const unsigned int size);
            unsigned int getCharacterSize() const;

            void setTextColor(const sf::Color color);
            sf::Color getTextColor() const;
            
            bool isFocused() const;

            virtual void drawCurrent(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
            virtual void updateCurrent(float dt) override;

        protected:
            virtual bool handleEventCurrent(sf::Event &event) override;

        private:
            // Reset cursor status means, that m_lastBlinkTime is set to 0 and
            // m_isCursorShown to true
            void resetCursorStatus();

    };

}

#endif // TEXTINPUTWIDGET_HPP
