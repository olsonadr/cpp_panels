/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#include "../headers/Element.hpp"

Element::Element(int pos_x, int pos_y,
                 const char *type, const char *name)
    : type(type)
{
    this->has_changed = true;
    this->pos = {
        .x = pos_x,
        .y = pos_y};
}

Element::Element(const Element &old_element)
{
    this->type = old_element.type;
    this->name = old_element.name;
    this->has_changed = old_element.has_changed;
    this->is_visible = old_element.is_visible;
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