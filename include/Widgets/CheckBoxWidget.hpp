#pragma once
#ifndef GSF_CHECKBOXWIDGET_HPP
#define GSF_CHECKBOXWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "ButtonWidget.hpp"
#include <string>

namespace gsf
{
    class CheckBoxWidget: public gsf::ButtonWidget
    {
    public:
        typedef std::unique_ptr<CheckBoxWidget> Ptr;
    private:
        bool m_isChecked;
        // If CheckBox is checked a rect is drawn. This member
        // variable specifies its color
        sf::Color m_checkedShapeColor;

    public:
        static Ptr create();
        static Ptr create(float width, float height); 
        CheckBoxWidget();
        CheckBoxWidget(float width, float height);

        bool isChecked() const;
        void setIsChecked(bool isChecked);

        sf::Color getCheckedShapeColor() const;
        void setCheckedShapeColor(sf::Color color);
    protected:
        virtual void loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes) override;
        virtual void applyAttribute(const std::string &name, 
                const std::string &value) override;
        
        virtual bool handleEventCurrentAfterChildren(sf::Event &event, 
                const sf::RenderTarget &target) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren(sf::RenderTarget &target, 
                sf::RenderStates states, sf::View defaultView) const override;
    private:
        void init();
    };
}

#endif // !GSF_CHECKBOXWIDGET_HPP
