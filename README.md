# cpp_panels library

## Abstract
An [ncurses](https://www.gnu.org/software/ncurses/) and [jpanel](https://docs.oracle.com/javase/tutorial/uiswing/components/panel.html)-esque c++ library for terminal output.


## Important Notes
- Currently, the void Container::add(Element &passed_element) function generates a memory leak, and I'm focusing on other things, so it is commented out. Please use the pointer add function.

- Every object you are intended to construct yourself in this library take a boolean value of whether or not the object is created dynamically, to try to avoid double free's. This parameter is required for all constructors but for copy constructors, which default to considering it as statically allocated. If you want to avoid memory leaks, please set this parameter to true when dynamically constructing this library's classes. This parameter is also always the last required (non-default) parameter.

- To clarify, all correctly-flagged dynamically-allocated Elements **which you add to a container** will be deleted for you, but this is not true for Elements that you do not add to anything. This is also not true for the Windows you create, as they cannot delete themselves. If you dynamically create your base Window, you must delete it yourself.

- This project uses ANSI escape sequences to clear and resize the terminal, which may need to be manually enabled depending on the terminal you're using if these codes don't work, you may just need to resize your terminal to the correct size and make sure you're using the console output stream display function (currently only one available). The unsafe_clear() function of Window clears the screen using OS specific and not totally secure methods, use at your own risk.


## Basic Structure
- Components are objects that hold data of some kind and can be created in very specific ways. They have an x and y position and their values, but these are the only mutable aspects. Components are the lowest level of object you'll use and cannot have components added to them, even if they are containers under the hood. The coordinates of the component are processed relative to the container holding it.

- Containers are objects that have integer x and y position as well as a width and height dimension. They can contain other containers or components. They are useful because the coordinates of each of its 'members' (or the objects you've added to it) are interpreted relative to the coordinates of the container holding it. This allows you to design panels that you can then move around or modify as you wish, as well as toggle whether or not it (and so all of its members) should be drawn. When merging the Elements down into one character buffer, the order the elements are added is the order they are layered, such that the members with higher indices (latest added) are displayed on top.


## Implemented Components
- Label:
  - A string with position, this is the fundamental component of the library. Using '\n' in your Label's value drops the cursor to the next row at the origin of the Label. A label can be horizontally or vertically oriented.

  - To construct a Label, pass in its position as two integer values, the contents of the label (what will be displayed) as a cstring, whether the Label should be displayed vertically as a boolean, whether the Label is constructed dynamically, and the 'name' of the Label (a recognizable title if you want to list the objects contained within a container later).


## Implemented Containers
- Panel:
  - The simplest kind of container, only has position and dimension in and of itself and contains other components or containers. This is intended as the interface for the container class and is the only type of container that is considered when recursively merging buffers.

  - To construct a Panel, pass you have two options. First, pass in its position as two integer values, it's dimensions as width and height integers, and whether it's dynamic as a boolean. The other option is to pass in just the dimensions and whether it's dynamic as described above. You can optionally add a name to either of these constructors if you want to label the Panel for later reference.
        
- Window:
  - This is the only container that allows you to actually display the contents of your layers of Elements. All Containers can merge their contents and return their character buffers, but Windows are the only one's that can interface with the terminal. You can add and remove elements to a Window as you would with a Panel using the methods of the Container class. Windows also resize the terminal when displayed.

  - To construct a Window, pass in its dimensions as two integers (width and height) and whether it is dynamically allocated. Optionally, you can construct it with a name for distinguishing it from other Windows.


## Intended Usage
- The intended work flow would be to create the Components and Containers you'll be using, adding them to each other as needed for your layout, then adding everything to a primary Window, which you can then display.

- You can set the 'str' of a Label, passing the new value and whether it's vertical. To add Elements to a Container (Panel or Window), you can call the add() function, passing in either an Element object or an Element pointer. If you pass in an Element object, it will be copied when being added, but if you pass in an Element pointer, it will not be copied and the memory address will just be added to the members list. This means that modifying the Element in your implementation will affect the Element within the class as well (so you don't need to free any of your own memory if you pass in the pointers and correctly pass in that they're dynamically allocated).

- To display any of this work, you'll need to create a Window. Note that you cannot add Windows to any other Container. You can imagine a Window as the 'canvas' on which you put all other Elements. You can add Elements to a Window freely (you can add Labels directly, for example). Before rendering anything, you should call the setup() function. This will clear your screen and resize your terminal to size (hopefully). Feel free to call this whenever you want to reset the terminal size, if you want to force this for the user. When you want to render to the terminal, call the display() function of your Window object. This will print the contents of its merged buffer to the terminal. Have fun!


## TODO
- Implement:
  - Border
  - Alert Box
- Look Into:
  - pipe()
  - dup2()
  - Using <stdio.h> and <unistd.h> instead of <iostream> (use printf (maybe write with pipes later)).
- Change character buffers to 1D