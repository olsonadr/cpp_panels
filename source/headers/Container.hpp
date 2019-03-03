/*
 *  Container class. It is an Element with dimensions that has an array of
 *  Elements, which it can compile into one 2D array of characters for
 *  rendering of many layered elements.
 */

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstring>      /* For strcmp() */
#include <cmath>	/* For round() */
#include "Element.hpp"  /* Base class of Container */
#include "Label.hpp"    /* For using specific functionality while merging */
#include "Border.hpp"   /* For using specific functionality while merging */
#include "Console.hpp"  /* For using specific functionality while merging */
#include "Alert.hpp"	/* For using specific functionality while merging */

class Container : public Element
{
    protected:
        // Fields (inherits visibility, type, position)
        struct int_duple dim; /* Dimensions of the container */
        char * merged_arr;    /* Dynamic 1D arr of chars of merged layers */
        Element ** members;   /* Dynamic array of Element pointers */
        int n_members;        /* Number of members in members arr */
        int len_members;      /* Length of members arr */
        char bg_char;	      /* The character to be put in empty space */

        // Methods
        void grow_members();	    /* Increases size of members array */
        void reset_merged();	    /* Resets the merged arr to blank (has_changed) */
        bool check_must_update();   /* Checks members if they need to update */

    public:
        // Constructors + Assignment Overload + Destructors
        Container(int pos_x, int pos_y,
                  int width, int height,
                  bool is_dynamic,
                  const char * type = "Container",
                  const char * name = "Container"); /* Primary constructor, empty members */

        Container(const Container & old_container,
                  bool is_dynamic = STATIC_ELEMENT); /* Copy constructor */

        void operator=(const Container & old_container); /* Overloaded assignment */

        virtual ~Container();

        // Accessors
        int_duple get_dim() { return this->dim; }
        int get_n_members() { return this->n_members; }
        Element * get_member(int index) { return this->members[index]; }
        char get_bg_char() { return this->bg_char; }

        // Mutators
        void set_bg_char(char new_bg_char);
        void add(Element & passed_element);
        void add(Element * passed_element);
        void remove(int index);
        virtual bool get_has_changed();
        virtual char * merge();

        // Misc
        Element * find(const char * name);
        int_duple find_global_pos(const char * name);
};

#endif
