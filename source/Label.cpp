/*
 *  Label class, which is the lowest level of Component. Each Label is a
 *  C-style string with a position, although it can be initialized as
 *  vertical. \n can be used in the string.
 */

#include "Label.hpp"

// Constructor
Label::Label(int pos_x, int pos_y,
             const char * str,
             bool is_dynamic,
             bool is_vertical,
             const char * name)
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
             const char * str,
             bool is_dynamic,
             const char * name)
    : Element(pos_x, pos_y, is_dynamic, "Label", name),
      str(str), is_vertical(HORIZONTAL_LABEL)
{
    this->len = 0;

    while (this->str[len] != '\0')
    {
        this->len++;
    }
}

// Overloaded Assignment
void Label::operator=(const Label & old_label)
{
    Element::operator=(old_label);
    this->str = old_label.str;
    this->len = old_label.len;
    this->is_vertical = old_label.is_vertical;
}

// Methods
/*
 * Sets the str field and len, modifying memory as needed, setting has_changed
 */
void Label::set_str(const char * new_val,
                    bool is_vertical)
{
    this->has_changed = true;
    this->str = new_val;
    this->is_vertical = is_vertical;
    this->len = 0;

    while (this->str[len] != '\0')
    {
        this->len++;
    }
}

/*
 * Sets whether the Label is vertically oriented.
 */
void Label::set_is_vertical(bool is_vertical)
{
    this->has_changed = true;
    this->is_vertical = is_vertical;
}

/*
 * Returns the number of characters this Label spans horizontally.
 */
int Label::get_x_span()
{
    int longest = 0;
    int curr = -1;

    for (int i = 0; i < this->len; i++)
    {
        curr++;

        if (this->str[curr] == '\n')
        {
            /* Found end of line */

            if (curr > longest)
            {
                /* This stretch until newline was longest */

                longest = curr;
            }
        }
    }

    return longest;
}

/*
 * Returns the number of characters this Label spans horizontally.
 */
int Label::get_y_span()
{
    int lines = 1;

    for (int i = 0; i < this->len - 1; i++)
    {
        /* len - 1 because last char being '\n' shouldn't count */

        if (this->str[i] == '\n')
        {
            /* New-line found */

            lines++;
        }
    }

    return lines;
}
