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
                     const char * type, const char * name)
    : Element(pos_x, pos_y, is_dynamic, type, name),
      members(new Element * [1]), n_members(0),
      len_members(1), bg_char(' ')
{
    // Contents + ends of lines
    this->merged_arr = new char[(width + 1) * height];

    this->dim =
    {
        .x = width,
        .y = height
    };
}

Container::Container(const Container & old_container, bool is_dynamic)
    : Element(old_container, is_dynamic),
      members(new Element * [old_container.len_members]),
      n_members(old_container.n_members),
      len_members(old_container.len_members),
      bg_char(old_container.bg_char)
{
    // Merged array
    this->merged_arr = new char[old_container.dim.y * old_container.dim.x];

    for (int row = 0; row < old_container.dim.y; row++)
    {
        for (int col = 0; col < old_container.dim.x; col++)
        {
            /* Copy contents of merged_arr */

            this->merged_arr[(row * old_container.dim.x) + col] =
                old_container.merged_arr[(row * old_container.dim.x) + col];
        }
    }

    // Members array
    for (int i = 0; i < old_container.n_members; i++)
    {
        /* Copy contents of members array */

        this->members[i] = old_container.members[i];
    }

    // Dimensions
    this->dim =
    {
        .x = old_container.dim.x,
        .y = old_container.dim.y
    };
}

