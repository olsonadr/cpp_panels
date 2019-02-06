#include "headers/cpp_panels.hpp"

int main()
{
    int width = 80;
    int height = 24;

    Panel p(20, 5, 30, 10);
    p.add(Label(5, 2, "Label Example. HA!"));
    p.add(Label(0,0,"Skeet, yaw.",true));

    Window w(width, height);
    w.add(p);
    w.add(Label(20,10, "s"));

    w.print_merged();

    return 0;
}