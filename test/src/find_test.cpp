#include "Window.hpp"
#include "Panel.hpp"
#include "Label.hpp"

//#include <stdio.h>

int main()
{
    /* find() and find_global_pos() Test */

    // Creating Window
    int width = 100;
    int height = 40;
    Window w(width, height);

    // Creating Elements
    Panel p(10, 10, 40, 20, STATIC_ELEMENT, "my_panel");
    Label origin(0, 0, "Label at origin (made vertical hopefully)",
                 STATIC_ELEMENT, "my_origin_label");
    Label panel_label(5, 5, "Label in Panel (X at pos)",
                      STATIC_ELEMENT, "my_panel_label");
    Label indicator(1, 1, "X", STATIC_ELEMENT);

    // Attributes
    p.set_bg_char('#');

    // Adding Elements to Panel
    p.add(panel_label);

    // Adding ELements to Window
    w.add(p);
    w.add(origin);
    w.add(indicator);

    // Setting up and displaying Window
    w.open();
    w.display();
    getchar();

    // Changing variables
    Element * found = w.find("my_origin_label");

    if (found != nullptr)
    {
        if (strcmp(found->get_type(), "Label") == 0)
        {
            Label * found_label = static_cast<Label *>(found);
            found_label->set_is_vertical(VERTICAL_LABEL);
        }
    }

    struct int_duple found_pos = w.find_global_pos("my_panel_label");

    indicator.set_pos(found_pos);

    // Redisplaying
    w.display();

    getchar();

    // Closing Window
    w.close();

    /* End find() and find_global_pos() Test */

    return 0;
}
