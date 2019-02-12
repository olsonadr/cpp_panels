/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#include "../headers/Window.hpp"

// Protected
/*
 * Resizes the terminal window if possible using ANSI an escape sequence.
 */
void Window::resize_terminal()
{
    char resize_str[26];
    sprintf(resize_str,
            "printf '\e[8;%d;%dt'",
            this->dim.y + 1, this->dim.x); // ANSI sequence, resizes terminal
    system(resize_str);
}

// Public
// Destructor
Window::~Window()
{
    system("printf '\e[?25h'");
}

// Methods
/*
 * Update and print the contents of the buffer
 */
void Window::display()
{
    merge();
    // std::cout << std::endl;
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            std::cout << this->merged_arr[row][col];
        }
        std::cout << std::endl;
    }
    system("printf '\e[H'");
}

/*
 * Clears screen, makes the cursor invisible, and resizes the terminal, should
 * be called before displaying at all.
*/
void Window::setup()
{
    // system("printf '\e[?25l'"); // ANSI sequence, makes cursor invisible
    system("printf '\e[2J'"); // ANSI clear of current screen
    resize_terminal();
}

/*
 * Clears the screen and the character buffer above the screen using OS-specific
 * commands system("CLS") and system("clear") and ANSI espcape sequences. This is
 * not safe as it uses the OS's commands which could have been modified, and can
 * also be somewhat slower.
 */
void Window::unsafe_clear()
{
    system("CLS");            // Windows OS clear
    system("tput clear");     // Unix terminal clear
    system("printf '\e[2J'"); // ANSI clear of current screen
}