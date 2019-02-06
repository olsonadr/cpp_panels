/*
 *  Panel class. It is a Container that has variable pos, and is primary
 *  container used to organize content within a Window. Basically, Panels
 *  are the interface through which the user accesses the Container funct-
 *  ionality for fencing off Elements. Has no added functionality to Cont-
 *  ainer, just simplifies user interface.
 */

#ifndef PANEL_HPP
#define PANEL_HPP

#include "Container.hpp"

class Panel : public Container
{
    public:
      // Constructors + Destructors + Operators
      Panel(int x = 0, int y = 0,
            int width = 0, int height = 0,
            const char *name = "Panel")
          : Container(x, y, width, height, "Panel", name) {}

      Panel(int width, int height,
            const char *name = "Panel")
          : Container(0, 0, width, height, "Panel", name) {}

      Panel(const Panel &old_panel)
          : Container(old_panel) {}

      void operator=(const Panel &old_panel) { Container::operator=(old_panel); }
};

#endif