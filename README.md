# GUI-SFML

![alt tag](/images/gui_sfml_example.jpg "Example Screenshot")

A GUI system for SFML, created during the development of a small 2D game. It is useable but might have some bugs or strange behaviors once in a while. Scenes can be created and defined from xml files. You can also create your own themes to change the appereance inside the assets/themes folder. To see how to use the library there is an example within the example folder.  

## Installtion and Libraries
To use GUI-SFML you need minimum SFML 2.4.0.
GUI-SFML has the tinyxml2 library included which is released under the Zlib licence.
To use GUI-SFML you have to add the path of the GUI-SFML project to your projects makefile and include ```GUI-SFML.hpp```.
To test an example you have to navigate to one of the example folders and create the example with ```make``` command.

## Available Widgets
- TextWidget
- TextInputWidget
- ButtonWidget
- TextButtonWidget
- CheckBoxWidget
- ListBoxWidget
- ComboBoxWidget
- ConsoleWidget
- ProgressWidget
- ScrollableWidget
- VerticalLayoutWidget
- HorizontalLayoutWidget
- WindowWidget
- Widget (can be used as a container for other widget)

## Note
The size of a widget, specified by creating or with setWidth and setHeight methods, are not always the real size of the widget. There are additional things which can affect the size of a widget like its outline thickness or scrollbars, topbars and other things like that. You have to take care of it when you create your scenes. You can get the real size of a widget by calling ```getGlobalBounds()```.
