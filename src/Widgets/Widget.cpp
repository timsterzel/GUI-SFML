#include "Widgets/Widget.hpp"
#include "GUIEnvironment.hpp"
#include "Orientation.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
/*
const std::map<std::string, std::string> gsf::Widget::ThemeAttributes = 
{
    { "outlineColor", "black" },
    { "outlineThickness", "0" },
    { "backgroundColor", "transparent" }
};
*/

gsf::Widget::Ptr gsf::Widget::create(bool isWindowWidget, std::string themePath)
{
    gsf::Widget::Ptr widget{ std::make_unique<gsf::Widget>
        (isWindowWidget, themePath) };    
    //widget->applyTheme(themePath);
    return std::move(widget);
}

gsf::Widget::Ptr gsf::Widget::create(float width, float height, 
        bool isWindowWidget, std::string themePath)
{
    gsf::Widget::Ptr widget{ std::make_unique<gsf::Widget>(width, height, 
            isWindowWidget, themePath) };
    //widget->applyTheme(themePath);
    return std::move(widget);
}

gsf::Widget::Widget(bool isWindowWidget, std::string themePath)
//, m_width{ 0.f }
//, m_height{ 0.f }
: m_context{ nullptr }
, m_orientation{ Orientation::None }
, m_contentArea{ 0.f, 0.f, 0.f, 0.f }
, m_fullArea{ 0.f, 0.f, 0.f, 0.f }
, m_outlineColor{ sf::Color::Black }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::White }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
, m_isWindowWidget{ isWindowWidget }
{
    init(themePath);
}

gsf::Widget::Widget(float width, float height, bool isWindowWidget, 
        std::string themePath)
//, m_width{ width }
//, m_height{ height }
: m_context{ nullptr }
, m_orientation{ Orientation::None }
, m_contentArea{ 0.f, 0.f, width, height }
, m_fullArea{ 0.f, 0.f, width, height }
, m_outlineColor{ sf::Color::Black }
, m_outlineThickness{ 0.f }
, m_bgColor{ sf::Color::White }
, m_parent{ nullptr }
, m_moveToForeground{ false }
, m_isRemoveable{ false }
, m_isVisible{ true }
, m_isWindowWidget{ isWindowWidget }
{
    init(themePath);
}

void gsf::Widget::init(const std::string &themePath)
{
    //loadThemeFile(themePath);
    //loadAttributes("Widget");
}

void gsf::Widget::applyTheme(const std::string &path)
{
    tinyxml2::XMLDocument document;
    loadThemeFile(document, path);
    std::map<std::string, std::string> attributes;
    loadAttributes(document, attributes);
    applyAttributes(attributes);
    //applyAttributes();
}

bool gsf::Widget::loadThemeFile(tinyxml2::XMLDocument &document, 
        const std::string &path)
{
    if (document.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Error by loading theme. Path: " << path << std::endl;
        return false;
    }
    return true;
}

void gsf::Widget::loadAttributes(tinyxml2::XMLDocument &document, 
    std::map<std::string, std::string> &attributes)
{
    loadAttributes(document, attributes, "Widget");
}

void gsf::Widget::loadAttributes(tinyxml2::XMLDocument &document, 
        std::map<std::string, std::string> &attributes, 
        const std::string &widgetName)
{
    tinyxml2::XMLElement *themeEl{ document.FirstChildElement("Theme") };
    if (!themeEl)
    {
        std::cout << "Error by loading theme: No valid theme file." << std::endl;
        return;
    }
    tinyxml2::XMLElement *widgetEl{ themeEl->FirstChildElement(
            widgetName.c_str()) };
    if (!widgetEl)
    {
        std::cout << "No Widget theme specified" << std::endl;
        return;
    }
    // Loop over all Attributes
    for (const tinyxml2::XMLAttribute *a{ widgetEl->FirstAttribute() }; a; 
            a = a->Next())
    {
        std::string name{ a->Name() };
        std::string value{ a->Value() };
        //themeAttr.insert(std::make_pair(name, value));
        // Important that we use [] operator here instead of insert or emplace, so
        // that the key is created with the value if it not exists or override the
        // value with the new one. This is important, because Theme Attributes, 
        // defind in child class themes have a higher priorety
        attributes[name] = value;
        //std::cout << "Attr: " << name << " : " << value << std::endl;
    }
}


