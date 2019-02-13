/*
 *  Container class. It is an Element with dimensions that has an array of
 *  Elements, which it can compile into one 1D buffer of characters for
 *  rendering of many layered elements.
 */

#include "Container.hpp"

// Constructors + Destructors + Operator Overloads
Container::Container(int pos_x, int pos_y,
                     int width, int height,
                     bool is_dynamic,
                     const char *type, const char *name)
    : Element(pos_x, pos_y, is_dynamic, type, name),
      members(new Element *[1]),
      n_members(0),
      len_members(1)
{
    // Contents + ends of lines
    this->merged_arr = new char[(width + 1) * height];

    this->dim = {
        .x = width,
        .y = height};
}

Container::Container(const Container &old_container, bool is_dynamic)
    : Element(old_container, is_dynamic),
      members(new Element *[old_container.len_members]),
      n_members(old_container.n_members),
      len_members(old_container.len_members)
{
    // Merged array
    this->merged_arr = new char[old_container.dim.y * old_container.dim.x];
    for (int row = 0; row < old_container.dim.y; row++)
    {
        for (int col = 0; col < old_container.dim.x; col++)
        { /* Copy contents of merged_arr */

            this->merged_arr[(row * old_container.dim.x) + col] =
                old_container.merged_arr[(row * old_container.dim.x) + col];
        }
    }

    // Members array
    for (int i = 0; i < old_container.n_members; i++)
    { /* Copy contents of members array */

        this->members[i] = old_container.members[i];
    }

    // Dimensions
    this->dim = {
        .x = old_container.dim.x,
        .y = old_container.dim.y};
}

void Container::operator=(const Container &old_container)
{
    Element::operator=(static_cast<Element>(old_container));

    // Merged array
    bool needs_realloc = this->dim.x != old_container.dim.x ||
                         this->dim.y != old_container.dim.y;

    if (needs_realloc)
    { /* Delete and start re-allocating (different dimensions) */

        delete[] this->merged_arr;
        this->merged_arr = new char[old_container.dim.y * old_container.dim.x];
    }

    for (int row = 0; row < old_container.dim.y; row++)
    {
        for (int col = 0; col < old_container.dim.x; col++)
        { /* Copy contents of merged_arr */

            this->merged_arr[(row * old_container.dim.x) + col] =
                old_container.merged_arr[(row * old_container.dim.x) + col];
        }
    }
    // End merged array

    // Members array
    if (this->len_members != old_container.len_members)
    {
        delete[] this->members;
        this->members = new Element *[old_container.len_members];
    }
    for (int i = 0; i < old_container.n_members; i++)
    { /* Copy contents of members array */

        this->members[i] = old_container.members[i];
    }
    this->n_members = old_container.n_members;
    this->len_members = old_container.len_members;
    // End members array

    // Dimensions
    this->pos.x = old_container.dim.x;
    this->pos.y = old_container.dim.y;
}

Container::~Container()
{
    for (int i = 0; i < this->n_members; i++)
    {
        if (this->members[i]->get_is_dynamic())
        {
            delete this->members[i];
        }
    }
    delete[] this->members;
    delete[] this->merged_arr;
}

// Protected
void Container::grow_members()
{
    Element *temp_members[this->n_members];
    for (int i = 0; i < this->n_members; i++)
    {
        temp_members[i] = this->members[i];
    }
    delete[] this->members;

    this->len_members *= 2;
    this->members = new Element *[this->len_members * 2];

    for (int i = 0; i < this->n_members; i++)
    {
        this->members[i] = temp_members[i];
    }
}

/*
 * Resets the merged buffer back to 'empty' state full of spaces with \n chars
 * at the end of each line.
 */
void Container::reset_merged()
{
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            this->merged_arr[(row * this->dim.x) + col] = ' ';
        }

        if (row < this->dim.y - 1)
        { /* For all but the last rows (which has a \0 instead). */

            this->merged_arr[(row * this->dim.x) + this->dim.x] = '\n';
        }
    }

    // The last chararcter of the buffer
    this->merged_arr[((this->dim.y - 1) * this->dim.x) + this->dim.x] = '\0';
}

// Public
/*
 * Add an Element to members, growing members as needed, takes a reference.
 * Changing the Element outside affects it inside as well.
*/
void Container::add(Element &passed_element)
{

    while (this->n_members + 1 >= this->len_members)
    { /* The members arr would be over capacity */

        grow_members();
    }

    this->members[n_members] = &passed_element;

    this->n_members += 1;
    this->has_changed = true;
}

