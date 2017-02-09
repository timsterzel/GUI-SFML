#ifndef TEXTINPUTWIDGET_HPP
#define TEXTINPUTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "ScrollableWidget.hpp"
#include <string>

namespace gsf
{
    class TextInputWidget: public gsf::Widget
    {
        protected:

        private:
            sf::Text m_text;
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

            virtual void drawWidget(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
            virtual void update(float dt) override;

        protected:

            virtual bool handleEvent(sf::Event &event) override;

        private:

    };

}

#endif // TEXTINPUTWIDGET_HPP
