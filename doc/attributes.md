# Scene XML Attributes
A Widget can have specific attributes and have all attributes of its parent Widgets. [You can find a class hierarchy here.](class_hierarchy.md)

## Special Types:
ColorString: sfml Color or rgb or rgba color in format: "(r,g,b)", "(r,g,b,a)"

OrientationString: "None", "Center", "CenterHorizonal", "CenterVertical", "Left", "Right", "Top", "Bottom" can be combined with '|' e.g.: "Left|Top"

dataString: Different string data, seperated by '|'. e.g.: "Text1|Text2|Text3" are 3 strings: Text1, Text2, Text3 which are added to the widget

## Widget
```xml
<Widget
	id="string"
	width="float"
	height="float"
	positionX="float"
	positionY="float"
	originX="float"
	originY="float"
	left="float"
	right="float"
	top="float"
	bottom="float"
	orientation="OrientationString";
	outlineColor="ColorString"
	outlineThickness="float"
	backgroundColor="ColorString"
/>
```

## ButtonWidget
```xml
<ButtonWidget
	hoverFillColor="ColorString"
/>
```

## CheckBoxWidget
```xml
<CheckBoxWidget
	checkedShapeColor="ColorString"
/>
```

## ComboBoxWidget
```xml
<ComboBoxWidget
	selectionColor="ColorString"
	listData="dataString"
/>
```

## ConsoleWidget
No specific attributes

## ListBoxWidget
```xml
<ListBoxWidget
	selectionColor="ColorString"
	listData="dataString"
/>
```

## ProgressWidget
```xml
<ProgressWidget
	progressColor="ColorString"
	progressMargin="float"
	progess="unsigned int"
/>
```

## ScrollableWidget
```xml
<ScrollableWidget
	scrollbarColor="ColorString"
	scrollButtonColor="ColorString"
	scrollButtonSymbolColor="ColorString"
	isVerticalScrollEnabled="boolean"
	isHorizontalScrollEnabled="boolean"
	isVerticalScrollbarDrawn="boolean"
	isHorizontalScrollbarDrawn="boolean"
/>
```

## TextButtonWidget
```xml
<TextButtonWidget
	textColor="ColorString"
	hoverTextColor="ColorString"
	characterSize="unsigned int"
	text="string"
/>
```

## TextInputWidget
```xml
<TextInputWidget
	characterSize="unsigned int"
	cursorColor="ColorString"
	isEditable="boolean"
	textColor="ColorString"
	isNewLineAccepted="boolean"
	isVerticalScrollEnabled="boolean"
	isHorizontalScrollEnabled="boolean"
	isVerticalScrollbarDrawn="boolean"
	isHorizontalScrollbarDrawn="boolean"
	blackListChars="string"
	whiteListChars="string"
	text="string"
/>
```

## TextWidget
```xml
<TextWidget
	characterSize="unsigned int"
	textColor="ColorString"
	outlineTextColor="ColorString"
	textOutlineThickness="float"
	text="string"
/>
```

## VerticalLayoutWidget
```xml
<VerticalLayoutWidget
	autoDetermineWidth="boolean"
	autoDetermineHeight="boolean"
/>
```

## HorizontalLayoutWidget
```xml
<HorizontalLayoutWidget
	autoDetermineWidth="boolean"
	autoDetermineHeight="boolean"
/>
```

## WindowWidget
```xml
<WindowWidget
	windowTitle="string"
	topBarFillColor="ColorString"
	windowTitleColor="ColorString"
	closeButtonFillColor="ColorString"
	closeButtonSymbolFillColor="ColorString"
/>
```