void gsf::Widget::applyAttributes(std::map<std::string, std::string> &attributes)
{
    for (auto const &attr : attributes)
    {
        std::string name{ attr.first };
        std::string value{ attr.second };
        applyAttribute(name, value);       
    }
}

void gsf::Widget::applyAttribute(const std::string &name, const std::string &value)
{
    if (name == "id")
    {
        setID(value);
    }
    else if (name == "width")
    {
        float val{ std::stof(value) };
        setWidth(val);
    }
    else if (name == "height")
    {
        float val{ std::stof(value) };
        setHeight(val);
    }
    else if (name == "positionX")
    {
        float val{ std::stof(value) };
        setPosition(val, getPosition().y);
    }
    else if (name == "positionY")
    {
        float val{ std::stof(value) };
        setPosition(getPosition().x, val);
    }
    else if (name == "originX")
    {
        float val{ std::stof(value) };
        setOrigin(val, getOrigin().y);
    }
    else if (name == "originY")
    {
        float val{ std::stof(value) };
        setOrigin(getOrigin().x, val);
    }
    else if (name == "left")
    {
        float val{ std::stof(value) };
        setLeftPosition(val);
    }
    else if (name == "right")
    {
        float val{ std::stof(value) };
        setRightPosition(val);
    }
    else if (name == "top")
    {
        float val{ std::stof(value) };
        setTopPosition(val);
    }
    else if (name == "bottom")
    {
        float val{ std::stof(value) };
        setBottomPosition(val);
    }
    else if (name == "orientation")
    {
        setOrientation(Orientation::None);
        std::vector<std::string> 
            orientationVals{ Utility::splitString(value, '|') };
        for (const std::string &ori : orientationVals)
        {
            std::string strUp{ Utility::toUpper(ori) };
            if(strUp == "CENTER")
            {
                setOrientation(getOrientation() | Orientation::Center);
            }
            else if(strUp == "CENTERHORIZONTAL")
            {
                setOrientation(getOrientation() | Orientation::CenterHorizontal);
            }
            else if(strUp == "CENTERVERTICAL")
            {
                setOrientation(getOrientation() | Orientation::CenterVertical);
            }
            else if(strUp == "LEFT")
            {
                setOrientation(getOrientation() | Orientation::Left);
            }
            else if(strUp == "RIGHT")
            {
                setOrientation(getOrientation() | Orientation::Right);
            }
            else if(strUp == "TOP")
            {
                setOrientation(getOrientation() | Orientation::Top);
            }
            else if(strUp == "BOTTOM")
            {
                setOrientation(getOrientation() | Orientation::Bottom);
            }
        }
    }
    else if (name == "backgroundColor")
    {
        sf::Color color{ Utility::stringToColor(value) };
        setBackgroundColor(color);
    }
    else if(name == "outlineColor")
    {
        sf::Color color { Utility::stringToColor(value) };
        setOutlineColor(color);
    }
    else if (name == "outlineThickness")
    {
        float thickness{ std::stof(value) };
        setOutlineThickness(thickness);
    }
}

void gsf::Widget::setID(const std::string &id)
{
    m_id = id;
}

std::string gsf::Widget::getID() const
{
    return m_id;
}

gsf::Widget* gsf::Widget::getChildWidgetByID(const std::string id) const
{    
    for (const auto &child : m_children)
    {
        if (child->getID() == id)
        {
            return child.get();
        }
        Widget* childTmp{ child->getChildWidgetByID(id) };
        if (childTmp != nullptr)
        {
            return childTmp;
        }
    }
    return nullptr;
}

void gsf::Widget::setContext(GUIEnvironment *context)
{
    m_context = context;
    contextSet();
    for (const auto &child : m_children)
    {
        child->setContext(context);
    }
}

void gsf::Widget::removeContext()
{
    m_context = nullptr;
    contextRemoved();
}

gsf::GUIEnvironment* gsf::Widget::getContext() const
{
    return m_context;
}


void gsf::Widget::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x, y);
}

void gsf::Widget::setPosition(const sf::Vector2f &position)
{
    sf::Transformable::setPosition(position);
}

