/*
 *  List class, is a container wherein its members are listed in order,
 *  and removing or toggling the visibility of an element shifts the other
 *  Elements upward, the dimensions of the list depend on the size of its
 *  members.
 */

#ifndef LIST_HPP
#define LIST_HPP

#define VERTICAL_LIST true
#define HORIZONTAL_LIST false

#include "Container.hpp"
#include "Label.hpp"

class List : public Container
{
    protected:
        // Fields
        bool is_vertical;
        int padding;
        int margins;

    public:
        // Constructors + Destructors + Operators
        List(int pos_x, int pos_y,
             int other_dimension,
             bool is_dynamic,
             bool is_vertical,
             const char * name = "List");

        List(int pos_x, int pos_y,
             int other_dimension,
             bool is_dynamic,
             const char * name = "List");

        List(const List & old_List, bool is_dynamic = STATIC_ELEMENT);

        void operator=(const List & old_list);

        // Accessors
        bool get_is_vertical() { return this->is_vertical; }

        // Mutators
        void set_is_vertical(bool new_val, int new_other_dim);
        void set_padding(int new_padding);
        void set_margins(int new_margins);

        // Overriden
        char * merge();
        void update();
};

#endif
