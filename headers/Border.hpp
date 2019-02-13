/*
 *  Border class, which is a special type of Component. Each Border holds the
 *  data necessary to display a border from it's position (hopefully (0,0)) to
 *  the edges of the container holding it. Can be constructed defining the cor-
 *  ners and all four sides or the corners, top and bottom char, and left and
 *  right char.
 */

#ifndef BORDER_HPP
#define BORDER_HPP

#include "Element.hpp"

class Border : public Element
{
  protected:
    char corner_char;
    char left_char;
    char right_char;
    char top_char;
    char bottom_char;

  public:
    // Constructors + Operators

    Border(char corners,
           char top, char bottom,
           char left, char right,
           bool is_dynamic,
           const char *name = "Border");

    Border(char corners,
           char top_and_bot,
           char left_and_right,
           bool is_dynamic,
           const char *name = "Border");

    Border(const Border &old_border,
           bool is_dynamic = false);

    void operator=(const Border &old_border);

    // Accessors
    char get_corner_char() { return this->corner_char; }
    char get_top_char() { return this->top_char; }
    char get_bottom_char() { return this->bottom_char; }
    char get_left_char() { return this->left_char; }
    char get_right_char() { return this->right_char; }

    // Mutators
    void set_corner_char(char m_char) { this->corner_char = m_char; }
    void set_top_char(char m_char) { this->top_char = m_char; }
    void set_bottom_char(char m_char) { this->bottom_char = m_char; }
    void set_left_char(char m_char) { this->left_char = m_char; }
    void set_right_char(char m_char) { this->right_char = m_char; }
};

#endif