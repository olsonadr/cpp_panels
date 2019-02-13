/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#include "Element.hpp"

Element::Element(int pos_x, int pos_y, bool is_dynamic,
                 const char *type, const char *name)
    : type(type), has_changed(true), is_visible(true), name(name), is_dynamic(is_dynamic)
{
    this->pos = {
        .x = pos_x,
        .y = pos_y};
}

Element::Element(const Element &old_element, bool is_dynamic)
{
    this->type = old_element.type;
    this->name = old_element.name;
    this->has_changed = old_element.has_changed;
    this->is_visible = old_element.is_visible;
    this->is_dynamic = is_dynamic;
    this->pos = {
        .x = old_element.pos.x,
        .y = old_element.pos.y};
}

void Element::operator=(const Element &old_element)
{
    this->type = old_element.type;
    this->name = old_element.name;
    this->has_changed = old_element.has_changed;
    this->is_visible = old_element.is_visible;
    this->pos = {
        .x = old_element.pos.x,
        .y = old_element.pos.y};
}

void Element::toggle_visible()
{
    this->is_visible = !(this->is_visible);
    this->has_changed = true;
}