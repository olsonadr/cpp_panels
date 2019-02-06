/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#include "../headers/Window.hpp"

// Methods

/* Update and print the contents of the buffer */
void Window::print_merged()
{
    merge();
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            std::cout << this->merged_arr[row][col];
        }
        std::cout << std::endl;
    }
}