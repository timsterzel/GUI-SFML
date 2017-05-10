#pragma once
#ifndef GSF_LISTBOXWIDGET_HPP
#define GSF_LISTBOXWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "ScrollableWidget.hpp"
#include "TextWidget.hpp"
#include "VerticalLayoutWidget.hpp"

namespace gsf
{
    class ListBoxWidget: public gsf::Widget
    {
    public:
        typedef std::unique_ptr<ListBoxWidget> Ptr;
    private:
        std::vector<sf::String> m_elements;
        // The elements as TextWidgets
        std::vector<VerticalLayoutWidget*> m_entryWidgets;
        unsigned int m_currentIndex;
        ScrollableWidget *m_scrollableWidget;
        VerticalLayoutWidget *m_entryWidgetContainer;
        int m_charSize;
        const sf::Font &m_font;
        sf::Color m_selectioColor;

        std::function<void(Widget*, int)> m_onElementSelectedListener;
    public:
        static Ptr create(const sf::Font &font);
        static Ptr create(float width, float height, const sf::Font &font);
        explicit ListBoxWidget(const sf::Font &font);
        ListBoxWidget(float width, float height, const sf::Font &font);
    
        void addElement(sf::String element);
        sf::String getElement(int index) const;
        sf::String currentText() const;
        int currentIndex() const;
        int count() const;

        float getContentHeight() const;
        sf::Color getSelectionColor() const;
        void setSelectionColor(sf::Color color);

        void setOnElementSelectedListener(std::function<void(Widget*, int)> listener);

    protected:
        virtual void loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes) override;
        virtual void applyAttribute(const std::string &name, 
                const std::string &value) override;
        
        virtual void boundsChanged() override;
        void createScrollable();

        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    private:
        void init(const sf::Font &font);
    };
}

#endif // !GSF_LISTBOXWIDGET_HPP
