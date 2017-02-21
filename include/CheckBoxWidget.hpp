#ifndef CHECKBOXWIDGET_HPP
#define CHECKBOXWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "ButtonWidget.hpp"
#include <string>

namespace gsf
{
    class CheckBoxWidget: public gsf::ButtonWidget
    {
        private:
            bool m_isChecked;
            // If CheckBox is checked a rect is drawn. This member
            // variable specifies its color
            sf::Color m_checkedShapeColor;

        public:
            CheckBoxWidget();
            CheckBoxWidget(float width, float height);

            bool isChecked() const;
            void setIsChecked(bool isChecked);

            sf::Color getCheckedShapeColor() const;
            void setCheckedShapeColor(sf::Color color);
            
            virtual void update(float dt) override;
        protected:
            virtual bool handleEvent(sf::Event &event) override;
            
        private:

            virtual void drawWidget(sf::RenderTarget &target, 
                    sf::RenderStates states) const override;
    };

}

#endif // !CHECKBOXWIDGET_HPP
