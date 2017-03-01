#pragma once
#ifndef TEXTINPUTWIDGET_HPP
#define TEXTINPUTWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "ScrollableWidget.hpp"
#include "TextWidget.hpp"
#include <string>

namespace gsf
{
    class TextInputWidget: public gsf::Widget
    {
    private:
        TextWidget *m_text;
        sf::Font &m_font;
        unsigned int m_charSize;
        bool m_isEditable;
        sf::Text m_cursor;
        sf::Color m_cursorColor;
        ScrollableWidget *m_scrollable;            
        // The text which is stored in TextInput
        std::wstring m_currentText;
        // The text which is shown in the Widget
        std::wstring m_shownText;
        // If it is false, entered new lines by user are not accepted
        bool m_acceptNewLines;
        // True when Widget is focused
        bool m_isFocused;
        // The position of the cursor inside the text
        unsigned int m_cursorPos;
        // The cnt of added line breaks in m_shownText before the cursor pos
        unsigned int m_lBreaksBefCur;
        // The indexes of the added new lines (index in m_shownText 
        // not m_currentText) 
        std::vector<unsigned int> m_lBreakIndexes;
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
        
        void setCursorColor(sf::Color color);
        sf::Color getCursorColor() const;

        void setIsEditable(bool isEditable);
        bool isEditable() const;

        void setText(const std::wstring &text);
        std::wstring getText() const;

        void setCharacterSize(const unsigned int size);
        unsigned int getCharacterSize() const;

        void setTextColor(const sf::Color color);
        sf::Color getTextColor() const;
            
        void setIsNewLineAccepted(bool isAccepted);
        bool getIsNewLineAccepted() const;

        bool isFocused() const;

        void setIsVerticalScrollEnabled(bool isEnabled);
        bool isVerticalScrollEnabled() const;
        void setIsHorizontalScrollEnabled(bool isEnabled);
        bool isHorizontalScrollEnabled() const;

        void setIsVerticalScrollbarDrawn(bool isDrawn);
        void setIsHorizontalScrollbarDrawn(bool isDrawn);
    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const;
        // Adjust the Text so that it fit in the Widget. E.g. when only vertical
        // scroll is enabled add line breaks on the right positions
        void adjustShownText();
    private:
        void init();
        // Reset cursor status means, that m_lastBlinkTime is set to 0 and
        // m_isCursorShown to true
        void resetCursorStatus();
        // Get the cnt of added line breaks by adjusting text up to the given index
        unsigned int getAddedLineBreaksUpToIndex(unsigned int index) const;
    };
}

#endif // TEXTINPUTWIDGET_HPP
