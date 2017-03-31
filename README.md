# GUI-SFML
A small GUI System for SFML. Just for learning purpose and gather experience. It is useable but have some bugs and some strange behaviors at the moment.

## Installtion and Libraries
To use GUI-SFML you need minimum SFML 2.4.0 and the library "TinyXML-2".
Just download the stable release from https://github.com/leethomason/tinyxml2/releases and copy tinyxml2.h and tinyxml2.cpp into the "libs" folder (Tested with stable Version 4.0.1).
To use GUI-SFML you have to add the path of the GUI-SFML project to your projects makefile and include GUI-SFML.hpp.
To test a example you have to navigate to one of the example folders and create the example with 'make' command.


##Available Widgets
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

There are some examples in the examples folder.
You can create a scene from a xml file.
