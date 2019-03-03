#include "Window.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Border.hpp"
#include "List.hpp"

#include <stdio.h>

int main()
{
    /* List Test */

    // Setup
    int list_x = 4, list_y = 2, other_dim = 20;
    Window my_window(100, 40);
    List my_list(list_x, list_y, other_dim, STATIC_ELEMENT, VERTICAL_LIST);
    Border my_border('+', '-', '|', STATIC_ELEMENT);
    Label first_label(0, 0, "Skr1234567890t!", STATIC_ELEMENT);
    Label second_label(0, 0, "Second skrt!", STATIC_ELEMENT);
    Label prompt(100 - 11, 40 - 1, "Press enter", STATIC_ELEMENT);
    Panel first_panel(0, 0, 18, 5, STATIC_ELEMENT);
    Border first_panel_border('+', '-', '|', STATIC_ELEMENT);
    first_panel.add(first_panel_border);
    Panel second_panel(0, 0, 18, 3, STATIC_ELEMENT);
    Border second_panel_border('X', '=', '|', STATIC_ELEMENT);
    second_panel.add(second_panel_border);

    // Set attributes
    my_window.set_bg_char('.');

    // Add Labels to my_list
    my_list.add(first_label);
    my_list.add(second_label);
    my_list.add(first_panel);
    my_list.add(second_panel);
    my_list.update();

    // Add my_list to window
    my_window.add(my_list);
    my_window.add(prompt);

    // Open Window
    my_window.open();
    my_window.unsafe_clear();
    my_window.display();
    getchar(); // FIRST PAUSE ----------------------------------------------------*

    // Add margins, padding, and border
    my_list.set_margins(1);
    my_list.set_padding(1);
    my_list.add(my_border);

    // Redisplay
    my_window.display();
    getchar(); // SECOND PAUSE ---------------------------------------------------*

    // Toggle visibility of first label
    first_label.make_invisible();

    // Redisplay
    my_window.display();
    getchar(); // THIRD PAUSE ---------------------------------------------------*

    // Cleanup
    my_window.close();

    /* End List Test */

    return 0;
}
