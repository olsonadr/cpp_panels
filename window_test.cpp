#include "headers/cpp_panels.hpp"

#include <stdio.h>
// #include <iostream>

int main()
{
    // Creating Window
    int width = 90;
    int height = 30;
    Window w(width, height, false);

    // Creating Elements
    Panel p(30, 10, 30, 10, false);
    Label l1(5, 2, "Should disappear!", false);
    Label *l2 = new Label(0, 1, "Should become vertical! (Corner of panel).", true);
    Label *l3 = new Label(10, 3, "New line escape here ->\nshould be on new line", true);
    Label l4(8, 0, "Should be cut -> Occluded?", false);
    Label l5(0, 20, "Should move!", false);
    Label l6(width - 14, height - 1, "Press enter...", false);

    // Adding Elements to their containers (order matters!)
    p.add(l2);
    p.add(&l4);
    w.add(&l1);
    w.add(l3);
    w.add(&l5);
    w.add(&p);
    w.add(&l6);

    // Seting up and displaying the Window
    w.setup();
    w.unsafe_clear();
    w.display();
    getchar();

    // Modifying Elements:
    l1.toggle_visible();
    l2->set_str("Vertical now!", true);
    l5.set_pos(5, 22);

    // Redisplaying Window
    w.display();
    getchar();

    return 0;
}