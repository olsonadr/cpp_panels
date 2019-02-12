/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include "sys/ioctl.h"
#include "Container.hpp"

class Window : public Container
{
protected:
  // Methods
  void resize_terminal();

public:
  // Constructors + Destructors + Operators
  Window(int width, int height,
         bool is_dynamic,
         const char *name = "Window")
      : Container(0, 0, width, height, is_dynamic, "Window", name) {}

  Window(const Window &old_window, bool is_dynamic = false)
      : Container(old_window, is_dynamic) {}

  ~Window();

  void operator=(const Window &old_window) { Container::operator=(old_window); }

  // Methods
  void setup();
  void display();
  void unsafe_clear();
};

#endif