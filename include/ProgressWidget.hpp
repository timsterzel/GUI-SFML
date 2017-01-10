#ifndef PROGRESSWIDGET_HPP
#define PROGRESSWIDGET_HPP
#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include <string>

namespace gsf
{
    class ProgressWidget: public gsf::Widget
    {
        private:
            sf::Color m_outlineColor;
            sf::Color m_progessColor;
            float m_outlineThickness;
            // Set margin of the progressbar
            float m_progressMargin;

            // The actual progress in percent
            int m_progress;

        public:
            ProgressWidget();
            ProgressWidget(float width, float height);

            virtual ~ProgressWidget();

            sf::Color getOutlineColor() const;
            void setOutlineColor(sf::Color color);
            sf::Color getProgressColor() const;
            void setProgressColor(sf::Color color);
            float getOutlineThickness() const;
            void setOutlineThickness(float outline);
            float getProgressMargin() const;
            void setProgressMargin(float margin);

            int getProgress() const;
            // Value between 0 and 100 (inclusive) is the value
            // lower then 0 its set ti 0 and higher then 100 the progress
            // is set to 100
            void setProgress(int progress);

            virtual void drawWidget(sf::RenderTarget &target, sf::RenderStates states) const override;
            virtual void update(float dt) override;

        protected:
            virtual bool handleEvent(sf::Event &event) override;
    };

}

#endif // !PROGRESSWIDGET_HPP