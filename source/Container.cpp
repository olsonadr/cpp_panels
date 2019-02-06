/*
 *  Container class. It is an Element with dimensions that has an array of
 *  Elements, which it can compile into one 2D array of characters for
 *  rendering of many layered elements.
 */

#include "../headers/Container.hpp"

// Constructors + Destructors + Operator Overloads
Container::Container(int pos_x, int pos_y,
                     int width, int height,
                     const char *type, const char *name)
    : Element(pos_x, pos_y, type, name),
      members(new Element *[1]),
      n_members(0),
      len_members(1)
{
    char **merged_arr = new char *[height];
    for (int row = 0; row < height; row++)
    {
        merged_arr[row] = new char[width];
    }

    this->dim = {
        .x = width,
        .y = height};
}

Container::Container(const Container &old_container)
    : Element(static_cast<Element>(old_container)),
      members(new Element *[old_container.len_members]),
      n_members(old_container.n_members),
      len_members(old_container.len_members)
{
    // Merged array
    this->merged_arr = new char *[old_container.dim.y];
    for (int row = 0; row < old_container.dim.y; row++)
    {
        this->merged_arr[row] = new char[old_container.dim.x];

        for (int col = 0; col < old_container.dim.x; col++)
        { /* Copy contents of merged_arr */

            this->merged_arr[row][col] = old_container.merged_arr[row][col];
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
        for (int row = 0; row < this->dim.y; row++)
        {
            delete[] this->merged_arr[row];
        }
        delete[] this->merged_arr;

        this->merged_arr = new char *[old_container.dim.y];
    }

    for (int row = 0; row < old_container.dim.y; row++)
    {
        if (needs_realloc)
        {
            this->merged_arr[row] = new char[old_container.dim.x];
        }

        for (int col = 0; col < old_container.dim.x; col++)
        { /* Copy contents of merged_arr */

            this->merged_arr[row][col] = old_container.merged_arr[row][col];
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
    delete[] this->members;
    for (int row = 0; row < this->dim.y; row++)
    {
        delete[] this->merged_arr[row];
    }
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

void Container::reset_merged()
{
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            this->merged_arr[row][col] = ' ';
        }
    }
}

// Public

/* Add a single Element to members, growing members as needed */
void Container::add(Element passed_element)
{
    while (this->n_members + 1 >= this->len_members)
    { /* The members arr would be over capacity */
        grow_members();
    }

    this->members[n_members] = new Element(passed_element);

    this->n_members += 1;
    this->has_changed = true;
}

/* Add an arr of Elements to members, growing members as needed */
void Container::add(Element *passed_elements,
                    int n_elements)
{
    while (this->n_members + n_elements > this->len_members)
    { /* The members arr would be over capacity */
        grow_members();
    }

    for (int i = 0; i < n_elements; i++)
    {
        this->members[n_members + i] = new Element(passed_elements[i]);
    }

    this->n_members += n_elements;
    this->has_changed = true;
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
char **Container::merge()
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

                if (this->members[i]->get_type() == "Label")
                { /* Member is a Label */

                    Label *curr_member =
                        static_cast<Label *>(this->members[i]);

                    int row = curr_member->get_pos().y;
                    int col = curr_member->get_pos().x;

                    for (int j = 0; j < curr_member->get_len(); j++)
                    {
                        // Check for \n escape character
                        if (curr_member->get_str()[j] == '\\' &&
                            j + 1 < curr_member->get_len() &&
                            curr_member->get_str()[j + 1] == 'n')
                        { /* Line-break (\n) at current j */
                            j++;
                            row++;
                            if (!curr_member->get_is_vertical())
                            { /* Label is horizontal (on \n reset to left) */
                                col = curr_member->get_pos().x;
                            }
                            continue;
                        }

                        // Set position in merged arr if in bounds
                        if (row < this->dim.y &&
                            col < this->dim.x)
                        {
                            this->merged_arr[row][col] = curr_member->get_str()[j];
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

                else if (this->members[i]->get_type() == "Panel")
                { /* Member is a Panel */

                    Container *curr_member =
                        static_cast<Panel *>(this->members[i]);

                    int row;
                    int col;

                    // Merge the panel and store its result
                    char **curr_member_contents = curr_member->merge();

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
                                this->merged_arr[row][col] =
                                    curr_member_contents[m_row][m_col];
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