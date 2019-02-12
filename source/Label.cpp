/*
 *  Label class, which is the lowest level of Component. Each Label is a
 *  C-style string with a position, although it can be initialized as
 *  vertical. \n can be used in the string.
 */

#include "../headers/Label.hpp"

// Constructor
Label::Label(int pos_x, int pos_y,
             const char *str,
             bool is_dynamic,
             bool is_vertical,
             const char *name)
    : Element(pos_x, pos_y, is_dynamic, "Label", name),
      str(str), is_vertical(is_vertical)
{
    this->len = 0;
    while (this->str[len] != '\0')
    {
        this->len++;
    }
}

Label::Label(int pos_x, int pos_y,
             const char *str,
             bool is_dynamic,
             const char *name)
    : Element(pos_x, pos_y, is_dynamic, "Label", name),
      str(str), is_vertical(false)
{
    this->len = 0;
    while (this->str[len] != '\0')
    {
        this->len++;
    }
}


// Overloaded Assignment
void Label::operator=(const Label &old_label)
{
    Element::operator=(old_label);
    this->str = old_label.str;
    this->len = old_label.len;
    this->is_vertical = old_label.is_vertical;
}


// Methods
/*
 * Sets the str field and len, modifying memory as needed.
 */
void Label::set_str(const char *new_val,
                    bool is_vertical)
{
    this->str = new_val;
    this->is_vertical = is_vertical;
    this->len = 0;
    while (this->str[len] != '\0')
    {
        this->len++;
    }
}