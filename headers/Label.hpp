/*
 *  Label class, which is the lowest level of Component. Each Label is a
 *  C-style string with a position, although it can be initialized as
 *  vertical. \n can be used in the string.
 */

#ifndef LABEL_HPP
#define LABEL_HPP

#include "Element.hpp"

class Label : public Element
{
protected:
  const char *str;
  int len;
  bool is_vertical;

public:
  // Constructors + Destructors + Overloaded Assignment
  Label(int pos_x, int pos_y,
        const char *str,
        bool is_dynamic,
        bool is_vertical,
        const char *name = "Label");

  Label(int pos_x, int pos_y,
        const char *str,
        bool is_dynamic,
        const char *name = "Label");

  Label(const Label &old_label, bool is_dynamic = false)
      : Element(old_label, is_dynamic),
        str(old_label.str),
        len(old_label.len),
        is_vertical(old_label.is_vertical) {}

  void operator=(const Label &old_label);

  // Accessors + Mutators
  void set_str(const char *new_val,
               bool is_vertical = false);

  const char *get_str() { return this->str; }

  int get_len() { return this->len; }

  bool get_is_vertical() { return this->is_vertical; }
};

#endif