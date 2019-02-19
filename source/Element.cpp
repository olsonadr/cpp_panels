/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#include "Element.hpp"

Element::Element(int pos_x, int pos_y, bool is_dynamic,
                 const char * type, const char * name)
    : type(type), has_changed(true),
      is_visible(true), name(name),
      is_dynamic(is_dynamic)
{
    this->pos =
    {
        .x = pos_x,
        .y = pos_y
    };
}

Element::Element(const Element & old_element, bool is_dynamic)
{
    this->type = old_element.type;
    this->name = old_element.name;
    this->has_changed = old_element.has_changed;
    this->is_visible = old_element.is_visible;
    this->is_dynamic = is_dynamic;
    this->pos =
    {
        .x = old_element.pos.x,
        .y = old_element.pos.y
    };
}

void Element::operator=(const Element & old_element)
{
    this->type = old_element.type;
    this->name = old_element.name;
    this->has_changed = old_element.has_changed;
    this->is_visible = old_element.is_visible;
    this->pos =
    {
        .x = old_element.pos.x,
        .y = old_element.pos.y
    };
}

// Mutators
/*
 * Toggles the visibility of the Element, marking that it has changed.
 */
void Element::toggle_visible()
{
    this->is_visible = !(this->is_visible);
    this->has_changed = true;
}

/*
 * Makes the Element visible, marking that it has changed.
 */
void Element::make_visible()
{
    this->is_visible = true;
    this->has_changed = true;
}

/*
 * Makes the Element invisible, marking that it has changed.
 */
void Element::make_invisible()
{
    this->is_visible = false;
    this->has_changed = true;
}

/*
 * Resets whether the Element has changed back to false. This should only
 * be called after these changes have been accounted for.
 */
void Element::reset_has_changed() { this->has_changed = false; }

/*
 * Sets the position of the Element to the passed integer values, marking
 * that it has changed.
 */
void Element::set_pos(int x, int y)
{
    this->pos = {.x = x, .y = y};
    this->has_changed = true;
}

/*
 * Sets the position of the Element to the passed int_duple, marking
 * that it has changed.
 */
void Element::set_pos(struct int_duple m_pos)
{
    this->pos = m_pos;
    this->has_changed = true;
}
