/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#define DYNAMIC_ELEMENT true
#define STATIC_ELEMENT false

class Element
{
protected:
  struct int_duple
  {
    int x;
    int y;
  };
  struct int_duple pos;
  bool has_changed;
  bool is_visible;
  bool is_dynamic;
  const char *name;
  const char *type;

public:
  // Constructors + Operator Overload
  Element(int pos_x, int pos_y, bool is_dynamic,
          const char *type = "Element",
          const char *name = "Element");

  Element(const Element &old_element, bool is_dynamic = STATIC_ELEMENT);

  void operator=(const Element &old_element);

  // Accessors
  int_duple get_pos() { return this->pos; }
  const char *get_name() { return this->name; }
  bool get_is_visible() { return this->is_visible; }
  bool get_has_changed() { return this->has_changed; }
  bool get_is_dynamic() { return this->is_dynamic; }
  const char *get_type() { return this->type; }

  // Mutators
  void set_pos(int x, int y) { this->pos = {.x = x, .y = y}; }
  void reset_has_changed() { this->has_changed = false; }
  void make_visible() { this->is_visible = true; }
  void make_invisible() { this->is_visible = false; }
  void toggle_visible();
};

#endif