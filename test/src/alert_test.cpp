#include "Window.hpp"
#include "Alert.hpp"

//#include <stdio.h>

int main()
{
    /* Alert Test */

    // Setup
    Window my_w(100, 20);
    my_w.open();
    Alert my_a("Alert Message!! (20)\nSecond lineeeeeee! (23)\nAnd a third!!!! (20)\nPress enter to advance... (30)\n",
               STATIC_ELEMENT);

    // Add Alert to Window
    my_w.add(my_a);

    // Making Alert Visible
    my_a.make_visible();

    // Display (and wait for enter)
    my_w.display();
    getchar();

    // Changing attribute
    my_a.set_size_percentage(1.f / 2);

    // Redisplaying
    my_w.display();
    getchar();

    // Cleanup
    my_w.close();

    /* End Alert Test */

    return 0;
}