const sf::Vector2f& gsf::Widget::getPosition() const
{
    return sf::Transformable::getPosition();
}

void gsf::Widget::setLeftPosition(float pos)
{
    float left{ pos + (getOrigin().x + m_outlineThickness) };
    setPosition(left, getPosition().y);
}

void gsf::Widget::setRightPosition(float pos)
{
    sf::FloatRect bounds{ getLocalBounds() };
    float right{ pos + (getOrigin().x + m_outlineThickness) - bounds.width };
    setPosition(right, getPosition().y);
}

void gsf::Widget::setTopPosition(float pos)
{
    float top{ pos + (getOrigin().y + m_outlineThickness) };
    setPosition(getPosition().x, top);
}

void gsf::Widget::setBottomPosition(float pos)
{
    sf::FloatRect bounds{ getLocalBounds() };
    float bottom{ pos + (getOrigin().y + m_outlineThickness) - bounds.height };
    setPosition(getPosition().x, bottom);
}

void gsf::Widget::setHorizontalCenterPosition(float pos)
{
    sf::FloatRect bounds{ getLocalBounds() };
    float localCenter{ (-m_outlineThickness + bounds.width) / 2.f };
    float originOffset{ localCenter - getOrigin().x };
    setPosition(pos - originOffset, getPosition().y);
}

void gsf::Widget::setVerticalCenterPosition(float pos)
{
    sf::FloatRect bounds{ getLocalBounds() };
    float localCenter{ (-m_outlineThickness + bounds.height) / 2.f };
    float originOffset{ localCenter - getOrigin().y };
    setPosition(getPosition().x, pos - originOffset);
}

void gsf::Widget::setCenterPosition(float x, float y)
{
    setHorizontalCenterPosition(x);
    setVerticalCenterPosition(y);
}

void gsf::Widget::setOrientation(int orientation)
{
    m_orientation = orientation;
}

int gsf::Widget::getOrientation() const
{
    return m_orientation;
}

void gsf::Widget::setOrigin(float x, float y)
{
    sf::Transformable::setOrigin(x, y);
}

void gsf::Widget::setOrigin(const sf::Vector2f &origin)
{
    sf::Transformable::setOrigin(origin);
}

const sf::Vector2f& gsf::Widget::getOrigin() const
{
    return sf::Transformable::getOrigin();
}

void gsf::Widget::move(float offsetX, float offsetY)
{
    sf::Transformable::move(offsetX, offsetY);
}

void gsf::Widget::move(const sf::Vector2f &offset)
{
    sf::Transformable::move(offset);
}

void gsf::Widget::attachChild(Ptr child)
{    
    child->setParent(this);
    Widget &childRef{ *child.get() };
    m_children.push_back(std::move(child));
   
    childAdded(childRef);
    arrangeChildren();
    calculateSize();
}

gsf::Widget::Ptr gsf::Widget::detachChild(const Widget& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), 
            [&] (Ptr &p) -> bool { return p.get() == &node; });
    // There is an error when we try to detach a child which does not exists, 
    // so stop execution in debug mode
    assert(found != m_children.end());

    Ptr result{ std::move(*found) };
    result->setParent(nullptr);
    m_children.erase(found);

    childRemoved();
    arrangeChildren();
    calculateSize();

    return result;
}
        
void gsf::Widget::contextSet()
{
    // Do nothing by default
}
        
void gsf::Widget::contextRemoved()
{
    // Do nothing by default
}

sf::Color gsf::Widget::getOutlineColor() const
{
    return m_outlineColor;
}

void gsf::Widget::setOutlineColor(sf::Color color)
{
    m_outlineColor = color;
}

float gsf::Widget::getOutlineThickness() const
{
    return m_outlineThickness;
}

void gsf::Widget::setOutlineThickness(float outline)
{
    m_outlineThickness = outline;
    boundsChanged();
}
void gsf::Widget::setParent(Widget *parent)
{
    m_parent = parent;
}

gsf::Widget* gsf::Widget::getParent() const
{
    return m_parent;
}

void gsf::Widget::setMoveToForground(bool moveToForeground)
{
    m_moveToForeground = moveToForeground;
}

