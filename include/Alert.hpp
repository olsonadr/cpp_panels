/*
 *  Alert class. It is a Component that has only an alert message, which it
 *  centers in a box that spans most of its parent container. You interface
 *  with an Alert just like you would a Label.
 */

#ifndef ALERT_HPP
#define ALERT_HPP

#include <cstdio>
#include <cstring>
#include "Element.hpp"
#include "Border.hpp"

class Alert : public Element
{
    protected:
        const char * message;
        float size_percentage;
        Border * border;
        char bg_char;
        int len;

    public:
        // Constructors + Destructors + Overloaded Assignment
        Alert(const char * message,
              bool is_dynamic,
              const char * name = "Alert");

        Alert(const Alert & old_alert, bool is_dynamic = STATIC_ELEMENT);

        void operator=(const Alert & old_alert);

        ~Alert();

        // Accessors
        const char * get_message()  { return this->message; }
        char get_bg_char()	    { return this->bg_char; }
        int get_len()		    { return this->len; }
        float get_size_percentage() { return this->size_percentage; }

        // Border Accessors
        char get_corner_char()	{ return this->border->get_corner_char(); }
        char get_top_char()	{ return this->border->get_top_char(); }
        char get_bottom_char()	{ return this->border->get_bottom_char(); }
        char get_left_char()	{ return this->border->get_left_char(); }
        char get_right_char()	{ return this->border->get_right_char(); }

        // Mutators
        void set_bg_char(char new_bg_char);
        void set_size_percentage(float new_val);
        void set_message(const char * new_val);
        void set_border(Border * new_border);
        void set_border(Border & new_border);

        // Misc
        int get_x_span(); /* Determines the number of characters
			     this Alert spans horizontally */
        int get_y_span(); /* Determines the number of characters
			     this Alert spans vertically */

        // Overriden
        bool get_has_changed();
        void reset_has_changed();
};

#endif
