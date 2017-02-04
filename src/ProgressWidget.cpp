#include "ProgressWidget.hpp"
#include <iostream>

gsf::ProgressWidget::ProgressWidget()
: Widget()
, m_progessColor{ sf::Color::Red }
, m_progressMargin{ 5.f }
, m_progress{ 0 }
{

}

gsf::ProgressWidget::ProgressWidget(float width, float height)
: Widget(width, height)
, m_progessColor{ sf::Color::Red }
, m_progressMargin{ 5.f }
, m_progress{ 0 }
{

}

gsf::ProgressWidget::~ProgressWidget()
{

}

sf::Color gsf::ProgressWidget::getProgressColor() const
{
    return m_progessColor;
}

void gsf::ProgressWidget::setProgressColor(sf::Color color)
{
    m_progessColor = color;
}

float gsf::ProgressWidget::getProgressMargin() const
{
    return m_progressMargin;
}

void gsf::ProgressWidget::setProgressMargin(float margin)
{
    m_progressMargin = margin;
}

int gsf::ProgressWidget::getProgress() const
{
    return m_progress;
}

void gsf::ProgressWidget::setProgress(int progress)
{
    progress = progress < 0 ? 0 : progress;
    progress = progress > 100 ? 100 : progress;
    m_progress = progress;
}

void gsf::ProgressWidget::drawWidget(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    // Draw progress rect
    // Calc acutal width of progress rect
    float widthProg{ (m_width - 2 * m_progressMargin) * (m_progress / 100.f) };
    float heightProg{ (m_height - 2 * m_progressMargin) };
    sf::RectangleShape progressShape{ { widthProg, heightProg } };
    progressShape.setPosition(m_progressMargin, m_progressMargin);
    progressShape.setFillColor(m_progessColor);
    target.draw(progressShape, states);
    //target.draw(m_text, states);
}

void gsf::ProgressWidget::update(float dt)
{
    // Do nothing by default
}

bool gsf::ProgressWidget::handleEvent(sf::Event &event)
{
    bool handled{ Widget::handleEvent(event) };
    return handled;
}
