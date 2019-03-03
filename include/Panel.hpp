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
        Panel(int pos_x, int pos_y,
              int width, int height,
              bool is_dynamic,
              const char * name = "Panel")
            : Container(pos_x, pos_y, width, height, is_dynamic, "Panel", name) {}

        Panel(const Panel & old_panel, bool is_dynamic = STATIC_ELEMENT)
            : Container(old_panel, is_dynamic) {}

        void operator=(const Panel & old_panel) { Container::operator=(old_panel); }
};

#endif
