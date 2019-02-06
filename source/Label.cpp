/*
 *  Label class, which is the lowest level of Component. Each Label is a
 *  C-style string with a position, although it can be initialized as
 *  vertical. \n can be used in the string.
 */

#include "../headers/Label.hpp"

// Overloaded Assignment
void Label::operator=(const Label &old_label)
{
    Element::operator=(old_label);
    this->str = old_label.str;
    this->len = old_label.len;
    this->is_vertical = old_label.is_vertical;
}