#include "Window.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Border.hpp"

#include <stdio.h>
#include <time.h>

void test(Window & w, Label & l);

int main()
{
    /* Border and Label Test */

    // Creating Window
    int width = 80;  //90;
    int height = 30; //30;
    Window w(width, height);

    // Creating Elements
    Panel p(30, 10, 30, 10, STATIC_ELEMENT);
    Label l1(5, 2, "Should disappear!", STATIC_ELEMENT);
    Label transparency_test(33, 14, "Behind!", STATIC_ELEMENT);
    Label * l2 = new Label(1, 1, "Should become vertical!", DYNAMIC_ELEMENT);
    Label * l3 = new Label(10, 3, "New line escape here ->\nshould be on new line",
                           DYNAMIC_ELEMENT);
    Label l4(8, 2, "Should be cut -> Occluded?", STATIC_ELEMENT);
    Label l5(0, 20, "Should move!", STATIC_ELEMENT);
    Label l6(width - 15, height - 2, "Press enter...", STATIC_ELEMENT);
    Label cpy_test(4, 15, "replaced (cpy)", STATIC_ELEMENT);
    Label frame_count(1, 1, "Press Enter for 10000 display calls...", STATIC_ELEMENT);
    frame_count.make_invisible();
    Border b('*', '-', '|', STATIC_ELEMENT);
    p.set_bg_char('*');

    // Adding Elements to their containers (order matters!)
    p.add(b);
    p.add(l2);
    p.add(&l4);
    w.add(&l1);
    w.add(l3);
    w.add(&l5);
    w.add(transparency_test); // Under the panel
    w.add(&p);
    w.add(&l6);
    w.add(b);
    w.add(frame_count);
    w.add(cpy_test);

    // Seting up and displaying the Window
    w.open();
    w.unsafe_clear();
    w.display();
    getchar();

    // Modifying Elements:
    l1.toggle_visible();
    p.set_bg_char('`');
    l2->set_str("Vertical now!", VERTICAL_LABEL);
    l5.set_pos(6, 22);
    b.set_corner_char('+');
    frame_count.make_visible();

    // Testing Label set_str_cpy()
    test(w, cpy_test);

    // Redisplaying Window
    w.display();
    getchar();

    // Check of speed
    char i_buff[70];
    time_t start = clock();

    for (int i = 0; i < 10000; i++)
    {
        sprintf(i_buff, "Frame %.4d\0", i);
        frame_count.set_str(i_buff);
        w.display();
    }

    time_t diff = clock() - start;
    getchar();
    sprintf(i_buff, "That supposedly took %d milli-seconds!\nAverage FPS was: %.2f\0",
            diff * 1000 / CLOCKS_PER_SEC, 10000.0 / (diff / CLOCKS_PER_SEC));
    frame_count.set_str(i_buff);

    // Redisplay After
    w.display();
    getchar();

    //Cleanup
    w.close();

    /* End Border and Label Test */

    return 0;
}

void test(Window & w, Label & l)
{
    const char * wow = "amazing grace";
    l.set_str_cpy(wow);
}
