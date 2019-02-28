/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdlib.h>      /* For system() call used in unsafe_clear() */
#include <termios.h>     /* For toggling ECHO of stdin */
#include "Container.hpp" /* Base class of Window */

// Maybe using later
// #include <stdio.h>    /* For possibly messing with stdin and stdout later */
// #include <unistd.h>   /* For possibly forking, etc. at a later point */

class Window : public Container
{
    protected:
        // Fields
        struct termios term_info;

        // Methods
        void resize_terminal();

    public:
        // Constructors + Destructors + Operators
        Window(int width, int height,
               const char * name = "Window")
            : Container(0, 0, width, height, false, "Window", name) {}

        Window(const Window & old_window)
            : Container(old_window, false) {}

        void operator=(const Window & old_window);

        ~Window() { this->Container::~Container(); }

        // Methods
        void open();
        void close();
        void display();
        void unsafe_clear();
};

#endif