/* 
 * Adds Element to members, Element is not copied, so changing it outside
 * affects it inside. Grows members as needed, takes an Element pointer.
 */
void Container::add(Element *passed_element)
{
    if (strcmp(passed_element->get_type(), "Window") != 0)
    {
        while (this->n_members + 1 >= this->len_members)
        { /* The members arr would be over capacity */

            grow_members();
        }

        this->members[n_members] = passed_element;

        this->n_members += 1;
        this->has_changed = true;
    }
}

/* Remove the Element at passed index from the members array */
void Container::remove(int index)
{
    for (int i = index + 1; i < this->n_members; i++)
    {
        this->members[i - 1] = this->members[i];
    }

    this->members[n_members - 1] = nullptr;
    this->n_members--;
    this->has_changed = true;
}

/* 
 * Merges the members of the container down into the single-layer
 * of chars held in merged_arr, but only if it has been updated and
 * so must be re-compiled or merged, returns merged_arr.
 */
char *Container::merge()
{
    bool must_update = this->has_changed;
    if (must_update == false)
    {
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_has_changed())
            {
                must_update = true;
                this->members[i]->reset_has_changed();
            }
        }
    }

    if (must_update)
    {
        reset_merged();
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_is_visible())
            { /* Member is visible, will be layered onto container's output */
                if (strcmp(this->members[i]->get_type(), "Label") == 0)
                { /* Member is a Label */

                    Label *curr_member =
                        static_cast<Label *>(this->members[i]);

                    int row = curr_member->get_pos().y;
                    int col = curr_member->get_pos().x;

                    for (int j = 0; j < curr_member->get_len(); j++)
                    {
                        if (curr_member->get_str()[j] == '\n')
                        { /* Line-break (\n) at current j, reset to left edge */
                            row++;
                            col = curr_member->get_pos().x;
                            continue;
                        }

                        // Set position in merged arr if in bounds
                        if (row < this->dim.y &&
                            col < this->dim.x)
                        {
                            this->merged_arr[(row * this->dim.x) + col] = curr_member->get_str()[j];
                        }

                        // Move cursor to next position for Label
                        if (curr_member->get_is_vertical())
                        {
                            row++;
                        }
                        else
                        {
                            col++;
                        }
                    }
                }

                else if (strcmp(this->members[i]->get_type(), "Border") == 0)
                { /* Member is a Border */

                    Border *curr_member =
                        static_cast<Border *>(this->members[i]);

                    for (int row = 0; row < this->dim.y; row++)
                    {
                        for (int col = 0; col < this->dim.x; col++)
                        {
                            if ((row == 0 || row == this->dim.y - 1) &&
                                (col == 0 || col == this->dim.x - 1))
                            { /* Is a corner position */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_corner_char();
                            }
                            else if (row == 0)
                            { /* The top row */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_top_char();
                            }
                            else if (row == this->dim.y - 1)
                            { /* The bottom row */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_bottom_char();
                            }
                            else if (col == 0)
                            { /* Left-most column */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_left_char();
                            }
                            else if (col == this->dim.x - 1)
                            { /* Right-most column */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_right_char();
                            }
                        }
                    }
                }

                else if (strcmp(this->members[i]->get_type(), "Panel") == 0)
                { /* Member is an implemented Container */

                    Container *curr_member =
                        static_cast<Container *>(this->members[i]);

                    int row;
                    int col;

                    // Merge the panel and store its result
                    char *curr_member_contents = curr_member->merge();

                    for (int m_row = 0; m_row < curr_member->get_dim().y; m_row++)
                    { /* For each row in curr_member */

                        row = curr_member->get_pos().y + m_row;

                        for (int m_col = 0; m_col < curr_member->get_dim().x; m_col++)
                        { /* For each column in curr_member */

                            col = curr_member->get_pos().x + m_col;
                            // Set position in merged arr if in bounds
                            if (row < this->dim.y &&
                                col < this->dim.x)
                            {
                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member_contents[(m_row * curr_member->get_dim().x) + m_col];
                            }
                        }
                    }
                }
            }
        }
    }
    this->has_changed = false;
    return this->merged_arr;
}