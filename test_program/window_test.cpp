#include "Window.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Border.hpp"
#include "List.hpp"
#include "Console.hpp"
#include "Alert.hpp"

#include <stdio.h>
#include <time.h>

int main()
{
    /* Alert Test */
    /*
     *    // Setup
     *    Window my_w(90, 30);
     *    my_w.open();
     *    Alert my_a("Alert Message!\nSecond line!\nAnd a third!!!", STATIC_ELEMENT);
     *    [> debug <]
     *    //printf("my_a.get_x_span() = %d\nmy_a.get_y_span() = %d\n",
     *    //       my_a.get_x_span(), my_a.get_y_span());
     *    //getchar();
     *    [> end debug <]
     *
     *    // Add Alert to Window
     *    my_w.add(my_a);
     *
     *    // Making Alert Visible
     *    my_a.make_visible();
     *
     *    // Display (and wait for enter)
     *    my_w.display();
     *    getchar();
     *
     *    // Make Alert invisible
     *    //my_a.make_invisible();
     *
     *    //// Redisplay (and wait again)
     *    //my_w.display();
     *    //getchar();
     *
     *    // Cleanup
     *    my_w.close();
     */
    /* End Alert Test */


    /* Console Test */
    /*
     *    // Setup
     *    int window_width = 70, window_height = 30;
     *    int panel_pos_x = 8, panel_pos_y = 3, panel_width = 42, panel_height = 22;
     *    int console_pos_x = 1, console_pos_y = 1, console_width = 40, console_height = 20,
     *        console_history_max = 20;
     *    char border_corners = '+', border_top_and_bot = '-', border_left_and_right = '|';
     *
     *    Window my_w(window_width, window_height);
     *    Panel my_p(panel_pos_x, panel_pos_y, panel_width, panel_height, STATIC_ELEMENT);
     *    Console my_c(console_pos_x, console_pos_y, console_width, console_height,
     *                 console_history_max, STATIC_ELEMENT, "my-console");
     *    Border my_b(border_corners, border_top_and_bot, border_left_and_right, STATIC_ELEMENT);
     *
     *    // Add Things to Panel
     *    my_p.add(my_b);
     *    my_p.add(my_c);
     *
     *    // Add Panel to Window
     *    my_w.add(my_p);
     *
     *    // Set Attributes
     *    my_c.setup_input(my_w.find_global_pos("my-console"));
     *
     *    // Open + Display Window
     *    my_w.open();
     *    my_w.unsafe_clear();
     *    my_w.display();
     *
     *    // Output Twice
     *    my_c.output("output numero 1");
     *    my_c.output("output number\ndos! (with line-break)");
     *    my_c.output("yee");
     *    my_c.output("feel free to input 4 times");
     *
     *    // Redisplay and Pause
     *    my_w.display();
     *
     *    // Get Input and Output About It
     *    for (int i = 0; i < 4; i++)
     *    {
     *        char buff[100];
     *        char buff2[200];
     *        my_c.input(buff);
     *        sprintf(buff2, "You inputted '%s'\0", buff);
     *        my_c.output(buff2);
     *        my_w.display();
     *    }
     *
     *    // Prompt Last Enter
     *    my_c.output("Hit enter to quit...");
     *
     *    // Redisplay and Pause
     *    my_w.display();
     *    my_c.pause_and_flush();
     *
     *    // Cleanup
     *    my_w.close();
     */
    /* End Console Test */


    /* List Test */
    /*
     *     // Setup
     *     int list_x = 4, list_y = 2, other_dim = 10;
     *     Window my_window(100, 40);
     *     List my_list(list_x, list_y, other_dim, STATIC_ELEMENT, VERTICAL_LIST);
     *     Border my_border('+', '-', '|', STATIC_ELEMENT);
     *     Label first_label(0, 0, "Skr1234567890t!", STATIC_ELEMENT);
     *     Label second_label(0, 0, "Second skrt!", STATIC_ELEMENT);
     *     Label prompt(100 - 11, 40 - 1, "Press enter", STATIC_ELEMENT);
     *
     *     // Set attributes
     *     my_list.set_padding(1);
     *     my_window.set_bg_char('.');
     *     my_list.set_bg_char(' ');
     *
     *     // Add Labels to my_list
     *     my_list.add(first_label);
     *     my_list.add(second_label);
     *     my_list.update();
     *
     *     // Add my_list to window
     *     my_window.add(my_list);
     *     my_window.add(prompt);
     *
     *     // Open Window
     *     my_window.open();
     *     my_window.unsafe_clear();
     *     my_window.display();
     *     getchar(); // FIRST PAUSE ----------------------------------------------------*
     *
     *     // Add margins, padding, and border
     *     my_list.set_margins(1);
     *     my_list.set_padding(2);
     *     my_list.add(my_border);
     *
     *     // Redisplay
     *     my_window.display();
     *     getchar(); // SECOND PAUSE ---------------------------------------------------*
     *
     *     // Make horizontal
     *     my_list.set_is_vertical(HORIZONTAL_LIST, 3);
     *
     *     // Redisplay
     *     my_window.display();
     *     getchar(); // THIRD PAUSE ----------------------------------------------------*
     *
     *     // Toggle visibility of first label
     *     first_label.make_invisible();
     *
     *     // Redisplay
     *     my_window.display();
     *     getchar(); // FOURTH PAUSE ---------------------------------------------------*
     *
     *     // Cleanup
     *     my_window.close();
     */
    /* End List Test */


    /* find() and find_global_pos() Test */
    /*
     *    // Creating Window
     *    int width = 100;
     *    int height = 40;
     *    Window w(width, height);
     *
     *    // Creating Elements
     *    Panel p(10, 10, 40, 20, STATIC_ELEMENT, "my_panel");
     *    Label origin(0, 0, "Label at origin (made vertical hopefully)",
     *                 STATIC_ELEMENT, "my_origin_label");
     *    Label panel_label(5, 5, "Label in Panel (X at pos)",
     *                      STATIC_ELEMENT, "my_panel_label");
     *    Label indicator(1, 1, "X", STATIC_ELEMENT);
     *
     *    // Attributes
     *    p.set_bg_char('#');
     *
     *    // Adding Elements to Panel
     *    p.add(panel_label);
     *
     *    // Adding ELements to Window
     *    w.add(p);
     *    w.add(origin);
     *    w.add(indicator);
     *
     *    // Setting up and displaying Window
     *    w.open();
     *    w.display();
     *    getchar();
     *
     *    // Changing variables
     *    Element * found = w.find("my_origin_label");
     *
     *    if (found != nullptr)
     *    {
     *        if (strcmp(found->get_type(), "Label") == 0)
     *        {
     *            Label * found_label = static_cast<Label *>(found);
     *            found_label->set_is_vertical(VERTICAL_LABEL);
     *        }
     *    }
     *
     *    struct int_duple found_pos = w.find_global_pos("my_panel_label");
     *
     *    indicator.set_pos(found_pos);
     *
     *    // Redisplaying
     *    w.display();
     *
     *    getchar();
     *
     *    // Closing Window
     *    w.close();
     */
    /* End find() and find_global_pos() Test */


    /* Border and Label Test */
    /*
     *    // Creating Window
     *    int width = 80;  //90;
     *    int height = 30; //30;
     *    Window w(width, height);
     *
     *    // Creating Elements
     *    Panel p(30, 10, 30, 10, STATIC_ELEMENT);
     *    Label l1(5, 2, "Should disappear!", STATIC_ELEMENT);
     *    Label transparency_test(33, 14, "Behind!", STATIC_ELEMENT);
     *    Label * l2 = new Label(1, 1, "Should become vertical!", DYNAMIC_ELEMENT);
     *    Label * l3 = new Label(10, 3, "New line escape here ->\nshould be on new line",
     *                           DYNAMIC_ELEMENT);
     *    Label l4(8, 2, "Should be cut -> Occluded?", STATIC_ELEMENT);
     *    Label l5(0, 20, "Should move!", STATIC_ELEMENT);
     *    Label l6(width - 15, height - 2, "Press enter...", STATIC_ELEMENT);
     *    Label frame_count(1, 1, "Press Enter for 10000 display calls...", STATIC_ELEMENT);
     *    frame_count.make_invisible();
     *    Border b('*', '-', '|', STATIC_ELEMENT);
     *    p.set_bg_char('*');
     *
     *    // Adding Elements to their containers (order matters!)
     *    p.add(b);
     *    p.add(l2);
     *    p.add(&l4);
     *    w.add(&l1);
     *    w.add(l3);
     *    w.add(&l5);
     *    w.add(transparency_test); // Under the panel
     *    w.add(&p);
     *    w.add(&l6);
     *    w.add(b);
     *    w.add(frame_count);
     *
     *    // Seting up and displaying the Window
     *    w.open();
     *    w.unsafe_clear();
     *    w.display();
     *    getchar();
     *
     *    // Modifying Elements:
     *    l1.toggle_visible();
     *    p.set_bg_char('`');
     *    l2->set_str("Vertical now!", VERTICAL_LABEL);
     *    l5.set_pos(6, 22);
     *    b.set_corner_char('+');
     *    frame_count.make_visible();
     *
     *    // Redisplaying Window
     *    w.display();
     *    getchar();
     *
     *    // Check of speed
     *    char i_buff[70];
     *    time_t start = clock();
     *
     *    for (int i = 0; i < 10000; i++)
     *    {
     *        sprintf(i_buff, "Frame %.4d\0", i);
     *        frame_count.set_str(i_buff);
     *        w.display();
     *    }
     *
     *    time_t diff = clock() - start;
     *    getchar();
     *    sprintf(i_buff, "That supposedly took %d milli-seconds!\nAverage FPS was: %.2f\0",
     *            diff * 1000 / CLOCKS_PER_SEC, 10000.0 / (diff / CLOCKS_PER_SEC));
     *    frame_count.set_str(i_buff);
     *
     *    // Redisplay After
     *    w.display();
     *    getchar();
     *
     *    //Cleanup
     *    w.close();
     */
    /* End Border and Label Test */


    return 0;
}
