/*
 *  Border class, which is a special type of Component. Each Border holds the
 *  data necessary to display a border from it's position (hopefully (0,0)) to
 *  the edges of the container holding it. Can be constructed defining the cor-
 *  ners and all four sides or the corners, top and bottom char, and left and
 *  right char.
 */

#include "Border.hpp"

// Constructors
Border::Border(char corners,
               char top, char bottom,
               char left, char right,
               bool is_dynamic,
               const char * name)
    : Element(0, 0, is_dynamic, "Border", name),
      corner_char(corners),
      top_char(top), bottom_char(bottom),
      left_char(left), right_char(right) {}

Border::Border(char corners,
               char top_and_bot,
               char left_and_right,
               bool is_dynamic,
               const char * name)
    : Element(0, 0, is_dynamic, "Border", name),
      corner_char(corners),
      top_char(top_and_bot),
      bottom_char(top_and_bot),
      left_char(left_and_right),
      right_char(left_and_right) {}

// Copy Constructor
Border::Border(const Border & old_border, bool is_dynamic)
    : Element(old_border, is_dynamic),
      corner_char(old_border.corner_char),
      top_char(old_border.top_char),
      bottom_char(old_border.bottom_char),
      left_char(old_border.left_char),
      right_char(old_border.right_char) {}

// Overloaded Operator
void Border::operator=(const Border & old_border)
{
    Element::operator=(old_border);
    this->corner_char = old_border.corner_char;
    this->top_char = old_border.top_char;
    this->bottom_char = old_border.bottom_char;
    this->left_char = old_border.left_char;
    this->right_char = old_border.right_char;
}
