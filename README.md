# cpp_panels library v1.0.1

## Abstract
An [ncurses](https://www.gnu.org/software/ncurses/) and [jpanel](https://docs.oracle.com/javase/tutorial/uiswing/components/panel.html)-esque c++ library for terminal output.


## Table of Contents
- [Notes](#important-notes) - list of various tips and notes you may find useful when using the library
- [Structure](#basic-structure) - the basic structure / types of classes in this library (Components / Containers)
- [Components](#implemented-components) - list of all currently implemented Components in the library
- [Containers](#implemented-containers) - list of all currently implemented Containers in the library
- [Usage](#intended-usage) - the intended usage and basic work-flow of this library
- [Examples](#example-projects) - some screenshots of a class project using this library
- [TODO](#TODO) - list of things I'm looking into


## Important Notes
- I'm putting this project together as an excuse to practice c++, expose myself to more c-style coding, and play around with different structures and styles of inheritance.

- When making, the default all target compiles the library as a shared 'libpanels.so' file, but you can explicitly call make with the targets 'shared' or 'static' to compile one specifically. Making it statically generates a file 'libpanels.a' in the root directory. There is a test program in the 'test_program' directory. Similarly, you can specify 'static' or 'shared' when making that and that makefile can be used as an example of how to compile with the library (copy the headers you need). The test program has many sections of code that show various pieces of functionality that are commented out. Just uncomment a section if you want to test that functionality.

- In all instances of characters and strings in this program, I interpret the '`' character as an empty slot, meaning that area is 'transparent' and elements below are visible through it. Keep this in mind.

- Every object you are intended to construct yourself in this library take a boolean value of whether or not the object is created dynamically, to try to avoid double free's. This parameter is required for all constructors but for copy constructors, which default to considering it as statically allocated. If you want to avoid memory leaks, please set this parameter to true when dynamically constructing this library's classes. This parameter is also always the last required (non-default) parameter.

- To clarify, all correctly-flagged dynamically-allocated Elements **which you add to a container** will be deleted for you, but this is not true for Elements that you do not add to anything. This is also not true for the Windows you create, as they cannot delete themselves. If you dynamically create your base Window, you must delete it yourself.

- This project uses ANSI escape sequences to clear and resize the terminal, which may need to be manually enabled depending on the terminal you're using if these codes don't work, you may just need to resize your terminal to the correct size and make sure you're using the console output stream display function (currently only one available). The unsafe_clear() function of Window clears the screen using OS specific and not totally secure methods, use at your own risk.

- Defined Constants
  - DYNAMIC_ELEMENT	=  true	    (used when constructing any Element)
  - STATIC_ELEMENT	=  false    (used when constructing any Element)
  - VERTICAL_LABEL	=  true	    (used when constructing or modifying Labels)
  - HORIZONTAL_LABEL	=  false    (used when constructing or modifying Labels)
  - VERTICAL_LIST	=  true	    (used when constructing or modifying Lists)
  - HORIZONTAL_LIST	=  false    (used when constructing or modifying Lists)
  - MAX_INPUT_LENGTH	=  100	    (default size of input buffers for Consoles)


## Basic Structure
- Components are objects that hold data of some kind and can be created in very specific ways. They have an x and y position and their values, but these are the only mutable aspects. Components are the lowest level of object you'll use and cannot have components added to them, even if they are containers under the hood. The coordinates of the component are processed relative to the container holding it.

- Containers are objects that have integer x and y position as well as a width and height dimension. They can contain other containers or components. They are useful because the coordinates of each of its 'members' (or the objects you've added to it) are interpreted relative to the coordinates of the container holding it. This allows you to design panels that you can then move around or modify as you wish, as well as toggle whether or not it (and so all of its members) should be drawn. When merging the Elements down into one character buffer, the order the elements are added is the order they are layered, such that the members with higher indices (latest added) are displayed on top.


## Implemented Components
- Label:
  - A string with position, this is the fundamental component of the library. Using '\n' in your Label's value drops the cursor to the next row at the origin of the Label. A label can be horizontally or vertically oriented.

  - To construct a Label, pass in its position as two integer values (col, row), the contents of the label (what will be displayed) as a cstring, whether the Label should be displayed vertically as a boolean, whether the Label is constructed dynamically, and the 'name' of the Label (a recognizable title if you want to list the objects contained within a container later). Refer to note on defined constants.

- Border:
  - The Border does not contain some merged buffer, it just contains characters for the corners and each side of the Border, which can be accessed and mutated as expected. The Border is then attached to its parent container when that parent merges.

  - To construct a Border, pass in three or five characters (corners, top and bottom, left and right; or corners, top, bottom, left, and right), whether the object is dynamic as a boolean, and, optionally, a recognizable name for the Border.

- Alert:
  - Basically a Label in interface, but it covers the majority of its parent container (two-thirds of each dimension) when added and visible (DEFAULTS TO **INVISIBLE**). It has a string that it shows centered in the Alert box (each line is not centered, but the clump is, so center them relative to each other). You can set the background character using set_bg_char(...) and you can set its Border's characters by using the same setters as you would with a Border.

  - To construct an Alert box, pass in the string message, whether it is dynamic as a boolian, and an optional recognizable name for the Alert box.

- Console:
  - Consoles are the primary method for terminal-like I/O in this system. Specifically, they primarily operate by calling output(...) with some null-terminated string to push some message to the Console, and input(...) with an input buffer (and optionally the size of the buffer (but please do pass it generally (it'll assume 100 if you don't))). This will echo the user input to the Console as well as put it into the passed buffer (null-terminated) for your program's use. The input area is always in the bottom of this component. Consoles do have dimension but cannot have any members. You can also clear() them. To use the input feature, you **must** call the setup_input(...) function, which takes the global coordinates of the Console (col, row) as a parameter, and sets the correct position for input. An easy way to find these coordinates **AFTER THE CONSOLE HAS BEEN ADDED TO THE WINDOW IN SOME CAPACITY** is to search for the Console's name using the Window function find_global_pos(..) and passing in the previously set name of the Console. Consoles cannot scroll as of now. I've made some of the ANSI and termios terminal controlling functions public, but keep in mind that the Console input() and setup_input() and the window open() and close() functions already use these to operate normally. Only use these if you know what you're doing.

  - To construct a Console, pass in its position as two integers (col, row), its width and height as integers, an integer representing the maximum number of elements to be stored in history (good practice to make this at least as much as the height of the Console so lines aren't cut off in an obvious manner), and whether this was allocated dynamically or not as a boolean. Optionally, you may (and very much should in this case) pass a string name to differentiate it from other Elements in your design later.


## Implemented Containers
- Panel:
  - The simplest kind of container, only has position and dimension in and of itself and contains other components or containers. This is intended as the interface for the container class and is the only type of container that is considered when recursively merging buffers.

  - To construct a Panel, pass you have two options. First, pass in its position as two integer values (col, row), it's dimensions as width and height integers, and whether it's dynamic as a boolean. The other option is to pass in just the dimensions and whether it's dynamic as described above. You can optionally add a name to either of these constructors if you want to label the Panel for later reference.

- Window:
  - This is the only container that allows you to actually display the contents of your layers of Elements. All Containers can merge their contents and return their character buffers, but Windows are the only one's that can interface with the terminal. You can add and remove elements to a Window as you would with a Panel using the methods of the Container class. Windows also resize the terminal when displayed.

  - To construct a Window, pass in its dimensions as two integers (width and height). Optionally, you can construct it with a name for distinguishing it from other Windows.

- List:
  - This is a container that is very similar to a Panel, except you only have direct control over one dimension, and the list can expand in the other. It holds members of any Element, but the positions of its members don't matter, the only thing that matters is the order of the elements. If the List is HORIZONTAL, they are stacked left to right. If the list is VERTICAL, they are stacked top to bottom. Making an element invisible directly will shift the following elements up or left accordingly. Pretty straightforward.

  - To construct a List, pass in it's position as two integers (col, row), the 'other dimension' (width if it is VERTICAL, else height), whether it was allocated dynamically, and, optionally, whether it is vertical as a boolean and an optional recognizable name string. Refer to defined constants note.

## Intended Usage
- The intended work flow would be to create the Components and Containers you'll be using, adding them to each other as needed for your layout, then adding everything to a primary Window, which you can then display.

- You can set the 'str' of a Label, passing the new value and whether it's vertical. To add Elements to a Container (Panel or Window), you can call the add(...) function, passing in either an Element reference or an Element pointer. Modifying the Element in your implementation will affect the Element within the class as well (so you don't need to free any of your own memory if you pass in the pointers and correctly pass in that they're dynamically allocated).

- To display any of this work, you'll need to create a Window. Note that you cannot add Windows to any other Container. You can imagine a Window as the 'canvas' on which you put all other Elements. You can add Elements to a Window freely (you can add Labels directly, for example). Before rendering anything, you should call the open() function. This will clear your screen and resize your terminal to size (hopefully). Feel free to call this whenever you want to reset the terminal size, if you want to force this for the user. When you want to render to the terminal, call the display() function of your Window object. This will print the contents of its merged buffer to the terminal. When you're done with the Window make sure to call close(). Have fun!

## Example Projects
- Hunt the Wumpus - class project in which player must navigate the cave of the dreaded 'Wumpus,' kill it, and steal its gold before escaping.
  - The general section of the UI are mostly Panels with Borders. The right sidebar is a List with Panels and Labels in it as well as a Console for communicating information to the Player. The game over dialogue is an example of an Alert with .82 percentage scaling. The Player's is its own Label that is moved around on top of the map.
  - ![Hunt the Wumpus UI Screenshot 1](doc/screenshots/hunt-the-wumpus-ui.png?raw=true)
  - ![Hunt the Wumpus UI Screenshot 2](doc/screenshots/hunt-the-wumpus-alert.png?raw=true)

## TODO
- Implement:
  - [x] Border
  - [x] Alert Box
  - [x] Input / History of Input Box
- Look Into:
  - [ ] pipe()
  - [ ] dup2()
  - [x] Using <stdio.h> and <unistd.h> instead of <iostream> (use printf (maybe write with pipes later)).
- Misc:
  - [x] Change character buffers to 1D
  - [ ] Get rid of gross indices when accessing buffers by storing them in variables