bool gsf::Widget::isMarkedForMoveToForeground() const
{
    return m_moveToForeground;
}

void gsf::Widget::setIsRemoveable(bool isRemoveable)
{
    m_isRemoveable = isRemoveable;
}

bool gsf::Widget::isRemoveable() const
{
    return m_isRemoveable;
}

void gsf::Widget::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

bool gsf::Widget::isVisible() const
{
    return m_isVisible;
}

bool gsf::Widget::isWindowWidget() const
{
    return m_isWindowWidget;
}

void gsf::Widget::setOnLeftClickListener(std::function
        <void(Widget*, sf::Vector2f)> listener)
{
    m_onLeftClickListener = listener;
}

void gsf::Widget::setOnRightClickListener(std::function
        <void(Widget*, sf::Vector2f)> listener)
{
    m_onRightClickListener = listener;
}

void gsf::Widget::setOnMiddleClickListener(std::function
        <void(Widget*, sf::Vector2f)> listener)
{
    m_onMiddleClickListener = listener;
}

void gsf::Widget::setWidth(const float width)
{
    m_contentArea.width = width;
    m_fullArea.width = width;
    boundsChanged();
}

float gsf::Widget::getWidth() const
{
    return m_contentArea.width;
    //return m_width;
}

void gsf::Widget::setHeight(const float height)
{
    m_contentArea.height = height;
    m_fullArea.height = height;
    boundsChanged();
}

float gsf::Widget::getHeight() const
{
    return m_contentArea.height;
    //return m_height;
}

float gsf::Widget::getLeft() const
{
    return getPosition().x - getOrigin().x;
}

float gsf::Widget::getRight() const
{
    return getPosition().x - getOrigin().x + getWidth();
}

float gsf::Widget::getTop() const
{
    return getPosition().y - getOrigin().y;
}

float gsf::Widget::getBottom() const
{
    return getPosition().y - getOrigin().y + getHeight();
}

float gsf::Widget::getWorldLeft() const
{
    return getWorldPosition().x - getOrigin().x;
}

float gsf::Widget::getWorldRight() const
{
    //return getWorldPosition().x - getOrigin().x + getWidth();
    return getWorldPosition().x - getOrigin().x + m_fullArea.width;
}

float gsf::Widget::getWorldTop() const
{
    return getWorldPosition().y - getOrigin().y;
}

float gsf::Widget::getWorldBottom() const
{
    //return getWorldPosition().y - getOrigin().y + getHeight();
    return getWorldPosition().y - getOrigin().y + m_fullArea.height;
}

float gsf::Widget::getRealLeft() const
{
    return getLocalBounds().left;
}

float gsf::Widget::getRealRight() const
{
    sf::FloatRect bounds{ getLocalBounds() };
    return bounds.left + bounds.width;
}

float gsf::Widget::getRealTop() const
{
    return getLocalBounds().top;
}

float gsf::Widget::getRealBottom() const
{
    sf::FloatRect bounds{ getLocalBounds() };
    return bounds.top + bounds.height;
}

float gsf::Widget::getWorldRealLeft() const
{
    return getGlobalBounds().left;
}

float gsf::Widget::getWorldRealRight() const
{
    sf::FloatRect bounds{ getGlobalBounds() };
    return bounds.left + bounds.width;
}

float gsf::Widget::getWorldRealTop() const
{
    return getGlobalBounds().top;
}

