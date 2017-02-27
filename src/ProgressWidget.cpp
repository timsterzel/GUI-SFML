#include "ProgressWidget.hpp"
#include <iostream>

gsf::ProgressWidget::ProgressWidget()
: Widget()
, m_progessColor{ sf::Color::Black }
, m_progressMargin{ 5.f }
, m_progress{ 0 }
{
    init();
}

gsf::ProgressWidget::ProgressWidget(float width, float height)
: Widget(width, height)
, m_progessColor{ sf::Color::Black }
, m_progressMargin{ 5.f }
, m_progress{ 0 }
{
    init();
}

void gsf::ProgressWidget::init()
{
    setOutlineThickness(4.f);
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

bool gsf::ProgressWidget::handleEventCurrentAfterChildren(sf::Event &event)
{
    bool handled{ Widget::handleEventCurrentAfterChildren(event) };
    return handled;
}

void gsf::ProgressWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ProgressWidget::drawCurrentAfterChildren(sf::RenderTarget &target, 
        sf::RenderStates states) const
{
    // Draw progress rect
    // Calc acutal width of progress rect
    float widthProg{ (getWidth() - 2 * m_progressMargin) * (m_progress / 100.f) };
    float heightProg{ (getHeight() - 2 * m_progressMargin) };
    sf::RectangleShape progressShape{ { widthProg, heightProg } };
    progressShape.setPosition(m_progressMargin, m_progressMargin);
    progressShape.setFillColor(m_progessColor);
    target.draw(progressShape, states);
    //target.draw(m_text, states);
}
