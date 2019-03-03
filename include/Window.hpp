/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdlib.h>      /* For system() call used in unsafe_clear() */
#include <termios.h>     /* For toggling ECHO of stdin */
#include <sys/ioctl.h>	 /* For storing the initial dims */
#include <cstdio>	 /* For storing the initial dims */
#include <unistd.h>	 /* For storing the initial dims */
#include "Container.hpp" /* Base class of Window */

// Maybe using later
// #include <stdio.h>    /* For possibly messing with stdin and stdout later */
// #include <unistd.h>   /* For possibly forking, etc. at a later point */

class Window : public Container
{
    protected:
        // Fields
        struct termios term_info;
        int init_width, init_height;

        // Methods
        void resize_terminal();
        void reset_terminal();

    public:
        // Constructors + Destructors + Operators
        Window(int width, int height,
               const char * name = "Window")
            : Container(0, 0, width, height, false, "Window", name),
              init_width(0), init_height(0) {}

        Window(const Window & old_window)
            : Container(old_window, false),
              init_width(0), init_height(0) {}

        void operator=(const Window & old_window);

        // Methods
        void open();
        void close();
        void display();
        void unsafe_clear();
};

#endif