float gsf::Widget::getWorldRealBottom() const
{
    sf::FloatRect bounds{ getGlobalBounds() };
    return bounds.top + bounds.height;
}
sf::FloatRect gsf::Widget::getGlobalBounds() const
{
    float left{ getWorldLeft() - m_outlineThickness };
    float top{ getWorldTop() - m_outlineThickness };
    float width{ m_fullArea.width + 2 * m_outlineThickness };
    float height{ m_fullArea.height + 2 * m_outlineThickness };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalBounds() const
{
    float left{ getLeft() - m_outlineThickness };
    float top{ getTop() - m_outlineThickness };
    float width{ m_fullArea.width + 2 * m_outlineThickness };
    float height{ m_fullArea.height + 2 * m_outlineThickness };
    return sf::FloatRect{ left, top, width, height };
}


sf::FloatRect gsf::Widget::getGlobalBoundsWithoutOutline() const
{
    float left{ getWorldLeft() };
    float top{ getWorldTop() };
    float width{ m_fullArea.width };
    float height{ m_fullArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalBoundsWithoutOutline() const
{
    float left{ getLeft() };
    float top{ getTop() };
    float width{ m_fullArea.width };
    float height{ m_fullArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getGlobalContentBounds() const
{
    float left{ m_contentArea.left + getWorldLeft() };
    float top{ m_contentArea.top + getWorldTop() };
    float width{ m_contentArea.width };
    float height{ m_contentArea.height };
    return sf::FloatRect{ left, top, width, height };
}

sf::FloatRect gsf::Widget::getLocalContentBounds() const
{
    float left{ m_contentArea.left };
    float top{ m_contentArea.top };
    float width{ m_contentArea.width };
    float height{ m_contentArea.height };
    return sf::FloatRect{ left, top, width, height };
}


void gsf::Widget::setBackgroundColor(const sf::Color color)
{
    m_bgColor = color;
}

sf::Color gsf::Widget::getBackgroundColor() const
{
    return m_bgColor;
}

void gsf::Widget::centerOrigin()
{
    setOrigin(getWidth() / 2.f, getHeight() / 2.f);
}

sf::Transform gsf::Widget::getWorldTransform() const
{
    sf::Transform trform{ sf::Transform::Identity };
    for (const Widget *node{ this }; node != nullptr; node = node->m_parent)
    {
        trform = node->getTransform() * trform;
    }
    return trform;
}

sf::Vector2f gsf::Widget::getWorldPosition() const
{
    // Get world position ignores the real position when the origin is set 
    // (the position is every time the one in the upper left corner)
    // so we add the origin here.
    return (getWorldTransform() * sf::Vector2f()) + getOrigin();
}

sf::Vector2f gsf::Widget::convertToLocalPoint(sf::Vector2f globalPoint) const
{
    return sf::Vector2f{ globalPoint.x - getWorldPosition().x, 
        globalPoint.y - getWorldPosition().y };
}

sf::FloatRect gsf::Widget::getFullAreaRect() const
{
    return m_fullArea;
}

sf::FloatRect gsf::Widget::getOverlappingArea(sf::FloatRect rectThis, 
    sf::FloatRect rectParent) const
{
        // Data of this widget
        float leftA{ rectThis.left };
        float rightA{ rectThis.left + rectThis.width };
        float topA{ rectThis.top };
        float bottomA{ rectThis.top + rectThis.height };
        // Data of parent widgets shown area
        float leftB{ rectParent.left };
        float rightB{ rectParent.left + rectParent.width };
        float topB{ rectParent.top };
        float bottomB{ rectParent.top + rectParent.height };

        // Calculate where the shown area starts. 
        // (The startpoint should be right of the left side of its parent and
        // under the top side of its parent. Is the startpoint right of the right 
        // side of its parent or
        // under the bottom side of its parent the overlapping area is zero.
        float leftAB{ std::max(leftA, leftB) };
        float topAB{ std::max(topA, topB) };
        // The shown size should only have the size of the area of the widget 
        // which is on the parent widget
        // For this we need the intersecting area of the this widget with its parent
        float overlapX{ std::max(0.f, std::min(rightA, rightB) 
                - std::max(leftA, leftB)) };
        float overlapY{ std::max(0.f, std::min(bottomA, bottomB) 
                - std::max(topA, topB)) };
        return sf::FloatRect{ leftAB, topAB, overlapX, overlapY };
}

sf::View gsf::Widget::createViewFromRect(sf::FloatRect rect, 
        sf::RenderTarget &target, sf::View defaultView) const
{
    float left{ rect.left };
    float top{ rect.top };
    float width{ rect.width };
    float height{ rect.height };
    sf::View view;
    // The view should have the same size as the widgets shown area,
    // so the shown area of the widget is never bigger than the size of the widget,
    // although when containing widgets of the widget are bigger.
    view.setSize(width , height);

    view.setCenter(left + (width / 2.f), top + (height / 2.f) );
    
    // The viewport is the area where the widget is on screen    
    sf::Vector2f defaultViewSize{ defaultView.getSize() };
    view.setViewport(sf::FloatRect(left / defaultViewSize.x, 
                top / defaultViewSize.y,
                width / defaultViewSize.x, 
                height / defaultViewSize.y));
    
    /*
    view.setViewport(sf::FloatRect(left / target.getSize().x, 
                top / target.getSize().y,
                width / target.getSize().x, 
                height / target.getSize().y));
    */
    return view;
}

sf::FloatRect gsf::Widget::getShownArea() const
{
    //sf::FloatRect rectThis{ getGlobalBoundsWithoutOutline() };
    sf::FloatRect rectThis{ getGlobalBounds() };
    if (m_parent)
    {
         // We have to get the parents shown screen area to calculate 
         // the overlapping rect
        sf::FloatRect rectParent{ m_parent->getContentShownArea() };
        return getOverlappingArea(rectThis, rectParent);
    }
    return rectThis;
}

sf::FloatRect gsf::Widget::getContentShownArea() const
{
    sf::FloatRect rectThis{ getGlobalContentBounds() };
    if (m_parent)
    {
         // We have to get the parents shown screen area to calculate 
         // the overlapping rect
        sf::FloatRect rectParent{ m_parent->getContentShownArea() };
        return getOverlappingArea(rectThis, rectParent);
    }
    return rectThis;
}

sf::View gsf::Widget::getShownAreaView(sf::RenderTarget &target, sf::View defaultView) const
{
    sf::FloatRect shownAreaRect{ getShownArea() };
    return createViewFromRect(shownAreaRect, target,defaultView);
}
/*
sf::View gsf::Widget::getShownAreaViewWithoutOutline(sf::RenderTarget &target) const
{
    sf::FloatRect shownAreaRect{ getShownAreaWithoutOutline() };
    return createViewFromRect(shownAreaRect, target);
}
*/
sf::View gsf::Widget::getContentShownAreaView(sf::RenderTarget &target, 
        sf::View defaultView) const
{
    sf::FloatRect shownAreaRect{ getContentShownArea() };
    return createViewFromRect(shownAreaRect, target, defaultView);
}

void gsf::Widget::boundsChanged()
{
    m_fullArea.width = getWidth();
    m_fullArea.height = getHeight();
    placeChildWidgets();
}

bool gsf::Widget::isIntersecting(sf::Vector2f pos) const
{
    return getGlobalBounds().contains(pos);
    //return pos.x >= getWorldLeft() && pos.x <= getWorldRight() && 
    //    pos.y >= getWorldTop() && pos.y <= getWorldBottom();
}

void gsf::Widget::placeChildWidgets()
{
    for (const Ptr &child : m_children)
    {
        placeChildWidget(child.get());
        child->placeChildWidgets();
    }
}

void gsf::Widget::placeChildWidget(Widget *widget)
{
    
    int orientation { widget->getOrientation() };
    // Orientation is None, so we have nothing to do
    if (orientation & Orientation::None)
    {
        return;
    }
    if (orientation & Orientation::Left)
    {
        widget->setLeftPosition(m_contentArea.left);
    }
    if (orientation & Orientation::Right)
    {
        widget->setRightPosition(m_contentArea.left + m_contentArea.width);
    }
    if (orientation & Orientation::Top)
    {
        widget->setTopPosition(m_contentArea.top);
    }
    if (orientation & Orientation::Bottom)
    {
        widget->setBottomPosition(m_contentArea.top + m_contentArea.height);
    }
    if (orientation & Orientation::Center)
    {
        widget->setCenterPosition( m_contentArea.left + (m_contentArea.width / 2.f),
                m_contentArea.top + (m_contentArea.height / 2.f));
    }
    if (orientation & Orientation::CenterHorizontal)
    {
        widget->setHorizontalCenterPosition(
                m_contentArea.left + (m_contentArea.width / 2.f));
    }
    if (orientation & Orientation::CenterVertical)
    {
        widget->setVerticalCenterPosition(
                m_contentArea.top + (m_contentArea.height / 2.f));
    }
}

void gsf::Widget::calculateSize()
{
    // Do nothing by default
}

void gsf::Widget::arrangeChildren()
{
    // Do nothing by default
}

void gsf::Widget::childAdded(Widget &widget)
{
    // Do nothing by default
}

void gsf::Widget::childRemoved()
{
    // Do nothing by default
}
bool gsf::Widget::handleEvent(sf::Event &event, const sf::RenderTarget &target)
{
    bool handled{ false };
    if(!isVisible())
    {
        return false;
    }

    if (handleEventCurrentBeforeChildren(event, target))
    {
        return true;
    }
    if (!handleEventChildren(event, target))
    {
        return handleEventCurrentAfterChildren(event, target);
    }
    return handled;
}

bool gsf::Widget::handleEventCurrentBeforeChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    return false;
}

bool gsf::Widget::handleEventChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    for (const Ptr &child : m_children)
    {
        if (child->handleEvent(event, target))
        {
            return true;
        }
    }
    return false;
}

bool gsf::Widget::handleEventCurrentAfterChildren(sf::Event &event, 
        const sf::RenderTarget &target)
{
    // Is the mouse in the shown area of the widget
    sf::Vector2f mousePos{ target.mapPixelToCoords({ event.mouseButton.x, 
            event.mouseButton.y }) };
    bool isMouseInShownArea{ getShownArea().contains(mousePos) };
    bool intersecting{ isIntersecting(mousePos) };
    if (isMouseInShownArea)
    {
        if (event.type == sf::Event::MouseButtonPressed && intersecting)
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left: 
                    if (m_onLeftClickListener) 
                    { 
                        m_onLeftClickListener(this, mousePos);
                        return true;
                    }
                    break;
                case sf::Mouse::Right: 
                    if (m_onRightClickListener)
                    {
                        m_onRightClickListener(this, mousePos); 
                        return true;
                    }
                    break;
                case sf::Mouse::Middle:
                    if (m_onMiddleClickListener)
                    {
                        m_onMiddleClickListener(this, mousePos);
                        return true;
                    }
                    break;
                default: break;
            }
        }
    }
    return false;
}


void gsf::Widget::update(float dt)
{
    updateCurrentBeforeChildren(dt);
    updateChildren(dt);
    updateCurrentAfterChildren(dt);
}

void gsf::Widget::updateCurrentBeforeChildren(float dt)
{
    // Do nothing by default
}

void gsf::Widget::updateChildren(float dt)
{
    for (const Ptr &child : m_children)
    {
        child->update(dt);
    }
}

void gsf::Widget::updateCurrentAfterChildren(float dt)
{
    // Do nothing by default
}
/*
void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing
}
*/
//void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
void gsf::Widget::draw(sf::RenderTarget &target, sf::RenderStates states, 
        sf::View defaultView) const
{
    if (m_isVisible)
    {
        states.transform *= getTransform();
        // Draw basic shape (background and outline)
        sf::RectangleShape basicShape{ sf::Vector2f(m_fullArea.width, 
                m_fullArea.height) };
        basicShape.setFillColor(m_bgColor);
        basicShape.setOutlineThickness(m_outlineThickness);
        basicShape.setOutlineColor(m_outlineColor);
        target.draw(basicShape, states);

        // Set the target to the view which is only the area of the widget, 
        // based on its with, height and position
        sf::View oldView{ target.getView() };
        sf::View view{ getShownAreaView(target, defaultView) };
        target.setView(view);

        drawCurrentBeforeChildren(target, states, defaultView);
        drawChildren(target, states, defaultView);
        drawCurrentAfterChildren(target, states, defaultView);

        target.setView(oldView);
    }
}

void gsf::Widget::drawCurrentBeforeChildren(sf::RenderTarget &target, 
    sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}

void gsf::Widget::drawChildren(sf::RenderTarget &target, 
        sf::RenderStates states, sf::View defaultView) const
{
    // Children are only drawn in content view
    sf::View oldView{ target.getView() };
    sf::View view{ getContentShownAreaView(target, defaultView) };
    target.setView(view);
    for (const Ptr &child : m_children)
    {
        child->draw(target, states, defaultView);
    }
    target.setView(oldView);
}

void gsf::Widget::drawCurrentAfterChildren(sf::RenderTarget &target, 
    sf::RenderStates states, sf::View defaultView) const
{
    // Do nothing by default
}
