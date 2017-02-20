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
        private:
            //sf::Text m_text;
            TextWidget *m_text;
            sf::Font &m_font;
            unsigned int m_charSize;
            bool m_isEditable;
            sf::Text m_cursor;
            ScrollableWidget *m_scrollable;            
            // The text which is stored in TextInput
            std::wstring m_currentText;
            // The text which is shown in the Widget
            std::wstring m_shownText;
            // True when Widget is focused
            bool m_isFocused;
            // The position of the cursor inside the text
            unsigned int m_cursorPos;
            // The cnt of added line breaks in m_shownText before the cursor pos
            unsigned int m_lBreaksBefCur;
            // When its true the cursor get drawn. The frequrency of the visibility
            // change is set by the m_blinkFreq member
            bool m_isCursorShown;
            // The time between a visibility change of the cursor
            float m_blinkFreq;
            // The time since the cursor was last shown or invisble in secods
            float m_lastBlinkTime;

        protected:
            // The minimum amount if chars where a line breake was added
            unsigned int m_minBreakCharCnt;

        public:
            TextInputWidget(float width, float height, sf::Font &font);
            
            void setIsEditable(bool isEditable);
            bool isEditable() const;

            void setText(const std::wstring &text);
            std::string getText() const;

            void setCharacterSize(const unsigned int size);
            unsigned int getCharacterSize() const;

            void setTextColor(const sf::Color color);
            sf::Color getTextColor() const;
        
            bool isFocused() const;
            
            void setIsVerticalScrollEnabled(bool isEnabled);
            bool isVerticalScrollEnabled() const;
            void setIsHorizontalScrollEnabled(bool isEnabled);
            bool isHorizontalScrollEnabled() const;

        protected:

            virtual void drawCurrent(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;

            virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                    sf::RenderStates states) const;
            virtual bool handleEventCurrent(sf::Event &event) override;
            // Adjust the Text so that it fit in the Widget. E.g. when only vertical
            // scroll is enabled add line breaks on the right positions
            void adjustShownText();

            // Determine the index of the char which is on the given position.
            // Returns -1 when there is no char
            int findIndexOfCharOnPos(sf::Vector2f localPos) const;
            int findCharOnPosBinary(sf::Vector2f localPos, std::size_t l, 
                    std::size_t r) const;
            // Returns true if the given position is inside the char 
            // on given index of m_text 
            bool isPosInCharOfText(sf::Vector2f pos, std::size_t i) const;
        private:


            virtual void updateCurrent(float dt) override;
            // Reset cursor status means, that m_lastBlinkTime is set to 0 and
            // m_isCursorShown to true
            void resetCursorStatus();

    };

}

#endif // TEXTINPUTWIDGET_HPP