void Container::operator=(const Container & old_container)
{
    Element::operator=(static_cast<Element>(old_container));

    // Merged array
    bool needs_realloc = this->dim.x != old_container.dim.x ||
                         this->dim.y != old_container.dim.y;

    if (needs_realloc)
    {
        /* Delete and start re-allocating (different dimensions) */

        delete[] this->merged_arr;
        this->merged_arr = new char[old_container.dim.y * old_container.dim.x];
    }

    for (int row = 0; row < old_container.dim.y; row++)
    {
        for (int col = 0; col < old_container.dim.x; col++)
        {
            /* Copy contents of merged_arr */

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
    {
        /* Copy contents of members array */

        this->members[i] = old_container.members[i];
    }

    this->n_members = old_container.n_members;
    this->len_members = old_container.len_members;
    // End members array

    // Dimensions
    this->pos.x = old_container.dim.x;
    this->pos.y = old_container.dim.y;

    // Background character
    this->bg_char = old_container.bg_char;
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
/*
 * Should only be called when members needs to increase in size (when adding an
 * element would put it over capacity. Doubles the length of the members array,
 * modifying memory as needed.
 */
void Container::grow_members()
{
    Element * temp_members[this->n_members];

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
 * Sets the background character that is treated as empty space (that displays
 * the stuff behind it) when seen by merge.
 */
void Container::set_bg_char(char new_bg_char)
{
    this->bg_char = new_bg_char;
    this->has_changed = true;
}

/*
 * Resets the merged buffer back to 'empty' state full of spaces with \n chars
 * at the end of each line (using bg_char to fill terminal).
 */
void Container::reset_merged()
{
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            this->merged_arr[(row * this->dim.x) + col] = this->bg_char;
        }

        if (row < this->dim.y - 1)
        {
            /* For all but the last rows (which has a \0 instead). */

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
void Container::add(Element & passed_element)
{

    while (this->n_members + 1 >= this->len_members)
    {
        /* The members arr would be over capacity */

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
void Container::add(Element * passed_element)
{
    if (strcmp(passed_element->get_type(), "Window") != 0)
    {
        while (this->n_members + 1 >= this->len_members)
        {
            /* The members arr would be over capacity */

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
 * Overriden get_has_changed function, which (instead of just checking
 * this's has_changed field) also checks its members.
 */
bool Container::get_has_changed()
{
    if (this->has_changed == false)
    {
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_has_changed() == true)
            {
                return true;
            }
        }
    }

    return this->has_changed;
}

/*
 * Recursively checks all the members (and their member's, etc.) to
 * see if any have changed and so the array must update.
 */
bool Container::check_must_update()
{
    bool must_update = this->has_changed;

    if (must_update == false)
    {
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_has_changed() == true)
            {
                must_update = true;
            }
        }
    }

    return must_update;
}

/*
 * Merges the members of the container down into the single-layer
 * of chars held in merged_arr, but only if it has been updated and
 * so must be re-compiled or merged, returns merged_arr.
 */
char * Container::merge()
{
    bool must_update = check_must_update();

    if (must_update)
    {
        reset_merged();

        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_is_visible())
            {
                /* Member is visible, will be layered onto container's output */

                if (strcmp(this->members[i]->get_type(), "Label") == 0)
                {
                    /* Member is a Label */

                    Label * curr_member =
                        static_cast<Label *>(this->members[i]);

                    int row = curr_member->get_pos().y;
                    int col = curr_member->get_pos().x;

                    for (int j = 0; j < curr_member->get_len(); j++)
                    {
                        if (curr_member->get_str()[j] == '\n')
                        {
                            /* Line-break (\n) at current j, reset to left edge */

                            row++;
                            col = curr_member->get_pos().x;
                            continue;
                        }

                        // Sets the appropriate char in buffer
                        if (row >= 0 && row < this->dim.y &&
                                col >= 0 && col < this->dim.x)
                        {
                            /* Is in bounds at index */

                            if (curr_member->get_str()[j] != '`')
                            {
                                /* Is not transparent char at index */

                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_str()[j];
                            }
                        }

                        // Move cursor to next position for Label
                        if (curr_member->get_is_vertical() == VERTICAL_LABEL)
                        {
                            row++;
                        }
                        else
                        {
                            col++;
                        }
                    }
                }

                else if (strcmp(this->members[i]->get_type(), "Alert") == 0)
                {
                    /* Member is an Alert */

                    Alert * curr_member =
                        static_cast<Alert *>(this->members[i]);

                    int alert_width, alert_height;
                    alert_width = 2 * this->dim.x / 3;
                    alert_height = 2 * this->dim.y / 3;

                    int alert_x, alert_y;
                    alert_x = this->dim.x / 6;
                    alert_y = this->dim.y / 6;

                    int message_width, message_height;
                    message_width = curr_member->get_x_span();
                    message_height = curr_member->get_y_span();

                    int message_x, message_y;
                    message_x = alert_x + (alert_width / 2) - (message_width / 2);
                    message_y = alert_y + (alert_height / 2) - (message_height / 2);

                    /* debug */
		    //printf("alert_x = %d, alert_y = %d\nalert_width = %d, alert_height= %d\nmessage_x = %d, message_y = %d\nmessage_width = %d, message_height = %d\n",
		    //       alert_x, alert_y, alert_width, alert_height,
		    //       message_x, message_y, message_width, message_height);
		    //getchar();
                    /* end debug */
		    
		    int row = 0;
		    int col = 0;

                    for (row = alert_y; row < alert_y + alert_height; row++)
                    {
                        for (col = alert_x; col < alert_x + alert_width; col++)
                        {
                            // Handle the Alert's Border
                            if ((row == alert_y || row == alert_y + alert_height - 1) &&
                                    (col == alert_x || col == alert_x + alert_width - 1))
                            {
                                /* Is a corner position */

                                if (curr_member->get_corner_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_corner_char();
                                }
                            }
                            else if (row == alert_y)
                            {
                                /* The top row */

                                if (curr_member->get_top_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_top_char();
                                }
                            }
                            else if (row == alert_y + alert_height - 1)
                            {
                                /* The bottom row */

                                if (curr_member->get_bottom_char() != '`')
                                {
                                    /* Is not transparent char at index */
                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_bottom_char();
                                }
                            }
                            else if (col == alert_x)
                            {
                                /* Left-most column */

                                if (curr_member->get_left_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_left_char();
                                }
                            }
                            else if (col == alert_x + alert_width - 1)
                            {
                                /* Right-most column */

                                if (curr_member->get_right_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_right_char();
                                }
                            }
                            else
                            {
                                /* In body of Alert, fill with bg_char */
				
                                this->merged_arr[(row * this->dim.x) + col] =
                                    curr_member->get_bg_char();
                            }
                        }
                    }

                    // Handle Message
                    row = message_y;
                    col = message_x;

		    /* debug */
		    //printf("row = %d, col = %d", row, col);
		    //getchar();
		    /* end debug */

		
		    for (int j = 0; j < curr_member->get_len(); j++)
		    {
			/* For each character in the message */

			if (curr_member->get_message()[j] == '\n')
			{
			    /* Line-break (\n) at current j, reset to left edge */

			    row++;
			    col = message_x;
			    continue;
			}

			// Sets the appropriate char in buffer
			if (row >= alert_y && row < alert_y + alert_height &&
				col >= alert_x && col < alert_x + alert_width)
			{
			    /* Is in bounds at index */

			    if (curr_member->get_message()[j] != '`')
			    {
				/* Is not transparent char at index */

				this->merged_arr[(row * this->dim.x) + col] =
				    curr_member->get_message()[j];
			    }
			}

			// Move cursor to next position for Alert
			col++;
		    }
                }

                else if (strcmp(this->members[i]->get_type(), "Border") == 0)
                {
                    /* Member is a Border */

                    Border * curr_member =
                        static_cast<Border *>(this->members[i]);

                    for (int row = 0; row < this->dim.y; row++)
                    {
                        for (int col = 0; col < this->dim.x; col++)
                        {
                            if ((row == 0 || row == this->dim.y - 1) &&
                                    (col == 0 || col == this->dim.x - 1))
                            {
                                /* Is a corner position */

                                if (curr_member->get_corner_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_corner_char();
                                }
                            }
                            else if (row == 0)
                            {
                                /* The top row */

                                if (curr_member->get_top_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_top_char();
                                }
                            }
                            else if (row == this->dim.y - 1)
                            {
                                /* The bottom row */

                                if (curr_member->get_bottom_char() != '`')
                                {
                                    /* Is not transparent char at index */
                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_bottom_char();
                                }
                            }
                            else if (col == 0)
                            {
                                /* Left-most column */

                                if (curr_member->get_left_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_left_char();
                                }
                            }
                            else if (col == this->dim.x - 1)
                            {
                                /* Right-most column */

                                if (curr_member->get_right_char() != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member->get_right_char();
                                }
                            }
                        }
                    }
                }

                else if (strcmp(this->members[i]->get_type(), "Console") == 0)
                {
                    /* Member is a Console */

                    Console * curr_member =
                        static_cast<Console *>(this->members[i]);

                    int row;
                    int col;

                    // Merge the container and store its result
                    char * curr_member_contents = curr_member->merge();

                    for (int m_row = 0; m_row < curr_member->get_dim().y; m_row++)
                    {
                        /* For each row in curr_member */

                        row = curr_member->get_pos().y + m_row;

                        for (int m_col = 0; m_col < curr_member->get_dim().x; m_col++)
                        {
                            /* For each column in curr_member */

                            col = curr_member->get_pos().x + m_col;

                            // Set position in merged arr if in bounds
                            if (row >= 0 && row < this->dim.y &&
                                    col >= 0 && col < this->dim.x)
                            {
                                if (curr_member_contents[(m_row * curr_member->get_dim().x) + m_col] != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member_contents[(m_row * curr_member->get_dim().x) + m_col];
                                }
                            }
                        }
                    }
                }

                else if (strcmp(this->members[i]->get_type(), "Panel") == 0 ||
                         strcmp(this->members[i]->get_type(), "List") == 0)
                {
                    /* Member is an implemented Container */

                    Container * curr_member =
                        static_cast<Container *>(this->members[i]);

                    int row;
                    int col;

                    // Merge the container and store its result
                    char * curr_member_contents = curr_member->merge();

                    for (int m_row = 0; m_row < curr_member->get_dim().y; m_row++)
                    {
                        /* For each row in curr_member */

                        row = curr_member->get_pos().y + m_row;

                        for (int m_col = 0; m_col < curr_member->get_dim().x; m_col++)
                        {
                            /* For each column in curr_member */

                            col = curr_member->get_pos().x + m_col;

                            // Set position in merged arr if in bounds
                            if (row >= 0 && row < this->dim.y &&
                                    col >= 0 && col < this->dim.x)
                            {
                                if (curr_member_contents[(m_row * curr_member->get_dim().x) + m_col] != '`')
                                {
                                    /* Is not transparent char at index */

                                    this->merged_arr[(row * this->dim.x) + col] =
                                        curr_member_contents[(m_row * curr_member->get_dim().x) + m_col];
                                }
                            }
                        }
                    }
                }
            }

            this->members[i]->reset_has_changed();
        }
    }

    this->has_changed = false;
    return this->merged_arr;
}

/*
 * Finds and returns a pointer to the Element in the members list with the given
 * identifying name, returns nullptr if not found.
 */
Element * Container::find(const char * name)
{
    for (int i = 0; i < this->n_members; i++)
    {
        if (strcmp(this->members[i]->get_name(), name) == 0)
        {
            /* Current member is Element being searched for */

            return this->members[i];
        }
        else if (strcmp(this->members[i]->get_type(), "Panel") == 0 ||
                 strcmp(this->members[i]->get_type(), "List") == 0)
        {
            /* Current member is a container object that can be recursed */

            Container * curr_member = static_cast<Container *>(this->members[i]);
            Element * m_result = curr_member->find(name);

            if (m_result != nullptr)
            {
                /* If it was found in that member */

                return m_result;
            }
        }
    }

    return nullptr;
}

/*
 * Finds and returns the global coordinates of the Element with the given name,
 * returns (-1,-1) if it is not found.
 */
int_duple Container::find_global_pos(const char * name)
{
    struct int_duple result =
    {
        .x = -1,
        .y = -1
    };

    for (int i = 0; i < this->n_members; i++)
    {
        if (strcmp(this->members[i]->get_name(), name) == 0)
        {
            /* Current member is Element being searched for */

            result.x = this->get_pos().x + this->members[i]->get_pos().x;
            result.y = this->get_pos().y + this->members[i]->get_pos().y;

            return result;
        }
        else if (strcmp(this->members[i]->get_type(), "Panel") == 0 ||
                 strcmp(this->members[i]->get_type(), "List") == 0)
        {
            /* Current member is a container object that can be recursed */

            Container * curr_member = static_cast<Container *>(this->members[i]);
            struct int_duple m_result = curr_member->find_global_pos(name);

            if (m_result.x != -1)
            {
                /* If it was found in that member */

                result.x = this->get_pos().x + m_result.x;
                result.y = this->get_pos().y + m_result.y;

                return result;
            }
        }
    }

    return result;
}
