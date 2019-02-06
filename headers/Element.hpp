/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

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
  const char *name;
  const char *type;

public:
  // Constructors + Operator Overload
  Element(int pos_x = 0, int pos_y = 0,
          const char *type = "Element",
          const char *name = "Element");

  Element(const Element &old_element);

  void operator=(const Element &old_element);

  // Misc Methods
  int_duple get_pos() { return this->pos; }
  bool get_is_visible() { return this->is_visible; }
  bool get_has_changed() { return this->has_changed; }
  void reset_has_changed() { this->has_changed = false; }
  const char *get_type() { return this->type; }
  void toggle_visible();
};

#endif