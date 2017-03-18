#include "ComboBoxWidget.hpp"
#include "GUIEnvironment.hpp"
#include <iostream>

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create(const sf::Font &font)
{
    Ptr widget{ std::make_unique<ComboBoxWidget>(font) };
    return std::move(widget);
}

gsf::ComboBoxWidget::Ptr gsf::ComboBoxWidget::create(float width, float height,
        const sf::Font &font)
{
    Ptr widget{ std::make_unique<ComboBoxWidget>(width, height, font) };
    return std::move(widget);
}

gsf::ComboBoxWidget::ComboBoxWidget(const sf::Font &font)
: Widget{  }
, m_listBoxWidgetUnique{ ListBoxWidget::create(0.f, 0.f, font) }
, m_listBoxWidget{ m_listBoxWidgetUnique.get() }
, m_currentText{ nullptr }
, m_charSize{ 0 }
, m_font(font)
{
    init(font);
}

gsf::ComboBoxWidget::ComboBoxWidget(float width, float height, const sf::Font &font)
: Widget{ width, height }
, m_listBoxWidgetUnique{ ListBoxWidget::create(width, 0.f, font) }
, m_listBoxWidget{ m_listBoxWidgetUnique.get() }
, m_currentText{ nullptr }
, m_charSize{ 0 }
, m_font(font)
{
    init(font);
}

void gsf::ComboBoxWidget::init(const sf::Font &font)
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
    
    m_listBoxWidget->setOutlineThickness(getOutlineThickness());
    m_listBoxWidget->setOutlineColor(getOutlineColor());
    m_listBoxWidget->setHeight(120.f);
    m_listBoxWidget->setIsVisible(false);
    // Change shown Text when selection changes
    m_listBoxWidget->setOnElementSelectedListener([this](Widget *widget, int index)
    {
        ListBoxWidget *listBox{ static_cast<ListBoxWidget*>(widget) };
        m_currentText->setText(listBox->currentText());
    });

    TextWidget::Ptr currentText{ 
        TextWidget::create("", font) };
    m_currentText = currentText.get();
    attachChild(std::move(currentText));
    boundsChanged();
}

gsf::ComboBoxWidget::~ComboBoxWidget()
{
    if (m_context)
    {
        // We have added a listBoxWidget to the context, so we have now to remove it
        // from the context, beacause its not longer needed
        //m_context->removeWidget(*m_listBoxWidget);
        m_listBoxWidget->setIsRemoveable(true);
    }
}

void gsf::ComboBoxWidget::addElement(sf::String element)
{
    m_listBoxWidget->addElement(element);
    if (m_listBoxWidget->count() == 1 && m_listBoxWidget)
    {
        m_currentText->setText(m_listBoxWidget->currentText());
    }
}

sf::String gsf::ComboBoxWidget::getElement(int index) const
{
    return m_listBoxWidget->getElement(index);
}

sf::String gsf::ComboBoxWidget::currentText() const
{
    return m_currentText->getText();

}
int gsf::ComboBoxWidget::currentIndex() const
{
    return m_listBoxWidget->currentIndex();
    //return m_currentIndex;
}

int gsf::ComboBoxWidget::count() const
{
    return m_listBoxWidget->count();
    //return m_elements.size();
}

sf::Color gsf::ComboBoxWidget::getSelectionColor() const
{
    return m_listBoxWidget->getSelectionColor();
}

void gsf::ComboBoxWidget::setSelectionColor(sf::Color color)
{
    m_listBoxWidget->setSelectionColor(color);
}
void gsf::ComboBoxWidget::contextSet()
{
    m_context->addWidget(std::move(m_listBoxWidgetUnique));
    m_listBoxWidgetUnique = nullptr;
}

void gsf::ComboBoxWidget::contextRemoved()
{
    
}

void gsf::ComboBoxWidget::boundsChanged()
{
    m_charSize = getHeight() - 2.f;
    if (m_currentText)
    {
        m_currentText->setCharacterSize(m_charSize);
    }
    m_listBoxWidget->setWidth(getWidth());
    placeChildWidgets();
}

bool gsf::ComboBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    bool handled = Widget::handleEventCurrentAfterChildren(event, target);
    if (event.type == sf::Event::MouseButtonPressed 
            && event.mouseButton.button == sf::Mouse::Left)
    {

        sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseButton.x, 
            event.mouseButton.y }) };
        bool intersecting{ isIntersecting(mousePos) };
        bool isInShownArea{ getShownArea().contains(mousePos) };
        if (intersecting && isInShownArea)
        {
            m_listBoxWidget->setIsVisible(!m_listBoxWidget->isVisible());
            // When there are no entries, there is nothing to show
            if (m_listBoxWidget->count() == 0)
            {
                m_listBoxWidget->setIsVisible(false);
            }
            // Calculate position of ListBox
            if (m_listBoxWidget->isVisible())
            {
                placeListBox();
            }
        }
        // "Close" (make unvisible) listBox when clicking not in the Combobox or
        // in listBoxWidget
        else if(!m_listBoxWidget->getGlobalBounds().contains(mousePos))
        {
            m_listBoxWidget->setIsVisible(false);
        }
    }
        return handled;
}

void gsf::ComboBoxWidget::placeListBox()
{
    if (!m_context)
    {
        return;
    }
    
    const sf::View &windowView{ m_context->getCurrentView() };
    float viewHeight{ windowView.getSize().y };
    float distanceYBottom{ viewHeight
        - getWorldBottom() };
    float distanceYTop{ getWorldTop() };
    sf::FloatRect gBounds{ getGlobalBoundsWithoutOutline() };
    float listContentHeight{ m_listBoxWidget->getContentHeight() };
    // Place under ComboBox
    if (distanceYBottom > distanceYTop)
    {
        // Total height should be the height of the lists content, and when its to 
        // large to show it, it should be the max possible showable height
        float totalHeight{ 
            listContentHeight > distanceYBottom 
                ? distanceYBottom : listContentHeight };
        m_listBoxWidget->setHeight(totalHeight);
        m_listBoxWidget->setPosition(gBounds.left, 
            gBounds.top + gBounds.height);
    }
    // Place on top of ComboBox
    else
    { 
        // Total height should be the height of the lists content, and when its to 
        // large to show it, it should be the max possible showable height
        float totalHeight{ 
            listContentHeight > distanceYTop ? distanceYTop : listContentHeight };
        m_listBoxWidget->setHeight(totalHeight);
        m_listBoxWidget->setPosition(gBounds.left, 
            gBounds.top - m_listBoxWidget->getHeight());
    }
    m_listBoxWidget->setWidth(gBounds.width);
    m_listBoxWidget->setOutlineThickness(getOutlineThickness());
    m_listBoxWidget->setOutlineColor(getOutlineColor());
    m_listBoxWidget->setBackgroundColor(getBackgroundColor());
        m_listBoxWidget->setMoveToForground(true);
}

void gsf::ComboBoxWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ComboBoxWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{

}
