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
      Label(int pos_x = 0, int pos_y = 0,
            const char *str = "",
            bool is_vertical = false,
            const char *name = "Label")
          : Element(pos_x, pos_y, "Label", name),
            str(str), is_vertical(is_vertical) { this->len = sizeof(str) - 1; }

      Label(const Label &old_label)
          : Element(old_label),
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