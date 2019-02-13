/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#include "Window.hpp"

// Protected
/*
 * Resizes the terminal window if possible using ANSI an escape sequence.
 */
void Window::resize_terminal()
{
    char resize_str[16];
    sprintf(resize_str,
            "\e[8;%d;%dt",
            this->dim.y, this->dim.x); // ANSI sequence, resizes terminal
    printf(resize_str);
}

// Public
// Operator Overload
void Window::operator=(const Window &old_window)
{
    Container::operator=(old_window);
}

// Methods
/*
 * Update and print the contents of the buffer
 */
void Window::display()
{
    merge();
    printf("\e[H"); // Set cursor to top-left corner
    printf(merged_arr);
    printf("\e[H"); // Set cursor to top-left corner
}

/*
 * Clears screen, makes the cursor invisible, disables ECHO and resizes the
 * terminal, should be called before displaying at all.
*/
void Window::open()
{
    printf("\e[?25l"); // ANSI sequence, makes cursor invisible
    resize_terminal();
    merge();

    // Disable Echo
    tcgetattr(0, &this->term_info);
    this->term_info.c_lflag &= ~ECHO; /* Turn off ECHO */
    tcsetattr(0, TCSANOW, &this->term_info);
}

/*
 * All operations that get terminal ready for user to use it as normal again,
 * currently makes the cursor visible again and enables ECHO.
 */
void Window::close()
{
    printf("\e[?25h"); // Make cursor visible
    printf("\e[2J");   // ANSI clear of current screen
    printf("\e[H");    // Set cursor to top-left corner

    // Restore Echo
    this->term_info.c_lflag |= ECHO; /* Turn on ECHO */
    tcsetattr(0, TCSANOW, &this->term_info);
}

/*
 * Clears the screen and the character buffer above the screen using OS-specific
 * commands system("CLS") and system("clear") and ANSI espcape sequences. This is
 * not safe as it uses the OS's commands which could have been modified, and can
 * also be somewhat slower.
 */
void Window::unsafe_clear()
{
    system("CLS");        // Windows OS clear
    system("tput clear"); // Unix terminal clear
    printf("\e[H");       // Set cursor to top-left corner
    // printf("\e[2J");     // ANSI clear of current screen
}