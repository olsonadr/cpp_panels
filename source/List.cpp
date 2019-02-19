/*
 *  List class, is a container wherein its members are listed in order,
 *  and removing or toggling the visibility of an element shifts the other
 *  Elements upward, the dimensions of the list depend on the size of its
 *  members.
 */

#include "List.hpp"

// Constructors + Destructors + Operator Overloads
List::List(int pos_x, int pos_y,
           int other_dimension,
           bool is_dynamic,
           bool is_vertical,
           const char * name)
    : Container(pos_x, pos_y,
                (is_vertical == VERTICAL_LIST) ? (other_dimension) : (0),
                (is_vertical == HORIZONTAL_LIST) ? (0) : (other_dimension),
                is_dynamic, name),
      is_vertical(is_vertical),
      padding(0),
      margins(0)
{
    this->has_changed = true;
    update();
}

List::List(int pos_x, int pos_y,
           int other_dimension,
           bool is_dynamic,
           const char * name)
    : Container(pos_x, pos_y,
                (is_vertical == VERTICAL_LIST) ? (other_dimension) : (0),
                (is_vertical == HORIZONTAL_LIST) ? (0) : (other_dimension),
                is_dynamic, name),
      is_vertical(VERTICAL_LIST),
      padding(0),
      margins(0)
{
    this->has_changed = true;
    update();
}

List::List(const List & old_list, bool is_dynamic)
    : Container(old_list, is_dynamic),
      is_vertical(old_list.is_vertical),
      padding(old_list.padding),
      margins(old_list.margins)
{
    this->has_changed = true;
    update();
}

void List::operator=(const List & old_list)
{
    Container::operator=(old_list);
    this->has_changed = true;
    this->padding = old_list.padding;
    this->margins = old_list.margins;
    update();
}

// Protected Methods
/*
 * Modifies the positions of the list's members to make it fit the list format.
 * The prior values are not stored, so this is permanent (unless called again).
 * Also modifies this->dim so it is accurately merged. Leaves borders alone.
 */
void List::update()
{
    /* Check whether it needs to update and if any are not borders */
    bool padding_fix = false;
    bool must_update = this->has_changed;

    if (must_update == false)
    {
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_has_changed())
            {
                must_update = true;
            }

            if (strcmp(this->members[i]->get_type(), "Border") != 0)
            {
                padding_fix = true;
            }
        }
    }

    /* Update if needed */
    if (must_update)
    {
        int curr_line = margins;

        for (int i = 0; i < this->n_members; i++)
        {

            if (this->members[i]->get_is_visible())
            {
                /* If member is visible (considered) */

                if (strcmp(this->members[i]->get_type(), "Label") == 0)
                {
                    /* Member is a Label */

                    Label * curr_member = static_cast<Label *>(this->members[i]);

                    if (this->is_vertical == VERTICAL_LIST)
                    {
                        /* This list is vertical */

                        this->members[i]->set_pos(margins, curr_line);
                        curr_line += curr_member->get_y_span();
                    }
                    else
                    {
                        /* This list is horizontal */

                        this->members[i]->set_pos(curr_line, margins);
                        curr_line += curr_member->get_x_span();
                    }
                }
                else if (strcmp(this->members[i]->get_type(), "Container") == 0)
                {
                    /* If member is a Container */

                    Container * curr_member = static_cast<Container *>(this->members[i]);

                    if (this->is_vertical == VERTICAL_LIST)
                    {
                        /* This list is vertical */

                        this->members[i]->set_pos(margins, curr_line);
                        curr_line += curr_member->get_dim().y;
                    }
                    else
                    {
                        /* This list is horizontal */

                        this->members[i]->set_pos(curr_line, margins);
                        curr_line += curr_member->get_dim().x;
                    }
                }

                curr_line += this->padding; /* Add the padding of the list */
            }
        }

        // Fix padding for last element
        if (padding_fix)
        {
            curr_line -= this->padding;
        }

        // Storing new dimension
        if (this->is_vertical == VERTICAL_LIST)
        {
            this->dim =
            {
                .x = this->dim.x,
                .y = curr_line
            };
        }
        else
        {
            this->dim =
            {
                .x = curr_line,
                .y = this->dim.y
            };
        }
    }
}

// Public Methods
void List::set_is_vertical(bool new_val, int other_dim)
{
    this->is_vertical = new_val;

    if (new_val == VERTICAL_LIST)
    {
        this->dim =
        {
            .x = other_dim,
            .y = 0
        };
    }
    else
    {
        this->dim =
        {
            .x = 0,
            .y = other_dim
        };
    }

    this->has_changed = true;
}

void List::set_padding(int new_padding)
{
    this->padding = new_padding;
    this->has_changed = true;
}

void List::set_margins(int new_margins)
{
    this->margins = new_margins;
    this->has_changed = true;
}

// Overriden
/*
 * Uses standard container merge method but updates positions + dim as needed first.
 */
char * List::merge()
{
    update();
    return this->Container::merge();
}
