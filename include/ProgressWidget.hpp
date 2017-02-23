#pragma once
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
        sf::Color m_progessColor;
        // Set margin of the progressbar
        float m_progressMargin;

        // The actual progress in percent
        int m_progress;

    public:
        ProgressWidget();
        ProgressWidget(float width, float height);

        sf::Color getProgressColor() const;
        void setProgressColor(sf::Color color);
        float getProgressMargin() const;
        void setProgressMargin(float margin);

        int getProgress() const;
        // Value between 0 and 100 (inclusive) is the value
        // lower then 0 its set ti 0 and higher then 100 the progress
        // is set to 100
        void setProgress(int progress);

    protected:
        virtual bool handleEventCurrentAfterChildren(sf::Event &event) override;
        virtual void updateCurrentAfterChildren(float dt) override;
        virtual void drawCurrentAfterChildren
                (sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        void init();
    };
}

#endif // !PROGRESSWIDGET_HPP
