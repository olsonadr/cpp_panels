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
      is_vertical(is_vertical), str(str), dynamic_str(false)
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
      is_vertical(HORIZONTAL_LABEL), str(str),
      dynamic_str(false)
{
    this->len = 0;

    while (this->str[len] != '\0')
    {
        this->len++;
    }
}

// Copy Constructor
Label::Label(const Label & old_label, bool is_dynamic)
    : Element(old_label, is_dynamic),
      len(old_label.len), str(old_label.str),
      is_vertical(old_label.is_vertical),
      dynamic_str(old_label.dynamic_str) {}

// Destructor
Label::~Label()
{
    if (this->dynamic_str == true)
    {
        delete[] this->str;
    }
}

// Overloaded Assignment
void Label::operator=(const Label & old_label)
{
    Element::operator=(old_label);
    this->len = old_label.len;
    this->is_vertical = old_label.is_vertical;
    this->dynamic_str = old_label.dynamic_str;
    this->str = old_label.str;
}

// Methods
/*
 * Sets the str field and len, modifying memory as needed, setting has_changed.
 */
void Label::set_str(const char * new_val,
                    bool is_vertical)
{
    this->has_changed = true;
    this->is_vertical = is_vertical;
    this->dynamic_str = false;
    this->str = new_val;
    this->len = 0;

    while (this->str[len] != '\0')
    {
        this->len++;
    }
}

/*
 * Sets the str field and len, copying the passed cstring to new dynamic memory,
 * modifying memory as needed, setting has_changed.
 */
void Label::set_str_cpy(const char * new_val,
                        bool is_vertical)
{
    this->has_changed = true;
    this->is_vertical = is_vertical;
    this->len = 0;

    while (new_val[len] != '\0')
    {
        this->len++;
    }

    char * str_buff = new char[this->len + 1];
    sprintf(str_buff, "%s\0", new_val);
    this->str = str_buff;
    this->dynamic_str = true;
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
