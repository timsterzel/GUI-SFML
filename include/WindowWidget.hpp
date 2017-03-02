#ifndef WINDOWWIDGET_HPP
#define WINDOWWIDGET_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "Widget.hpp"
#include "Components/MoveableBlock.hpp"

namespace gsf
{
    class WindowWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<WindowWidget> Ptr;
    private:
        float m_topBarHeight;
        MoveableBlock m_topBar;
        MoveableBlock m_btnClose;
        // the two Symbol creates a X
        sf::RectangleShape m_btnCloseSymbolA;
        sf::RectangleShape m_btnCloseSymbolB;
        sf::Color m_btnCloseSymbolColor;
        sf::Text m_windowTitle;
        //std::string m_windowTitle;

        sf::Font &m_windowTitleFont;
        sf::Color m_windowTitleColor;
        
        bool m_moveModeActive;
        // The relative Mouse pos where the topbar is clicked by activating moving
        sf::Vector2f m_moveModeRelMousePos;
    public:
        static Ptr create(float width, float height, std::wstring title, 
                sf::Font &font);
        WindowWidget(float width, float height, std::wstring title, 
                sf::Font &font);

        sf::Color getTopbarFillColor() const;
        void setTopBarFillColor(const sf::Color color);

        sf::Color getCloseButtonFillColor() const;
        void setCloseButtonFillColor(const sf::Color color);

        sf::Color getCloseButtonSymbolFillColor() const;
        void setCloseButtonSymbolFillColor(const sf::Color color);
        
        std::wstring getWindowTitle() const;
        void setWindowTitle(const std::wstring &text);

        sf::Font getWindowTitleFont() const;
        void setWindowTitleFont(sf::Font &font);

        sf::Color getWindowTitleColor() const;
        void setWindowTitleColor(sf::Color color);

    protected:
        // Override this so we can adjust the topbar whem outline thickness or
        // width changed
        virtual void boundsChanged() override;

        virtual bool handleEventCurrentBeforeChildren(sf::Event &event);
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states) const override;
    private:
        void init();
        // Get the view for drawing Topbar 
        //sf::View getTopBarView(sf::RenderTarget &target) const;
        // Get a view which only draw in title area
        sf::View getWindowTitleView(sf::RenderTarget &target) const;

        virtual void arrangeChildren() override;
        virtual void childAdded(Widget &child);
    };
}

#endif // WINDOWWIDGET_HPP
