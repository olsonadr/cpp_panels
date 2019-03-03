#include "Window.hpp"
#include "Panel.hpp"
#include "Border.hpp"
#include "Console.hpp"

//#include <stdio.h>

int main()
{
    /* Console Test */

    // Setup
    int window_width = 70, window_height = 30;
    int panel_pos_x = 8, panel_pos_y = 3, panel_width = 42, panel_height = 22;
    int console_pos_x = 1, console_pos_y = 1, console_width = 40, console_height = 20,
        console_history_max = 20;
    char border_corners = '+', border_top_and_bot = '-', border_left_and_right = '|';

    Window my_w(window_width, window_height);
    Panel my_p(panel_pos_x, panel_pos_y, panel_width, panel_height, STATIC_ELEMENT);
    Console my_c(console_pos_x, console_pos_y, console_width, console_height,
                 console_history_max, STATIC_ELEMENT, "my-console");
    Border my_b(border_corners, border_top_and_bot, border_left_and_right, STATIC_ELEMENT);


    // Add Things to Panel
    my_p.add(my_b);
    my_p.add(my_c);

    // Add Panel to Window
    my_w.add(my_p);


    // Set Attributes
    my_c.setup_input(my_w.find_global_pos("my-console"));
    my_c.set_display_input_line(false);


    // Open + Display Window
    my_w.open();
    my_w.unsafe_clear();
    my_w.display();


    // Output Three Times
    my_c.output("output numero 1");
    my_c.output("output number\ndos! (with line-break)");
    my_c.output("\nWow! Hit enter for input tests...");

    // Redisplay and Pause
    my_w.display();
    my_c.pause_and_flush();


    // Prompt Input and Display
    my_c.set_display_input_line(true);
    my_c.output("\nfeel free to input 4 times");
    my_w.display();

    // Get Input and Output About It
    for (int i = 0; i < 4; i++)
    {
        char buff[100];
        char buff2[200];
        my_c.input(buff, 100);
        sprintf(buff2, "You inputted '%s'\0", buff);
        my_c.output(buff2);
        my_w.display();
    }


    // Prompt unbuffered, redisplay
    my_c.output("\nNow unbuffered using input()...");
    my_c.set_display_input_line(true);
    my_w.display();

    // Get unbuffered input using input()
    char buff[2];
    char buff2[200];
    my_c.disable_buffer();
    my_c.input(buff, 2);
    my_c.enable_buffer();
    sprintf(buff2, "You pressed '%s'\0", buff);
    my_c.output(buff2);
    my_w.display();


    // Prompt unbuffered, redisplay
    my_c.output("\nNow using custom_input()...");
    my_c.set_display_input_line(false);
    my_w.display();

    // Get unbuffered input using custom_input()
    char c_buff[2];
    char c_buff2[200];
    my_c.disable_buffer();
    my_c.custom_input(c_buff, 2, false);
    my_c.enable_buffer();
    sprintf(c_buff2, "You pressed '%s'\0", buff);
    my_c.output(c_buff2);
    my_w.display();


    // Prompt unbuffered, redisplay
    my_c.output("\nNow using unbuffed_char_input()...");
    my_c.set_display_input_line(true);
    my_w.display();

    // Get unbuffered input using unbuffed_char_input()
    char char_input;
    char char_buff_2[200];
    char_input = my_c.unbuffed_char_input();
    sprintf(char_buff_2, "You pressed '%c'\0", char_input);
    my_c.output(char_buff_2);
    my_w.display();


    // Prompt Clear Enter
    my_c.output("\nHit enter to clear...");

    // Redisplay and Pause
    my_w.display();
    my_c.pause_and_flush();

    // Prompt Last Enter
    my_c.clear();
    my_c.output("Hit enter to quit...");

    // Redisplay and Pause
    my_w.display();
    my_c.pause_and_flush();

    // Cleanup
    my_w.close();

    /* End Console Test */

    return 0;
}
