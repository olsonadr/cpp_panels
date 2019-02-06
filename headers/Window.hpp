/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include "Container.hpp"

class Window : public Container
{
public:
  // Constructors + Destructors + Operators
  Window(int width, int height,
         const char *name = "Window")
      : Container(0, 0, width, height, "Window", name) {}

  Window(const Window &old_window)
      : Container(old_window) {}

  void operator=(const Window &old_window) { Container::operator=(old_window); }

  // Methods
  void print_merged();
};

#endif