#include "../../include/Widgets/ListBoxWidget.hpp"
#include "../../include/Utility.hpp"
#include <iostream>

gsf::ListBoxWidget::Ptr gsf::ListBoxWidget::create(const sf::Font &font)
{
    Ptr widget{ std::make_unique<ListBoxWidget>(font) };
    return widget;
}

gsf::ListBoxWidget::Ptr gsf::ListBoxWidget::create(float width, float height,
        const sf::Font &font)
{
    Ptr widget{ std::make_unique<ListBoxWidget>(width, height, font) };
    return widget;
}

gsf::ListBoxWidget::ListBoxWidget(const sf::Font &font)
: Widget{  }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_entryWidgetContainer{ nullptr }
, m_charSize{ 12 }
, m_font { font }
, m_selectioColor{ sf::Color{ 192, 192, 192 } }
{
    init(font);
}

gsf::ListBoxWidget::ListBoxWidget(float width, float height, const sf::Font &font)
: Widget{ width, height }
, m_currentIndex{ 0 }
, m_scrollableWidget{ nullptr }
, m_entryWidgetContainer{ nullptr }
, m_charSize{ 12 }
, m_font{ font }
, m_selectioColor{ sf::Color{ 192, 192, 192 } }
{
    init(font);
}


void gsf::ListBoxWidget::init(const sf::Font &font)
{
    setOutlineThickness(4.f);
    m_outlineColor = sf::Color::Black;
    
    ScrollableWidget::Ptr scrollableWidget
        { ScrollableWidget::create(getWidth(), getHeight()) };
    m_scrollableWidget = scrollableWidget.get();
    scrollableWidget->setIsHorizontalScrollEnabled(false);
    attachChild(std::move(scrollableWidget));
    
    VerticalLayoutWidget::Ptr layout{ VerticalLayoutWidget::create(m_scrollableWidget->getWidth(),
    m_scrollableWidget->getHeight()) };
    
    m_entryWidgetContainer = layout.get();
    m_scrollableWidget->attachChild(std::move(layout));
    
}

void gsf::ListBoxWidget::loadAttributes(tinyxml2::XMLDocument &document, 
                std::map<std::string, std::string> &attributes)
{
    Widget::loadAttributes(document, attributes);
    Widget::loadAttributes(document, attributes, "ListBoxWidget");
}

void gsf::ListBoxWidget::applyAttribute(const std::string &name, 
        const std::string &value)
{
    Widget::applyAttribute(name, value);
    if(name == "selectionColor")
    {
        sf::Color color { Utility::stringToColor(value) };
        setSelectionColor(color);
    }
    else if(name == "listData")
    {
        std::vector<std::string> data{ Utility::splitString(value, '|') };
        for (const std::string &str : data)
        {
            addElement(str);
        }
    }
}

void gsf::ListBoxWidget::addElement(sf::String element)
{
    m_elements.push_back(element);
    
    TextWidget::Ptr textWidget{ TextWidget::create(element, m_font, m_charSize) };
    VerticalLayoutWidget::Ptr textContainer{ VerticalLayoutWidget::create(getWidth(), 
            textWidget->getLocalBounds().height ) };
    textContainer->disableAutoDetermineWidth();
    textContainer->attachChild(std::move(textWidget));

    m_entryWidgets.push_back(textContainer.get());
    m_entryWidgetContainer->attachChild(std::move(textContainer));
    m_scrollableWidget->recalculateScroll();
    if (m_elements.size() == 1)
    {
        m_currentIndex = 0;
        m_entryWidgets[0]->setBackgroundColor(m_selectioColor);
    }
}
sf::String gsf::ListBoxWidget::getElement(int index) const
{
    return m_elements[index];
}

sf::String gsf::ListBoxWidget::currentText() const
{
    return m_elements.size() > 0 ? m_elements[m_currentIndex] : L"";

}
int gsf::ListBoxWidget::currentIndex() const
{
    return m_currentIndex;
}

int gsf::ListBoxWidget::count() const
{
    return m_elements.size();
}

bool gsf::ListBoxWidget::selectElement(std::size_t index)
{
    
    if (index < 0 || index > m_elements.size() - 1)
    {
        return false;
    }
    // First deselect actual selection
    m_entryWidgets[m_currentIndex]->setBackgroundColor(
        sf::Color::Transparent);
    // Select new entry
    m_entryWidgets[index]->setBackgroundColor(m_selectioColor);
    m_currentIndex = index;
    if (m_onElementSelectedListener)
    {
        m_onElementSelectedListener(this, index); 
    }
    return true;
}

bool gsf::ListBoxWidget::selectElement(const sf::String &text)
{
    int indexFound{ -1 };
    for (std::size_t i{ 0 }; i != m_elements.size(); i++)
    {
        sf::String element{ m_elements[i] };
        if (element == text)
        {
            indexFound = i;
            break;
        }
    }
    // text is not in element container
    if (indexFound == -1)
    {
        return false;
    }
    return selectElement(indexFound);
}

float gsf::ListBoxWidget::getContentHeight() const
{
    if (!m_entryWidgetContainer)
    {
        return 0.f;
    }
    return m_entryWidgetContainer->getLocalBounds().height;
}

sf::Color gsf::ListBoxWidget::getSelectionColor() const
{
    return m_selectioColor;
}

void gsf::ListBoxWidget::setSelectionColor(sf::Color color)
{
    m_selectioColor = color;
}

void gsf::ListBoxWidget::setOnElementSelectedListener(std::function<void(Widget*, 
            int)> listener)
{
    m_onElementSelectedListener = listener;
}

void gsf::ListBoxWidget::boundsChanged()
{
    if (m_scrollableWidget)
    {
        m_scrollableWidget->setWidth(getWidth());
        m_scrollableWidget->setHeight(getHeight());
    }
    if (m_entryWidgetContainer)
    {
        m_entryWidgetContainer->setWidth(getWidth());
    }
    for (Widget *widget : m_entryWidgets)
    {
        widget->setWidth(getWidth());
    }
    placeChildWidgets();
}

bool gsf::ListBoxWidget::handleEventCurrentAfterChildren(sf::Event &event, 
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
            for (unsigned int i{ 0 }; i < m_entryWidgets.size(); i++)
            {
                auto entry{ m_entryWidgets[i] };
                if (entry->isIntersecting(mousePos) && m_currentIndex != i)
                {
                    selectElement(i);
                    return true;
                }
            }
        }
    }
    return handled;
}

void gsf::ListBoxWidget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}

void gsf::ListBoxWidget::drawCurrentAfterChildren
    (sf::RenderTarget &target, sf::RenderStates states, sf::View defaultView) const
{

}
