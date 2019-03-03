/*
 *  Alert class. It is a Component that has only an alert message, which it
 *  centers in a box that spans most of its parent container. You interface
 *  with an Alert just like you would a Alert.
 */

#include "Alert.hpp"

// Constructors + Operators + Destructors
/*
 * Parameterized Constructor
 */
Alert::Alert(const char * message,
             bool is_dynamic,
             const char * name)
    : Element(0, 0, is_dynamic, "Alert", name),
      message(message), size_percentage(3.f / 4),
      border(new Border('#', '-', '|', DYNAMIC_ELEMENT)),
      bg_char(' ')
{
    make_invisible();

    this->len = 0;

    while (this->message[len] != '\0')
    {
        this->len++;
    }
}


/*
 * Copy Constructor
 */
Alert::Alert(const Alert & old_alert, bool is_dynamic)
    : Element(old_alert, is_dynamic),
      message(old_alert.message),
      size_percentage(old_alert.size_percentage),
      len(old_alert.len),
      bg_char(old_alert.bg_char)
{
    make_invisible();
    this->border = new Border(*old_alert.border);
}


/*
 * Overloaded Assignment
 */
void Alert::operator=(const Alert & old_alert)
{
    make_invisible();
    Element::operator=(old_alert);
    this->message = old_alert.message;
    this->size_percentage = old_alert.size_percentage;
    this->len = old_alert.len;
    this->border->operator=(*old_alert.border);
    this->bg_char = old_alert.bg_char;
}


/*
 * Deletes all used dynamic memory.
 */
Alert::~Alert()
{
    if (border->get_is_dynamic() == DYNAMIC_ELEMENT)
    {
        delete border;
    }
}


// Methods
/*
 * Sets the message field and len, modifying memory as needed, setting has_changed
 */
void Alert::set_message(const char * new_val)
{
    this->has_changed = true;
    this->message = new_val;
    this->len = 0;

    while (this->message[len] != '\0')
    {
        this->len++;
    }
}


/*
 * Sets the Border of this Alert to a passed Border pointer, so it can be modified
 * ouside this Alert and it will update. Takes a Border pointer.
 */
void Alert::set_border(Border * new_border)
{
    this->border = new_border;
    this->has_changed = true;
}


/*
 * Sets the Border of this Alert to a passed Border pointer, so it can be modified
 * ouside this Alert and it will update. Takes a Border object.
 */
void Alert::set_border(Border & new_border)
{
    this->border = &new_border;
    this->has_changed = true;
}


/*
 * Sets the background character for this Alert to the passed character, flagging
 * that the Alert must be updated.
 */
void Alert::set_bg_char(char new_bg_char)
{
    this->bg_char = new_bg_char;
    this->has_changed = true;
}


/*
 * Sets the percentage of its parent container that the Alert will now cover,
 * defaults to 3/4.
 */
void Alert::set_size_percentage(float new_val)
{
    this->size_percentage = new_val;
    this->has_changed = true;
}


/*
 * Returns the number of characters this Alert's message spans horizontally.
 */
int Alert::get_x_span()
{
    int longest = 0;
    int curr = -1;

    for (int i = 0; i < this->len - 1; i++)
    {
        curr++;

        if (this->message[i + curr] == '\n'
                || this->message[i + curr] == '\0')
        {
            /* Found end of line */

            if (curr > longest)
            {
                /* This stretch until newline was longest */

                longest = curr;
            }

            i += curr;
            curr = -1;
        }
    }

    return longest;
}


/*
 * Returns the number of characters this Alert spans horizontally.
 */
int Alert::get_y_span()
{
    int lines = 1;

    for (int i = 0; i < this->len - 1; i++)
    {
        /* len - 1 because last char being '\n' shouldn't count */

        if (this->message[i] == '\n')
        {
            /* New-line found */

            lines++;
        }
    }

    return lines;
}


/*
 * Returns whether this or its Border has changed.
 */
bool Alert::get_has_changed()
{
    return this->has_changed || this->border->get_has_changed();
}


/*
 * Resets that this and its Border may have changed.
 */
void Alert::reset_has_changed()
{
    this->has_changed = false;
    this->border->reset_has_changed();
}
